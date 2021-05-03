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

package simuladorWRON.src.NodoControl.Dynamic_WRON;

import simuladorWRON.src.NodoControl.Dynamic_WRON.RwaAlgorithms.*;
//
// TODO auto-generated module
//
module Dynamic_WRON_Control
{
    parameters:
        int num_nodos;


        int num_tx_por_edge_router;
        int num_lng_ond;

        string dynamic_RWA_algorithm;

        double wavelength_bit_rate @unit(bps);
        double dynamic_load;

        string dynamic_RWA_algorithm_proteccion;

        bool proteccion;

        @display("bgb=412,260,#aecaee,#5aa206,2;bgp=26,10");
    gates:
        input in;


    submodules:

        Control_RWA_dinamico: Control_Dynamic_RWA { //

            parameters:
                num_nodos = num_nodos;


                num_lng_ond = num_lng_ond;
                num_tx_por_edge_router = num_tx_por_edge_router;

                wavelength_bit_rate = wavelength_bit_rate;
                dynamic_load = dynamic_load;

                dynamic_RWA_algorithm = dynamic_RWA_algorithm;

                @display("i=block/cogwheel;p=120,130;b=32,30");

        }



        Metodo_RWA_dinamico: <dynamic_RWA_algorithm> like Dynamic_RWA { //

            parameters:
                num_nodos = num_nodos;
				proteccion=proteccion;

                num_lng_ond = num_lng_ond;
                num_tx_por_edge_router = num_tx_por_edge_router;

                wavelength_bit_rate = wavelength_bit_rate;
                dynamic_load = dynamic_load;

                @display("i=block/wheelbarrow;p=120,214;b=32,30");

        }



        Metodo_RWA_Proteccion: <dynamic_RWA_algorithm_proteccion> like Dynamic_RWA { //

            parameters:
                num_nodos = num_nodos;

				proteccion=proteccion;

                num_lng_ond = num_lng_ond;
                num_tx_por_edge_router = num_tx_por_edge_router;

                wavelength_bit_rate = wavelength_bit_rate;
                dynamic_load = dynamic_load;

                @display("i=block/wheelbarrow;p=304,214;b=32,30");

        }


    connections allowunconnected:

        in --> Control_RWA_dinamico.in;
        Control_RWA_dinamico.out_rwa --> Metodo_RWA_dinamico.in_control_rwa;
        Control_RWA_dinamico.in_rwa <-- Metodo_RWA_dinamico.out_control_rwa;
        
        Metodo_RWA_dinamico.out_proteccion --> Metodo_RWA_Proteccion.in_proteccion;
        Metodo_RWA_Proteccion.out_proteccion --> Metodo_RWA_dinamico.in_proteccion;
}
