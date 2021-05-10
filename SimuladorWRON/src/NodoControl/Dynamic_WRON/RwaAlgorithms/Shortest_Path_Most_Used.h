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

#ifndef __SHORTEST_PATH_MOST_USED_H__
#define __SHORTEST_PATH_MOST_USED_H__


#define PETICION_LIGHTPATH 1
#define RUTA_Y_LONG_ONDA 2


#include <omnetpp.h>
#include <vector>
#include <time.h>
#include <signal.h>
#include "../../../PaquetesPropios/mipaquete_m.h"
#include "../../../NodoControl/Estado.h"

//using namespace std;
typedef std::vector<int> int_vector_t;
typedef std::vector<double> double_vector_t;
typedef std::vector< int_vector_t > int_matrix_t;
typedef std::vector< double_vector_t > double_matrix_t;


class Shortest_Path_Most_Used : public cSimpleModule
{
	private:

		int num_lng_ond;
		int num_nodos;
		bool proteccionActivada;



  	public:
		int numInitStages() const;


	protected:
		virtual void initialize(int stage);
		virtual void handleMessage(cMessage *msg);

};

#endif
