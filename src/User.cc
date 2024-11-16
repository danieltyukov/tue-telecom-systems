#include "User.h"

namespace _5xta0_omnet_erlang {

Define_Module(User);

void User::initialize()
{
    name = getFullName();
    userID = stoi(name.substr(5, name.length() - 6));
    numberOfUsers = par("numberOfUsers");
    meanCallDuration = par("meanCallDuration");
    meanTimeBetweenCalls = par("meanTimeBetweenCalls");
    status = IDLE;
    refreshStatus();
    rngExp.setMean(meanCallDuration);
    rngErl.setMean(meanTimeBetweenCalls);
//    if (rngNor.draw() > 0)
//    if (IsGonnaCall())
    if (userID % 4 == 0)
        callAnotherUser();
}

void User::handleMessage(cMessage *msg)
{
    ErlangMsg* message = dynamic_cast<ErlangMsg*>(msg);
    std::string name = message->getName();
    int callerId = message->getCallerId();
    int calleeId = message->getCalleeId();
    delete msg;
//    EV << name << " " << callerId << " " << calleeId << "\n";
    EMsgName ename = ConstCharToEMsgName(name.c_str());

    switch(ename)
    {
    case EMsgName::CALLREQUEST:
//        EV << "Debug: Nothing to do\n";
        break;
    case EMsgName::CONFIRM:
        if (userID == callerId)
            status = Status::CALLER;
        else
            status = Status::CALLEE;
        refreshStatus();
        if (status == Status::CALLER)
            hangUp(calleeId);
        break;
    case EMsgName::HANGUP:
        status = Status::IDLE;
        refreshStatus();
//        if (rngNor.draw() > 0)
        if (IsGonnaCall())
            callAnotherUser();
        break;
    case EMsgName::REJECT_NOCHANNELS:
//        if (rngNor.draw() > 0)
            callAnotherUser();
        break;
    case EMsgName::REJECT_USERBUSY:
//        if (rngNor.draw() > 0)
            callAnotherUser();
        break;
    default:
        EV << "Debug: Nothing to do\n";
        break;
    }
}

void User::finish()
{
    return;
}

int User::callAnotherUser()
{
    int calleeId = randomCallee();
    ErlangMsg *newMsg = new ErlangMsg(EMsgNameToConstChar(EMsgName::CALLREQUEST));
    newMsg->setCallerId(userID);
    newMsg->setCalleeId(calleeId);
    sendDelayed(newMsg, rngErl.draw(), "gate$o");
    return calleeId;
}

void User::hangUp(int calleeId)
{
    ErlangMsg *newMsg = new ErlangMsg(EMsgNameToConstChar(EMsgName::HANGUP));
    newMsg->setCallerId(userID);
    newMsg->setCalleeId(calleeId);
    double callLength = rngExp.draw();
    sendDelayed(newMsg, callLength, "gate$o");
}

void User::refreshStatus()
{
    cDisplayString& dispStr = getDisplayString();
    if (status == IDLE)
        dispStr.parse("i=block/user,green,100");
    else
        dispStr.parse("i=block/user,red,100");
}

int User::randomCallee()
{
    // make sure the caller does not call themselves
    int calleeId = userID;
    while (calleeId == userID)
        calleeId =  rand() % numberOfUsers;
    return calleeId;
}

const char* User::EMsgNameToConstChar(EMsgName messageName)
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

User::EMsgName User::ConstCharToEMsgName(const char* messageName)
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


bool User::IsGonnaCall()
{
    return (userID % 10);
}


}; // namespace
