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

package inet.networklayer.ipv4;
import inet.networklayer.contract.IServiceTable;

//
// TODO auto-generated type
//
simple IPv4ServiceTable like IServiceTable
{
    parameters:
        string serviceTableModule;
        @display("i=block/table");
        xml serviceConfig = xmldoc("serviceConfig.xml");//default(xml("<config><edge-service hosts='Edge1' services='s1'/></config>"));
        xml serviceList = xmldoc("serviceList.xml");//default(xml("<config><edge-service service='s1' ip='5.5.5.5'/></config>"));
}

