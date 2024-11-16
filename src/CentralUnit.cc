#include "CentralUnit.h"

namespace _5xta0_omnet_erlang {

Define_Module(CentralUnit);

void CentralUnit::initialize()
{
    nChannelsAvailable = par("numberOfChannels");
    linkList.reserve(nChannelsAvailable);
}

void CentralUnit::handleMessage(cMessage *msg)
{
    ErlangMsg* message = dynamic_cast<ErlangMsg*>(msg);
    std::string name = message->getName();
    int callerId = message->getCallerId();
    int calleeId = message->getCalleeId();
    delete msg;
    EV << name << " " << callerId << " " << calleeId << "\n";
    EMsgName ename = ConstCharToEMsgName(name.c_str());

    switch(ename)
    {
    case EMsgName::CALLREQUEST:
//        if (nChannelsUsed >= nChannelsAvailable) {
//            notifyCaller(callerId, calleeId, EMsgName::REJECT_NOCHANNELS);
//            rejectNoChannelsCounter++;
//        }
//        else if (checkIfUserInCall(calleeId) || checkIfUserInCall(callerId)) {
//            notifyCaller(callerId, calleeId, EMsgName::REJECT_USERBUSY);
//            rejectUserBusyCounter++;
//        }
        if (checkIfUserInCall(calleeId) || checkIfUserInCall(callerId)) {
            notifyCaller(callerId, calleeId, EMsgName::REJECT_USERBUSY);
            rejectUserBusyCounter++;
        }
        else if (nChannelsUsed >= nChannelsAvailable) {
            notifyCaller(callerId, calleeId, EMsgName::REJECT_NOCHANNELS);
            rejectNoChannelsCounter++;
        }
        else {
            addToLinkList(callerId, calleeId);
            notifyBothUsers(callerId, calleeId, EMsgName::CONFIRM);
            successCounter++;
        }
        callRequestCounter++;
        break;
    case EMsgName::HANGUP:
        removeFromlinkList(callerId, calleeId);
        notifyBothUsers(callerId, calleeId, EMsgName::HANGUP);
        break;
    case EMsgName::REJECT_NOCHANNELS:
        EV << "Debug: Nothing to do\n";
        break;
    case EMsgName::REJECT_USERBUSY:
        EV << "Debug: Nothing to do\n";
        break;
    case EMsgName::CONFIRM:
        EV << "Debug: Nothing to do\n";
        break;
    default:
        EV << "Debug: Nothing to do\n";
        break;
    }
}

void CentralUnit::finish()
{
    EV << getName() << " Number of call requests                  :    " << std::setw(5) << callRequestCounter               << "\n";
    EV << getName() << " Number of successful calls               :    " << std::setw(5) << successCounter                   << "\n";
//    EV << getName() << " Number of hang ups                       :    " << std::setw(5) << hangUpCounter                    << "\n";
    EV << getName() << " Number of rejected calls (user busy)     :    " << std::setw(5) << rejectUserBusyCounter            << "\n";
    EV << getName() << " Number of rejected calls (no channels)   :    " << std::setw(5) << rejectNoChannelsCounter          << "\n";
    EV << getName() << " Total call duration                      :    " << std::setw(5) << totalCallDuration                << " seconds\n";
    EV << getName() << " Average call duration                    :    " << std::setw(5) << totalCallDuration/hangUpCounter  << " seconds\n";
//    EV << " Traffic load          :    " << std::setw(5) << totalCallDuration/3600           << " Erlang\n";
//    EV << " Blocking probability  :    " << std::setw(5) << 100.0*rejectNoChannelsCounter/callRequestCounter  << " %\n";
}

void CentralUnit::notifyCaller(int callerId, int calleeId, EMsgName msgName)
{
    ErlangMsg *newMsg = new ErlangMsg(EMsgNameToConstChar(msgName));
    newMsg->setCallerId(callerId);
    newMsg->setCalleeId(calleeId);
    send(newMsg, "gate$o", callerId);
}

void CentralUnit::notifyCallee(int callerId, int calleeId, EMsgName msgName)
{
    ErlangMsg *newMsg = new ErlangMsg(EMsgNameToConstChar(msgName));
    newMsg->setCallerId(callerId);
    newMsg->setCalleeId(calleeId);
    send(newMsg, "gate$o", calleeId);
}

void CentralUnit::notifyBothUsers(int callerId, int calleeId, EMsgName msgName)
{
    ErlangMsg *newMsg1 = new ErlangMsg(EMsgNameToConstChar(msgName));
    newMsg1->setCallerId(callerId);
    newMsg1->setCalleeId(calleeId);
    send(newMsg1, "gate$o", callerId);
    ErlangMsg *newMsg2 = new ErlangMsg(EMsgNameToConstChar(msgName));
    newMsg2->setCallerId(callerId);
    newMsg2->setCalleeId(calleeId);
    send(newMsg2, "gate$o", calleeId);
}

void CentralUnit::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "%d out of %d channels used", nChannelsUsed, nChannelsAvailable);
    getDisplayString().setTagArg("t", 0, buf);
}

bool CentralUnit::checkIfUserInCall(int id)
{
    bool inCall = false;
    SLink iterLink;
    for (int i = 0; i < linkList.size(); i++)
    {
        iterLink = linkList[i];
        if (iterLink.calleeId == id || iterLink.callerId == id)
        {
            inCall = true;
            break;
        }
    }
    return inCall;
}

void CentralUnit::addToLinkList(int callerId, int calleeId)
{
    SLink link = {callerId, calleeId, simTime().dbl()};
    linkList.push_back(link);
    nChannelsUsed++;
}

void CentralUnit::removeFromlinkList(int callerId, int calleeId)
{
    SLink link = {callerId, calleeId, 0};
    SLink iterLink;
    double callDuration = 0;
    for (int i = 0; i < linkList.size(); i++)
    {
        iterLink = linkList[i];
        if (iterLink.calleeId == link.calleeId && iterLink.callerId == link.callerId)
        {
            callDuration = simTime().dbl() - iterLink.callStartTime;
            totalCallDuration += callDuration;
            linkList.erase(linkList.begin() + i);
            nChannelsUsed--;
            hangUpCounter++;
            break;
        }
    }
}

const char* CentralUnit::EMsgNameToConstChar(EMsgName messageName)
{
    switch(messageName)
    {
    case EMsgName::CALLREQUEST:
        return "CALLREQUEST";
    case EMsgName::CONFIRM:
        return "CONFIRM";
    case EMsgName::HANGUP:
        return "HANGUP";
    case EMsgName::REJECT_NOCHANNELS:
        return "REJECT_NOCHANNELS";
    case EMsgName::REJECT_USERBUSY:
        return "REJECT_USERBUSY";
    default:
        return " ";
    }
}

CentralUnit::EMsgName CentralUnit::ConstCharToEMsgName(const char* messageName)
{
    EMsgName msgName;
    if (strcmp(messageName, "CALLREQUEST") == 0)
        msgName = EMsgName::CALLREQUEST;
    else if (strcmp(messageName, "CONFIRM") == 0)
        msgName = EMsgName::CONFIRM;
    else if (strcmp(messageName, "HANGUP") == 0)
        msgName = EMsgName::HANGUP;
    else if (strcmp(messageName, "REJECT_NOCHANNELS") == 0)
        msgName = EMsgName::REJECT_NOCHANNELS;
    else if (strcmp(messageName, "REJECT_USERBUSY") == 0)
        msgName = EMsgName::REJECT_USERBUSY;
    return msgName;
}


}; // namespace
