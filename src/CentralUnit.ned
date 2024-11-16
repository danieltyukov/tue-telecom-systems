package _5xta0_omnet_erlang;

simple CentralUnit
{
    parameters:
        int numberOfChannels;
        @display("i=block/network");
    gates:
        inout gate[];
}
