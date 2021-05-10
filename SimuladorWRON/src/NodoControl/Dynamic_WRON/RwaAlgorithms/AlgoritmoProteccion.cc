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

#include "AlgoritmoProteccion.h"

Define_Module(AlgoritmoProteccion);


int AlgoritmoProteccion::numInitStages() const{return 2;}

void AlgoritmoProteccion::initialize(int stage)
{

    if(stage==1)
    {
        //Número de longitudes de onda y nodos de la red.

        num_lng_ond=(int)par("num_lng_ond");
        cModule * c_modulo_estado;
        c_modulo_estado = getParentModule()->getParentModule()->getParentModule()->getSubmodule("estado");
        modulo_estado = check_and_cast<Estado *>(c_modulo_estado);

    }
}

void AlgoritmoProteccion::handleMessage(cMessage *msg)
{

    RutaYLong *ruta_y_long_encontrada;
    int longitud_de_onda_protec=-1;
    int origen;
    int destino;
    int caminoProteccion;


    switch (msg->getKind())
    {
        case  RUTA_Y_LONG_ONDA:
        {
            ruta_y_long_encontrada=check_and_cast<RutaYLong*>(msg);
            origen = ruta_y_long_encontrada->getNodo_origen();
            destino = ruta_y_long_encontrada->getNodo_destino();


            for(int i=0; i<ruta_y_long_encontrada->getRutaArraySize();i++)
            {

                      EV << ruta_y_long_encontrada->getRuta(i) << " ";

            }

                EV << endl;


            ruta_y_long_encontrada->setLongitud_onda_proteccion(longitud_de_onda_protec);
            //ruta_y_long_encontrada->setRuta_proteccionArraySize(modulo_estado->pathDistance(origen,destino,caminoProteccion));
            //ruta_y_long_encontrada->setRuta_proteccion(i,modulo_estado->linkInPath(origen,destino,caminoProteccion,i));


            send(ruta_y_long_encontrada,"out_proteccion");

            break;
        }
    }
}
