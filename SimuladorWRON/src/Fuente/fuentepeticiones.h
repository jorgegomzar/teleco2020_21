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

#define __FUENTEPETICIONES_H__


#define PETICION_LIGHTPATH 1

#define INTERRUPCION 100


#include <omnetpp.h>
#include "../PaquetesPropios/mipaquete_m.h"

using namespace omnetpp; //añadido por compatibilidad
/**
 * TODO - Generated class
 */
class fuentePeticiones : public cSimpleModule
{
	private:
		int num_nodos;
		double duracion_media_lightpath;
		double intervalo_medio_entre_peticiones;

		cRNG *rng_interrupcion;
		cRNG *rng_origen;
		cRNG *rng_destino;
		cRNG *rng_duracion_lightpath;


	public:
		int numInitStages() const;

	protected:
		virtual void initialize(int stage);
		virtual void handleMessage(cMessage *msg);
};

