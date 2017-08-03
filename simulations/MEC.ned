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

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.WirelessHost;
import inet.node.inet.AdhocHost;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.networklayer.configurator.ipv4.HostAutoConfigurator;
import ned.DatarateChannel;
import inet.node.inet.StandardHost;
import inet.node.wireless.AccessPoint;
import mec_sim.EdgeNode;
import inet.common.misc.ThruputMeteringChannel;
//import inet.networklayer.ipv4.IPv4ServiceTable;

network MEC
{
    parameters:
        int numHosts;
        **.mgmt.numChannels = 1;
        @display("bgb=559.70667,414.21997");
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
                @display("p=38,39");
        }
        ue: WirelessHost {
            @display("r=,,#707070;p=134,274");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xmldoc("config2.xml");
                addStaticRoutes = false;
                addDefaultRoutes = false;
                @display("p=103,24");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=28,190");
        }
        RG: EdgeNode {
            @display("p=234,152");
        }
        //        serviceTable: IPv4ServiceTable {
        //            parameters:
        //                @display("p=38,96;is=s");
        //                serviceConfig = xmldoc("service.xml");
        //        }
        ap: AccessPoint {
            @display("p=162,214");
        }
        SP1: StandardHost {
            @display("p=367,77;i=device/server");
        }
        SP2: StandardHost {
            @display("p=367,215;i=device/server");
        }
        Enoma: StandardHost {
            @display("p=234,24;i=device/server");
        }

    connections:
        SP1.ethg++ <--> C <--> RG.ethg++;
        ap.ethg++ <--> C <--> RG.ethg++;
        RG.ethg++ <--> C <--> SP2.ethg++;
        Enoma.ethg++ <--> C <--> RG.ethg++;
}
