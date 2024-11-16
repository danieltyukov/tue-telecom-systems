//
// Generated file, do not edit! Created by nedtool 5.7 from Erlang.msg.
//

#ifndef ___5XTA0_OMNET_ERLANG_ERLANG_M_H
#define ___5XTA0_OMNET_ERLANG_ERLANG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace _5xta0_omnet_erlang {

/**
 * Class generated from <tt>Erlang.msg:3</tt> by nedtool.
 * <pre>
 * packet ErlangMsg
 * {
 *     int callerId;
 *     int calleeId;
 * 
 * }
 * </pre>
 */
class ErlangMsg : public ::omnetpp::cPacket
{
  protected:
    int callerId;
    int calleeId;

  private:
    void copy(const ErlangMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ErlangMsg&);

  public:
    ErlangMsg(const char *name=nullptr, short kind=0);
    ErlangMsg(const ErlangMsg& other);
    virtual ~ErlangMsg();
    ErlangMsg& operator=(const ErlangMsg& other);
    virtual ErlangMsg *dup() const override {return new ErlangMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getCallerId() const;
    virtual void setCallerId(int callerId);
    virtual int getCalleeId() const;
    virtual void setCalleeId(int calleeId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ErlangMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ErlangMsg& obj) {obj.parsimUnpack(b);}

} // namespace _5xta0_omnet_erlang

#endif // ifndef ___5XTA0_OMNET_ERLANG_ERLANG_M_H

