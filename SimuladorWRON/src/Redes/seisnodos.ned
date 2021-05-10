package simuladorWRON.src.Redes;

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

//
// TODO auto-generated module
//

import simuladorWRON.src.CoreRouters.CoreRouter;

import simuladorWRON.src.NodoControl.NodoControl;
import simuladorWRON.src.Fuente.fuentePeticiones;
import simuladorWRON.src.Redes.sencillo.sencillo;


network SeisNodos 
{
    parameters:
        int num_nodos;
    


    	bool dynamic;

        int num_tx_por_edge_router;
        int num_lng_ond;
        double wavelength_bit_rate @unit(bps);
        double duracion_media_lightpath_dinamico;

        double dynamic_load;

        @display("bgb=80000,40000;bgs=0.075,km");


    submodules:


  usuarios[num_nodos]: fuentePeticiones {

            parameters:
                x;
                y;
                
                
                num_nodos = num_nodos;

                num_tx_por_edge_router = num_tx_por_edge_router;
                num_lng_ond = num_lng_ond;
                wavelength_bit_rate = wavelength_bit_rate; 
                dynamic_load = dynamic_load;
				duracion_media_lightpath_dinamico = duracion_media_lightpath_dinamico;

                 @display("i=block/source_s;p=0,0,exact,$x,$y;b=2500,2500");


            gates:
                out;


        }


        nodo[num_nodos]: CoreRouter {

            parameters:
                x;
                y;
            

                 @display("i=abstract/switch_s;p=0,0,exact,$x,$y;b=2500,2500");


            gates:
                in_a1;
                in_a2;
                in_a3;
                in_a4;
                in_a5;
                in_a6;
                in_a7;
                in_a8;
                in_fuente;

                out_a1;
                out_a2;
                out_a3;
                out_a4;
                out_a5;
                out_a6;
                out_a7;
                out_a8;

        }


  

        nodo_control: NodoControl {

            parameters:
                num_nodos = num_nodos;

                num_tx_por_edge_router = num_tx_por_edge_router;
                num_lng_ond = num_lng_ond;
                wavelength_bit_rate = wavelength_bit_rate; 
                dynamic_load = dynamic_load;


                @display("i=block/star;p=1466.6666,1586.6665;b=2500,2500");

        }

 	texto: sencillo {

            parameters:
             
                @display("p=60000,40000;b=10,10");

        }


	textodos: sencillo {

            parameters:
             
                @display("p=15000,40000;b=10,10");
	}


    connections allowunconnected:
        
            nodo[0].out_a1 --> {  datarate = wavelength_bit_rate; delay = 0.015s; } --> nodo[1].in_a1; //1
            nodo[0].in_a1 <-- {  datarate = wavelength_bit_rate; delay = 0.015s; } <-- nodo[1].out_a1;

            nodo[0].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[5].in_a1; //2
            nodo[0].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[5].out_a1;
            
            nodo[1].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[2].in_a1; //3
            nodo[1].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[2].out_a1;
            
            nodo[5].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[4].in_a1; //4
            nodo[5].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[4].out_a1;
            
            nodo[5].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[2].in_a2; //5
            nodo[5].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[2].out_a2;
            
            nodo[2].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[3].in_a1; //6
            nodo[2].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[3].out_a1;
            
            nodo[4].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.01s; } --> nodo[3].in_a2; //7
            nodo[4].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.01s; } <-- nodo[3].out_a2;

 			usuarios[0].out --> nodo[0].in_fuente; 
 			usuarios[1].out --> nodo[1].in_fuente; 
 			usuarios[2].out --> nodo[2].in_fuente; 
 			usuarios[3].out --> nodo[3].in_fuente; 
 			usuarios[4].out --> nodo[4].in_fuente; 
 			usuarios[5].out --> nodo[5].in_fuente; 
 
}
