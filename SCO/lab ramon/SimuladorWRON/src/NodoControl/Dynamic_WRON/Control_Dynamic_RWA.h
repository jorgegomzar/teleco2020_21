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


#define __CONTROL_DYNAMIC_RWA_H__


#define PETICION_LIGHTPATH 1
#define RUTA_Y_LONG_ONDA 2
#define LIBERAR_LIGHTPATH 100

#define TRANSIENT_PERIOD 500
#define MAX_MUESTRAS 1E7

#include <omnetpp.h>
#include <vector>
#include "../../PaquetesPropios/mipaquete_m.h"
#include "../../NodoControl/Estado.h"
#include "../../Analisis/analisis.h"

//using namespace std;
typedef std::vector<int> int_vector_t;
typedef std::vector<double> double_vector_t;
typedef std::vector< int_vector_t > int_matrix_t;
typedef std::vector< double_vector_t > double_matrix_t;


class Control_Dynamic_RWA : public cSimpleModule
{
	private:
		Estado *modulo_estado;

		int num_txrx_por_edge_router;
		int num_nodos;
		long num_muestras;
		int num_lng_ond;
		int num_enlaces;

		Analisis probabilidad_no_establecimiento;

  	public:
		int numInitStages() const;


	protected:
		virtual void initialize(int stage);
		virtual void handleMessage(cMessage *msg);
		virtual void finish();
};


