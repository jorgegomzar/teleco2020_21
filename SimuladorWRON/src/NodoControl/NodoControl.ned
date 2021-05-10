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

package simuladorWRON.src.NodoControl;

import simuladorWRON.src.NodoControl.Dynamic_WRON.Dynamic_WRON;


//
// TODO auto-generated module
//


module NodoControl
{
    parameters:
        int num_nodos;


        int num_tx_por_edge_router;
        int num_lng_ond;

        double wavelength_bit_rate @unit(bps);
        double dynamic_load;


        @display("bgb=292,352,#aecaee,#5aa206,2;bgp=18,10;bgl=2");


    submodules:

        estado: Estado {

            parameters:
                num_nodos = num_nodos;


                num_lng_ond = num_lng_ond;
                num_tx_por_edge_router = num_tx_por_edge_router;

                @display("i=block/table2;p=97,45");

        }



        WRON_Dinamica: Dynamic_WRON {
            parameters:
                num_nodos = num_nodos;


                num_lng_ond = num_lng_ond;
                num_tx_por_edge_router = num_tx_por_edge_router;

                wavelength_bit_rate = wavelength_bit_rate;
                dynamic_load = dynamic_load;


                @display("p=97,151;b=144,30,,#32d258,#319c30");

        }

       
}
