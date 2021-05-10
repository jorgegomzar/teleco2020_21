///////////////////////////////////////////////////////////////////
// This software is copyrighted by Optical Communications Group. //
// University of Valladolid	(UVa)								 //
//																 //
// WRON simulator   											 //
// has been developed by Optical Communications Group.	 		 //
// University of Valladolid (UVa)		 						 //
// Contact e-mail: rduran@tel.uva.es,natalia.fernandez@tel.uva.es //
//																 //
// Escuela Técnica Superior de Ingenieros de Telecomunicación	 //
// Campus Miguel Delibes										 //
// Universidad de Valladolid									 //
// Paseo de Belén, 15											 //
// 47011 Valladolid, Spain										 //
//																 //
// This file is part of CHRON simulator, 						 //
// an optical network simulation tool							 //
// based on OMNeT++/OMNEST discrete-event simulation framework.  //
//																 //
// Authoring:													 //
// Natalia Fernández Sordo (natalia.fernandez@tel.uva.es)		 //
// Ramón J. Durán Barroso (rduran@tel.uva.es)					 //
// Ignacio de Miguel Jiménez (ignacio.miguel@tel.uva.es)		 //
///////////////////////////////////////////////////////////////////

package simuladorWRON.src.Redes;

import simuladorWRON.src.CoreRouters.CoreRouter;

import simuladorWRON.src.NodoControl.NodoControl;
import simuladorWRON.src.Fuente.fuentePeticiones;
import simuladorWRON.src.Redes.sencillo.sencillo;

