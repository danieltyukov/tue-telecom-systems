#ifndef ___5XTA0_OMNET_ERLANG_CENTRALUNIT_H
#define ___5XTA0_OMNET_ERLANG_CENTRALUNIT_H

#include <omnetpp.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Erlang_m.h"

using namespace omnetpp;

namespace _5xta0_omnet_erlang {

class CentralUnit : public cSimpleModule
{
    int nChannelsAvailable      = 0;
    int nChannelsUsed           = 0;
    int callRequestCounter      = 0;
    int successCounter          = 0;
    int hangUpCounter           = 0;
    int rejectUserBusyCounter   = 0;
    int rejectNoChannelsCounter = 0;
    double totalCallDuration    = 0;
    struct SLink
    {
        int callerId;
        int calleeId;
        double callStartTime;
    };
    std::vector<SLink> linkList;
    enum EMsgName {CALLREQUEST, CONFIRM, HANGUP, REJECT_NOCHANNELS, REJECT_USERBUSY};
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void refreshDisplay() const override;
    virtual void addToLinkList(int callerId, int calleeId);
    virtual void removeFromlinkList(int callerId, int calleeId);
    virtual const char* EMsgNameToConstChar(EMsgName messageName);
    virtual EMsgName ConstCharToEMsgName(const char* messageName);
    virtual bool checkIfUserInCall(int id);
    virtual void notifyBothUsers(int callerId, int calleeId, EMsgName msgName);
    virtual void notifyCaller(int callerId, int calleeId, EMsgName msgName);
    virtual void notifyCallee(int callerId, int calleeId, EMsgName msgName);
};

}; // namespace

#endif
