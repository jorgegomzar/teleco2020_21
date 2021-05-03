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

#include "Aur_Exhastive.h"

Define_Module(Aur_Exhaustive);

int Aur_Exhaustive::numInitStages() const{return 2;}

void Aur_Exhaustive::initialize(int stage)
{
	cTopology::Node *nodo_auxiliar;

	cModule *c_modulo_estado;
	Estado *modulo_estado;

	int num_enlace_salida_nodo;
	int i;
	int j;
	int k;


	if(stage==1)
	{
		num_lng_ond=(int)par("num_lng_ond");
		num_nodos=(int)par("num_nodos");
		proteccionActivada=(bool)(getParentModule()->par("proteccion"));

		c_modulo_estado = getParentModule()->getParentModule()->getParentModule()->getSubmodule("estado");
		modulo_estado = check_and_cast<Estado *>(c_modulo_estado);

		// Se crea e inicia el grafo

		netTopology.extractByNedTypeName((cStringTokenizer("simuladorWRON.src.CoreRouters.CoreRouter").asVector()));


		enlaces_en_topologia.resize(modulo_estado->num_enlaces);
		num_enlaces = modulo_estado->num_enlaces;


		for(i=0;i<netTopology.getNumNodes();i++)
		{
			nodo_auxiliar=netTopology.getNode(i);
			num_enlace_salida_nodo=nodo_auxiliar->getNumOutLinks();


			for(j=0;j<num_enlace_salida_nodo;j++)
			{

				if(nodo_auxiliar->getLinkOut(j)->isEnabled())
				{
					for(k=0;k<modulo_estado->num_enlaces;k++)
					{
						if((nodo_auxiliar->getModule()->getId()==modulo_estado->tabla_enlaces[k][1])&&(nodo_auxiliar->getLinkOut(j)->getLocalGate()->getId()==modulo_estado->tabla_enlaces[k][3]))
						{
							enlaces_en_topologia[k]=nodo_auxiliar->getLinkOut(j);
						}
					}
					nodo_auxiliar->getLinkOut(j)->disable();
				}
			}
		}



//		for(i=0;i<num_enlaces;i++)
//		{
//
//			ev << enlaces_en_topologia[i]->getLocalGate()->getOwnerModule()->getFullName() << " , " << (simulation.getModule(modulo_estado->tabla_enlaces[i][1]))->getFullName() << "  (" << enlaces_en_topologia[i]->getLocalGateId() << " , " << modulo_estado->tabla_enlaces[i][3] << ")" << endl;
//		}


	}

}

void Aur_Exhaustive::handleMessage(cMessage *msg)
{
	int origen;
	int destino;
	int w;
	int i;
	int j;
	double distancia_minima=HUGE_VAL;
	int mejor_w=-1;

	cModule *red_fisica = getParentModule()->getParentModule()->getParentModule()->getParentModule();
	cModule *c_modulo_estado = getParentModule()->getParentModule()->getParentModule()->getSubmodule("estado");
	Estado *modulo_estado = check_and_cast<Estado *>(c_modulo_estado);

	cModule *modulo_auxiliar;
	cTopology::Node *origennod, *destinonod;
	RutaYLong *paquete_ruta_y_longonda;

	struct route_s
	{
		double longitud;
		std::vector<cTopology::LinkOut *> path;
	}
	rutas[num_lng_ond];


	switch (msg->getKind())
	{

        case PETICION_LIGHTPATH:
        {
                PeticionLightpath *mensaje_peticion = check_and_cast<PeticionLightpath *>(msg);

                origen = mensaje_peticion->getNodo_origen();
                destino = mensaje_peticion->getNodo_destino();


                for(w=0;w<num_lng_ond;w++)
                {

                    //habilitar enlaces
                    for(i=0;i<num_enlaces;i++)
                    {
                        if(modulo_estado->checkChannelAvailability(i,w)==true)
                        {
                            enlaces_en_topologia[i]->enable();
                        }
                    }


                    modulo_auxiliar = red_fisica->getSubmodule("nodo", origen );
                    assert( modulo_auxiliar != NULL );
                    origennod = netTopology.getNodeFor( modulo_auxiliar );
                    assert( origennod != NULL );

                    modulo_auxiliar = red_fisica->getSubmodule("nodo", destino );
                    assert( modulo_auxiliar != NULL );
                    destinonod = netTopology.getNodeFor( modulo_auxiliar );
                    assert( destinonod != NULL );

                    netTopology.calculateUnweightedSingleShortestPathsTo( destinonod );

                    rutas[w].longitud = origennod->getDistanceToTarget();

                    if(rutas[w].longitud<distancia_minima)
                    {
                        distancia_minima=rutas[w].longitud;
                        mejor_w=w;
                    }

                    if(origennod->getDistanceToTarget()!=HUGE_VAL)
                    {
                        rutas[w].path.resize( num_nodos );

                        j=0;

                        while(origennod!=destinonod)
                            {
                                rutas[w].path[j] = origennod->getPath(0);
                                j++;
                                origennod = origennod->getPath(0)-> getRemoteNode();
                            }

                    }

                    // Deshabilitar enlaces

                    for(i=0;i<num_enlaces;i++)
                    {
                        if(modulo_estado->checkChannelAvailability(i,w)==true)
                        {
                            enlaces_en_topologia[i]->disable();
                        }
                    }

                } //Para cada longitud de onda


                paquete_ruta_y_longonda = new RutaYLong("Paquete con Ruta y Longitud Onda",RUTA_Y_LONG_ONDA);
                paquete_ruta_y_longonda->setNodo_origen(origen);
                paquete_ruta_y_longonda->setNodo_destino(destino);
                paquete_ruta_y_longonda->setTiempo_servicio(mensaje_peticion->getTiempo_servicio());
                paquete_ruta_y_longonda->setLongitud_onda(mejor_w);

                if(mejor_w>=0)
                {
                    paquete_ruta_y_longonda->setRutaArraySize((unsigned int)rutas[mejor_w].longitud);

                    for(i=0;i<rutas[mejor_w].longitud;i++)
                    {
                        for(j=0;j<num_enlaces;j++)
                        {
                            if(rutas[mejor_w].path[i]==enlaces_en_topologia[j])
                            {
                                paquete_ruta_y_longonda->setRuta(i,j);
                                j=num_enlaces;
                            }
                        }
                    }
                }


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