//
//@brief This network corresponds to NSFNet Topology
//
network NSFNet
{
    parameters:

        double num_nodos;
    

    	bool semi_static;
    	bool dynamic;

        double num_tx_por_edge_router;
        double num_lng_ond;
        double wavelength_bit_rate @unit(bps);
        double duracion_media_lightpath_dinamico;

        double dynamic_load;


        @display("bgb=11626.666,7773.333;bgi=maps/usa,s,bgg 1000,2,grey95;bgs=0.075,km");


    submodules:


        nodo[num_nodos]: CoreRouter {

            @display("i=abstract/opticalswitch;p=500,0,exact,$x,$y;is=s");


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

                 @display("i=block/source_s;p=0,0,exact,$x,$y");


            gates:
                out;


        }


        nodo_control: NodoControl {

            parameters:
                num_nodos = num_nodos;

                num_tx_por_edge_router = num_tx_por_edge_router;
                num_lng_ond = num_lng_ond;
                wavelength_bit_rate = wavelength_bit_rate; 
                dynamic_load = dynamic_load;



                @display("i=block/star_l;p=1493.3333,6573.333;b=706.6666,613.3333");

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
        
        //Distances between nodes obtained from 
    	//S.Ghose et al. "Multihop Virtual Topology Design in WDM Optical Networks for Self-Similar Traffic"
    	//Photonic Network Communications, 10:2, 199–214, 2005
    	
            nodo[0].out_a1 --> {  datarate = wavelength_bit_rate; delay = 0.0055s;@display("ls=blue,2"); } --> nodo[1].in_a1; //1
            nodo[0].in_a1 <-- {  datarate = wavelength_bit_rate; delay = 0.0055s;@display("ls=blue,2"); } <-- nodo[1].out_a1;

//            nodo[0].out_a8 --> {  datarate = wavelength_bit_rate; delay = 0.0055s; @display("ls=blue,2"); } --> nodo[1].in_a8; //1
//            nodo[0].in_a8 <-- {  datarate = wavelength_bit_rate; delay = 0.0055s; @display("ls=blue,2"); } <-- nodo[1].out_a8;


            nodo[0].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.003s;@display("ls=blue,2"); } --> nodo[2].in_a1; //2
            nodo[0].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.003s;@display("ls=blue,2"); } <-- nodo[2].out_a1;

            nodo[0].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.005s;@display("ls=blue,2"); } --> nodo[3].in_a1; //3
            nodo[0].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.005s;@display("ls=blue,2"); } <-- nodo[3].out_a1;

            nodo[1].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.014s;@display("ls=blue,2"); } --> nodo[6].in_a2; //4
            nodo[1].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.014s;@display("ls=blue,2"); } <-- nodo[6].out_a2;

            nodo[1].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.008s;@display("ls=blue,2"); } --> nodo[2].in_a3; //5
            nodo[1].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.008s;@display("ls=blue,2"); } <-- nodo[2].out_a3;

            nodo[2].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.01s;@display("ls=blue,2"); } --> nodo[7].in_a1; //6
            nodo[2].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.01s;@display("ls=blue,2"); } <-- nodo[7].out_a1;

            nodo[3].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.003s;@display("ls=blue,2"); } --> nodo[4].in_a1; //7
            nodo[3].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.003s;@display("ls=blue,2"); } <-- nodo[4].out_a1;

            nodo[3].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.012s;@display("ls=blue,2"); } --> nodo[8].in_a1; //8
            nodo[3].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.012s;@display("ls=blue,2"); } <-- nodo[8].out_a1;

            nodo[4].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.0055s;@display("ls=blue,2"); } --> nodo[7].in_a2; //9
            nodo[4].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.0055s;@display("ls=blue,2"); } <-- nodo[7].out_a2;

            nodo[4].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.004s;@display("ls=blue,2"); } --> nodo[5].in_a1; //10
            nodo[4].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.004s;@display("ls=blue,2"); } <-- nodo[5].out_a1;

            nodo[5].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.0035s;@display("ls=blue,2"); } --> nodo[6].in_a1; //11
            nodo[5].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.0035s;@display("ls=blue,2"); } <-- nodo[6].out_a1;

            nodo[6].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.0035s;@display("ls=blue,2"); } --> nodo[9].in_a1; //12
            nodo[6].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.0035s;@display("ls=blue,2"); } <-- nodo[9].out_a1;

            nodo[7].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.01s;@display("ls=blue,2"); } --> nodo[12].in_a1; //13
            nodo[7].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.01s;@display("ls=blue,2"); } <-- nodo[12].out_a1;

            nodo[7].out_a4 --> {  datarate = wavelength_bit_rate; delay = 0.006s;@display("ls=blue,2"); } --> nodo[11].in_a1; //14
            nodo[7].in_a4 <-- {  datarate = wavelength_bit_rate; delay = 0.006s;@display("ls=blue,2"); } <-- nodo[11].out_a1;

            nodo[8].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.004s;@display("ls=blue,2"); } --> nodo[10].in_a1; //15
            nodo[8].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.004s;@display("ls=blue,2"); } <-- nodo[10].out_a1;

            nodo[8].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.005s;@display("ls=blue,2"); } --> nodo[13].in_a3; //16
            nodo[8].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.005s;@display("ls=blue,2"); } <-- nodo[13].out_a3;

            nodo[9].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } --> nodo[10].in_a2; //17
            nodo[9].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } <-- nodo[10].out_a2;

            nodo[9].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } --> nodo[13].in_a2; //18
            nodo[9].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } <-- nodo[13].out_a2;

            nodo[9].out_a4 --> {  datarate = wavelength_bit_rate; delay = 0.0045s;@display("ls=blue,2"); } --> nodo[11].in_a2; //19
            nodo[9].in_a4 <-- {  datarate = wavelength_bit_rate; delay = 0.0045s;@display("ls=blue,2"); } <-- nodo[11].out_a2;

            nodo[12].out_a2 --> {  datarate = wavelength_bit_rate; delay = 0.0015s;@display("ls=blue,2"); } --> nodo[13].in_a1; //20
            nodo[12].in_a2 <-- {  datarate = wavelength_bit_rate; delay = 0.0015s;@display("ls=blue,2"); } <-- nodo[13].out_a1;

            nodo[12].out_a3 --> {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } --> nodo[10].in_a3; //21
            nodo[12].in_a3 <-- {  datarate = wavelength_bit_rate; delay = 0.0025s;@display("ls=blue,2"); } <-- nodo[10].out_a3;


        

        for j=0..num_nodos-1 {
 			usuarios[j].out --> nodo[j].in_fuente; 
        }
 	

}
