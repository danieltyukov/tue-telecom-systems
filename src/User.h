#ifndef ___5XTA0_OMNET_ERLANG_USER_H
#define ___5XTA0_OMNET_ERLANG_USER_H

#include <omnetpp.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Erlang_m.h"

using namespace omnetpp;

namespace _5xta0_omnet_erlang {

class User : public cSimpleModule
{
    std::string name;
    int userID;
    int numberOfUsers;
    double meanCallDuration;
    double meanTimeBetweenCalls;
    bool callFlag = false;
    enum Status {IDLE, CALLER, CALLEE};
    Status status;
    enum EMsgName {CALLREQUEST, CONFIRM, HANGUP, REJECT_NOCHANNELS, REJECT_USERBUSY};
    cExponential  rngExp;
    cErlang       rngErl;
    cNormal       rngNor;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void refreshStatus();
    virtual int randomCallee();
    virtual const char* EMsgNameToConstChar(EMsgName messageName);
    virtual EMsgName ConstCharToEMsgName(const char* messageName);
    virtual int callAnotherUser();
    virtual void hangUp(int calleeId);
    virtual bool IsGonnaCall();
//    virtual void sendMessage();
};

}; // namespace

#endif
