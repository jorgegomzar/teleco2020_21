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

#ifndef __ESTADO_H__
#define __ESTADO_H__

#include <omnetpp.h>
#include <vector>


//using namespace std;
typedef std::vector<int> int_vector_t;
typedef std::vector<double> double_vector_t;
typedef std::vector< int_vector_t > int_matrix_t;
typedef std::vector< double_vector_t > double_matrix_t;

using namespace omnetpp; //añadido por compatibilidad
/**
 * TODO - Generated class
 */
class Estado : public cSimpleModule
{

	private:

		int num_nodos;
		int num_lng_ond;
		int num_tx_por_edge_router;

        ///Topology Nodes
        std::vector<cTopology::Node *> topologyNodes;

        ///Object from cTopology
        cTopology netTopology;

        /// Matrix of double data with distances between nodes
        std::vector< std::vector < double > > distanceBetweenNodes;
        std::vector< std::vector < std::vector < std::vector < int > > > > fibresInShortestPaths;
  protected:
	  virtual void finish();
      void buildPathsTable();
  public:

	  int numInitStages() const;

	  double_matrix_t topologia_actual;
	  double_matrix_t topologia_logica;
	  double_matrix_t topologia_pasada;

	  int_matrix_t tx_usados;
	  int_matrix_t tx_pasado;
	  int_matrix_t tx_propuestos;

	  int numero_conexiones;
	  int numero_conexiones_actual;
	  int numero_conexiones_pasada;

	  int_matrix_t estado;
	  int num_enlaces;
	  int_matrix_t tabla_enlaces;

      std::vector<cTopology::LinkOut *> enlaces_en_topologia;
      std::vector< int_matrix_t > tabla_distancia;
	  int_matrix_t tabla_num_caminos;
	  std::vector< std::vector< int_matrix_t > > enlaces_caminos_fisicos;

	  double_matrix_t tiempos;
	  int_matrix_t tablatxrx;
	  int_matrix_t estado_tx;
	  int_matrix_t estado_rx;
      std::vector<cTopology::LinkOut *> fibresLinks;

      struct route_s
      {
          double length;
          std::vector<cTopology::Node*>node; //Save route nodes
          std::vector<cTopology::LinkOut *> path;
      }*track;
      int restoration(int,int, long int);

      bool checkChannelAvailability(int,int);
      bool checkRxAvailability(int);
      bool checkTxAvailability(int);
      int numPaths(int,int);
      int pathDistance(int,int,int);
      int linkInPath(int,int,int,int);


  protected:
      virtual void initialize(int stage);




      //Links down revisor
      void calculateRoutes(int,int);
      void backTracking(int , int , bool* , int );
      void connection();
      void translateNodesIntoLinks();
      void arrangeRoutes();
      int setNewLinks(std::vector <int>&,int,int,int,int);
      bool setLinks(int* ,int,int, int , int , int );
      int translateModulationToCodeInt(const char* );
      bool checkLinksDown(int);
      std::vector< std::vector <int> >  connections; //adjacent nodes
      std::vector< std::vector <int> >  routesMatrix,linksMatrix;
      std::vector <int> linksVector;
      std::vector <int> route,LPsAlreadyReleased;
};



#endif



