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

network mec
{
    parameters:
        int numHosts = 0;
        //**.mgmt.numChannels = 1;
        @display("bgb=699,414");
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
        //mobile: WirelessHost {
        //    @display("r=,,#707070;p=129,394");
        //}
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xmldoc("config2.xml");
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

        //ap: AccessPoint {
        //    @display("p=143,350");
        //}
        SP1: StandardHost {
            @display("p=405,24;i=device/server");
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
        ue: StandardHost {
            @display("p=214,394;i=device/cellphone");
        }
        //        serviceTable: IPv4ServiceTable {
        //            parameters:
        //                @display("p=38,96;is=s");
        //                serviceConfig = xmldoc("service.xml");
        //        }
        //ap: AccessPoint {
        //    @display("p=143,350");
        //}
        SP2: StandardHost {
            @display("p=518,24;i=device/server");
        }
        Sw: EtherSwitch {
            @display("p=462,85");
        }
        lifecycleController: LifecycleController {
            @display("p=34,72");
        }
    connections:
        //ap.ethg++ <--> C <--> Edge1.ethg++; //edge1[0]
        Edge1.ethg++ <--> C <--> RG1.ethg++; //edge1[1] - RG1[0]
        Edge2.ethg++ <--> C <--> RG1.ethg++; //edge2[0] - RG1[1]
        Enoma.ethg++ <--> C <--> Core.ethg++; //Enoma[0] - Core[0]
        Sw.ethg++ <--> C <--> Core.ethg++; //SP1[0] - Core[1]
        RG1.ethg++ <--> C <--> Core.ethg++; //RG1[2] - Core[2]
        RG2.ethg++ <--> C <--> Core.ethg++; //RG2[0] - Core[3]
        RG1.ethg++ <--> C <--> RG2.ethg++; //RG1[3] - RG2[1]
        RG2.ethg++ <--> C <--> Edge3.ethg++; //RG2[2] - Edge3[0]
        Edge1.ethg++ <--> C <--> ue.ethg++; //edge1[1] - RG1[0]
        Sw.ethg++ <--> C <--> SP1.ethg++;
        Sw.ethg++ <--> C <--> SP2.ethg++;
}
