import inet.node.inet.AdhocHost;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.ethernet.Eth100M;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.apskradio.packetlevel.ApskScalarRadioMedium;

import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.visualizer.integrated.IntegratedVisualizer;

network _5xta0_mac_assignment
{
    parameters:
        @display("bgb=800,600");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=50.7,41.6");
        }
        visualizer: IntegratedVisualizer {
            @display("p=144.3,41.6");
        }
        radioMedium: ApskScalarRadioMedium {
            @display("p=244.4,41.6");
        }
        server: StandardHost {
            @display("p=113.1,165.09999");
        }
        Cell7Node1: AdhocHost {
            parameters:
                @display("p=390,72.799995;i=misc/person3");
        }
        Cell7Node2: AdhocHost {
            parameters:
                @display("p=474.5,81.9;i=misc/person4");
        }
        Cell7Node3: AdhocHost {
            parameters:
                @display("p=353.6,163.8;i=misc/person3");
        }
        Cell6Node1: AdhocHost {
            parameters:
                @display("p=514.8,175.5;i=misc/person4");
        }
        Cell1Node1: AdhocHost {
            parameters:
                @display("p=353.6,267.8;i=misc/person3");
        }
        Cell7Node4: AdhocHost {
            parameters:
                @display("p=435.5,236.59999;i=misc/person4");
        }
        Cell5Node1: AdhocHost {
            parameters:
                @display("p=530.39996,299;i=misc/person3");
        }
        Cell1Node2: AdhocHost {
            parameters:
                @display("p=353.6,347.1;i=misc/person4");
        }
        Cell1Node3: AdhocHost {
            parameters:
                @display("p=435.5,330.19998;i=misc/person3");
        }
        Cell3Node1: AdhocHost {
            parameters:
                @display("p=508.3,390;i=misc/person4");
        }
        Cell2Node1: AdhocHost {
            parameters:
                @display("p=412.1,400.4;i=misc/person3");
        }
        Cell2Node2: AdhocHost {
            parameters:
                @display("p=319.8,443.3;i=misc/person4");
        }
        Cell3Node2: AdhocHost {
            parameters:
                @display("p=529.1,464.1;i=misc/person3");
        }
        Cell4Node1: AdhocHost {
            parameters:
                @display("p=145.59999,249.59999;i=misc/person4");
        }
        Cell4Node2: AdhocHost {
            parameters:
                @display("p=114.4,335.4;i=misc/person3");
        }
        Cell4Node3: AdhocHost {
            parameters:
                @display("p=192.4,358.8;i=misc/person4");
        }
        Cell2Node3: AdhocHost {
            parameters:
                @display("p=367.9,544.7;i=misc/person3");
        }
        Cell4Node4: AdhocHost {
            parameters:
                @display("p=269.1,249.59999;i=misc/person4");
        }
        Cell1Node4: AdhocHost {
            parameters:
                @display("p=269.1,366.6;i=misc/person3");
        }
        Cell2Node4: AdhocHost {
            parameters:
                @display("p=455,536.89996;i=misc/person4");
        }
        Cell6Node2: AdhocHost {
            parameters:
                @display("p=692.89996,236.59999;i=misc/person3");
        }
        Cell6Node3: AdhocHost {
            parameters:
                @display("p=600.6,227.5;i=misc/person4");
        }
        Cell5Node2: AdhocHost {
            parameters:
                @display("p=600.6,358.8;i=misc/person3");
        }
        Cell5Node3: AdhocHost {
            parameters:
                @display("p=681.2,315.9;i=misc/person4");
        }
        Cell3Node3: AdhocHost {
            parameters:
                @display("p=660.39996,390;i=misc/person3");
        }
        Cell1: WirelessHost {
            @display("p=334.616,318.912;i=device/antennatower;r=100");
        }
        Cell2: WirelessHost {
            @display("p=401.056,473.53598;i=device/antennatower;r=100");
        }
        Cell3: WirelessHost {
            @display("p=581.048,426.42398;i=device/antennatower;r=100");
        }
        Cell4: WirelessHost {
            @display("p=193.28,315.288;i=device/antennatower;r=100");
        }
        Cell5: WirelessHost {
            @display("p=613.664,315.288;i=device/antennatower;r=100");
        }
        Cell6: WirelessHost {
            @display("p=613.664,164.288;i=device/antennatower;r=100");
        }
        Cell7: WirelessHost {
            @display("p=436.08798,153.416;i=device/antennatower;r=100");
        }
    connections:
        Cell1.ethg++ <--> Eth100M <--> server.ethg++;
        Cell3.ethg++ <--> Eth100M <--> server.ethg++;
        Cell2.ethg++ <--> Eth100M <--> server.ethg++;
        Cell4.ethg++ <--> Eth100M <--> server.ethg++;
        Cell5.ethg++ <--> Eth100M <--> server.ethg++;
        Cell6.ethg++ <--> Eth100M <--> server.ethg++;
        Cell7.ethg++ <--> Eth100M <--> server.ethg++;
}
