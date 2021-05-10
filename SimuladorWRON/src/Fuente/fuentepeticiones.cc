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

#include "fuentepeticiones.h"

Define_Module(fuentePeticiones);

int fuentePeticiones::numInitStages() const{return 2;}

void fuentePeticiones::initialize(int stage)
{
	double carga;
	double tasa;


	if(stage==1)
	{
		num_nodos = (int)par("num_nodos");
		carga = (double)par("dynamic_load");
		tasa = (double)par("wavelength_bit_rate");
		duracion_media_lightpath = (double)par("duracion_media_lightpath_dinamico");

		intervalo_medio_entre_peticiones = duracion_media_lightpath/((num_nodos-1)*carga);

		rng_interrupcion = getRNG(0);
		rng_origen = getRNG(1);
		rng_destino = getRNG(2);
		rng_duracion_lightpath = getRNG(3);

		if((bool)getParentModule()->par("dynamic")==true)
		{
		    cMessage *interrupcion;
		    interrupcion=new cMessage("Solicitud de Nuevo Lightpath",INTERRUPCION);
		    scheduleAt(simTime()+exponential(intervalo_medio_entre_peticiones,0),interrupcion);
		}
	}


}

void fuentePeticiones::handleMessage(cMessage *msg)
{
	int origen;
	int destino;
	double tiempo_servicio;

	switch (msg->getKind())
	{
		case INTERRUPCION:

			origen = this->getIndex();

			destino = origen + 1 + intuniform (0,num_nodos-2,2);
			if(destino >= num_nodos)destino-=num_nodos;

			tiempo_servicio = exponential (duracion_media_lightpath,3);

			PeticionLightpath *mensaje_peticion = new PeticionLightpath("Solicitud de Nuevo Lightpath",PETICION_LIGHTPATH);
			mensaje_peticion->setNodo_origen(origen);
			mensaje_peticion->setNodo_destino(destino);
			mensaje_peticion->setTiempo_servicio(tiempo_servicio);

			send(mensaje_peticion,"out");

			scheduleAt(simTime()+exponential(intervalo_medio_entre_peticiones,0),msg);

			break;

	};
}

