package _5xta0_omnet_erlang;

simple User
{
    parameters:
        int numberOfUsers;
        double meanCallDuration;
        double meanTimeBetweenCalls;
        @display("i=block/user");
    gates:
        inout gate;
}
