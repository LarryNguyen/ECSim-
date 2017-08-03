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

package mec_sim;

import inet.applications.udpapp.UDPEdgeApp;
import inet.examples.adhoc.hostautoconf.Host;
import inet.networklayer.ipv4.IPv4ServiceTable;
import inet.node.inet.Router;
import inet.transportlayer.contract.IUDP;
import inet.applications.contract.IUDPApp;

module EdgeNode extends Router
{
    parameters:
        int numUdpApps = default(0);
        
    submodules:
        udpApp[numUdpApps]: <> like IUDPApp {
            parameters:
                @display("p=574,231,row,60");
        }

        udpE: <udpType> like IUDP {
            @display("p=452,231");
        }
    connections:
        udpE.ipOut --> networkLayer.transportIn++;
        udpE.ipIn <-- networkLayer.transportOut++;

        for i=0..numUdpApps-1 {
            udpApp[i].udpOut --> udpE.appIn++;
            udpApp[i].udpIn <-- udpE.appOut++;
        }

}
