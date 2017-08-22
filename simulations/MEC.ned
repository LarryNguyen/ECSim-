//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import inet.common.lifecycle.LifecycleController;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.WirelessHost;
import inet.node.inet.AdhocHost;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.networklayer.configurator.ipv4.HostAutoConfigurator;
import ned.DatarateChannel;
import inet.node.inet.StandardHost;
import inet.node.wireless.AccessPoint;
import inet.common.misc.ThruputMeteringChannel;
import inet.networklayer.ipv4.IPv4ServiceTable;
import mec_sim.EdgeNode;
import inet.node.ethernet.Eth100M;

network mec
{
    parameters:
        int numHostsE1 = 3;
        int numHostsE2 = 2;
        int numHostsE3 = 3;

        int numServices = 5;
        **.mgmt.numChannels = 1;
        @display("bgb=699,481");
    types:
        channel C100 extends DatarateChannel
        {
            datarate = 100Mbps;
            delay = 0.1us;
        }
        channel C extends ThruputMeteringChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "#N";
        }
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            parameters:
                @display("p=46,24");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xmldoc("config3.xml");
                addStaticRoutes = true;
                addDefaultRoutes = true;
                @display("p=103,24");
        }
        //radioMedium: Ieee80211ScalarRadioMedium {
        //    parameters:
        //        @display("p=30,256");
        //}
        Edge1: EdgeNode {
            @display("p=214,272;i=device/antennatower");
        }

        //SP1: StandardHost {
        //    @display("p=405,24;i=device/server");
        //}
        //SP2: StandardHost {
        //    @display("p=518,24;i=device/server");
        //}
        SP[numServices]: StandardHost {
            @display("is=s;p=372,17,r;i=device/server");
        }
        Enoma: StandardHost {
            @display("p=234,24;i=device/server");
        }

        RG1: EdgeNode {
            @display("p=239,159");
        }
        Core: EdgeNode {
            @display("p=315,94");
        }
        RG2: EdgeNode {
            @display("p=444,159");
        }
        Edge2: EdgeNode {
            @display("p=405,283;i=device/antennatower");
        }
        Edge3: EdgeNode {
            @display("p=573,231;i=device/antennatower");
        }
        ue1[numHostsE1]: StandardHost {
            @display("is=s;p=17,428,r;i=device/cellphone");
            //@display("p=,r;i=device/cellphone");
        }
        ue2[numHostsE2]: StandardHost {
            @display("is=s;p=340,398,r;i=device/cellphone");
            //@display("p=,r;i=device/cellphone");
        }
        ue3[numHostsE3]: StandardHost {
            @display("is=s;p=608,428,r;i=device/cellphone");
            //@display("p=,r;i=device/cellphone");
        }
		//ue: WirelessHost {
        //    @display("r=,,#707070;p=129,394");
        //}
        //ap: AccessPoint {
        //    @display("p=143,350");
        //}

        Sw: EtherSwitch {
            @display("p=462,85");
        }
        lifecycleController: LifecycleController {
            @display("p=34,72");
        }
        //test: StandardHost {
        //    @display("p=138,272;i=device/server");
        //}
        //r1: Router {
        //    @display("p=208,332");
        //}
        sw1: EtherSwitch {
            @display("p=151,349");
        }
        sw2: EtherSwitch {
            @display("p=383,349");
        }
        sw3: EtherSwitch {
            @display("p=622,315");
        }
    connections:

        Edge1.ethg++ <--> C <--> RG1.ethg++; //edge1[1] - RG1[0]
        Edge2.ethg++ <--> C <--> RG1.ethg++; //edge2[0] - RG1[1]
        Enoma.ethg++ <--> C <--> Core.ethg++; //Enoma[0] - Core[0]
        Sw.ethg++ <--> C <--> Core.ethg++; //SP1[0] - Core[1]
        RG1.ethg++ <--> C <--> Core.ethg++; //RG1[2] - Core[2]
        RG2.ethg++ <--> C <--> Core.ethg++; //RG2[0] - Core[3]
        RG1.ethg++ <--> C <--> RG2.ethg++; //RG1[3] - RG2[1]
        RG2.ethg++ <--> C <--> Edge3.ethg++; //RG2[2] - Edge3[0]
        Edge1.ethg++ <--> C <--> sw1.ethg++;
        Edge2.ethg++ <--> C <--> sw2.ethg++;
        Edge3.ethg++ <--> C <--> sw3.ethg++;
        for i=0..numHostsE1-1 {
            sw1.ethg++ <--> C <--> ue1[i].ethg++;
        }
        for i=0..numHostsE2-1 {
            sw2.ethg++ <--> C <--> ue2[i].ethg++;
        }
        for i=0..numHostsE3-1 {
            sw3.ethg++ <--> C <--> ue3[i].ethg++;
        }
        for i=0..numServices-1 {
            Sw.ethg++ <--> C <--> SP[i].ethg++;
        }
        //Sw.ethg++ <--> C <--> SP1.ethg++;
        //Sw.ethg++ <--> C <--> SP2.ethg++;


}
