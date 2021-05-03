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

package simuladorWRON.src.NodoControl.Dynamic_WRON.RwaAlgorithms;

import simuladorWRON.src.NodoControl.Dynamic_WRON.*;
//
// TODO auto-generated module
//
simple Aur_Exhaustive like Dynamic_RWA
{
        parameters:
           	int num_nodos;
        
        	int num_tx_por_edge_router;
        	int num_lng_ond;
        
        	double wavelength_bit_rate @unit(bps);
        	double dynamic_load;
        	
        	bool proteccion;

    gates:

        input in_control_rwa;
        output out_control_rwa;
        
       output out_proteccion;
        input in_proteccion;
}
