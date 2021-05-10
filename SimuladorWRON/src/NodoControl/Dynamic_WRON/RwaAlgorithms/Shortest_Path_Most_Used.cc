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

#include "Shortest_Path_Most_Used.h"

Define_Module(Shortest_Path_Most_Used);

int Shortest_Path_Most_Used::numInitStages() const{return 2;}

void Shortest_Path_Most_Used::initialize(int stage)
{


	if(stage==1)
	{
        //Número de longitudes de onda y nodos de la red.

		num_lng_ond=(int)par("num_lng_ond");
		num_nodos=(int)par("num_nodos");
        proteccionActivada=(bool)(getParentModule()->par("proteccion"));






	}
}

void Shortest_Path_Most_Used::handleMessage(cMessage *msg)
{
    //Acceso al módulo estado con toda la información de la red.

	cModule *c_modulo_estado = getParentModule()->getParentModule()->getParentModule()->getSubmodule("estado");
	Estado *modulo_estado = check_and_cast<Estado *>(c_modulo_estado);
    //Para entrar en los métodos del estado de la red hay que utilizar: modulo_estado->"Método"


    //Variables

	int origen;
	int destino;
	int w;
	int i;
	int j;
	int mejor_w=-1;
	int camino=-1;

	int orden_lng_ond[num_lng_ond];
	int auxiliar_lng_ond[num_lng_ond];

	bool libre;

    RutaYLong *paquete_ruta_y_longonda;


    switch (msg->getKind())
    {

        case PETICION_LIGHTPATH:
        {

            PeticionLightpath *mensaje_peticion = check_and_cast<PeticionLightpath *>(msg);

            origen = mensaje_peticion->getNodo_origen();
            destino = mensaje_peticion->getNodo_destino();




              //          paquete_ruta_y_longonda = new RutaYLong("Paquete con Ruta y Longitud Onda",RUTA_Y_LONG_ONDA);
              //          paquete_ruta_y_longonda->setNodo_origen(origen);
              //          paquete_ruta_y_longonda->setNodo_destino(destino);
              //          paquete_ruta_y_longonda->setTiempo_servicio(mensaje_peticion->getTiempo_servicio());
              //          paquete_ruta_y_longonda->setLongitud_onda(mejor_w);
              //          paquete_ruta_y_longonda->setRutaArraySize((unsigned int)rutas[mejor_w].longitud);
              //          paquete_ruta_y_longonda->setRuta(i,j);



                if((proteccionActivada==false)||(paquete_ruta_y_longonda->getLongitud_onda()<0))
                {
                    send(paquete_ruta_y_longonda,"out_control_rwa");
                }
                else
                {
                    paquete_ruta_y_longonda->setProteccion_activada(true);
                    send(paquete_ruta_y_longonda,"out_proteccion");

                }

                delete(mensaje_peticion);

                break;
        }

        case RUTA_Y_LONG_ONDA:
        {

            paquete_ruta_y_longonda=check_and_cast <RutaYLong*> (msg);

            if(paquete_ruta_y_longonda->getLongitud_onda_proteccion()<0)
            {
                paquete_ruta_y_longonda->setLongitud_onda(-1);
            }
            send(paquete_ruta_y_longonda,"out_control_rwa");

            break;
        }

    }
}

