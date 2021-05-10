//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without EVen the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "Estado.h"

Define_Module(Estado);

int Estado::numInitStages() const{return 1;}


void Estado::initialize(int stage)
{

    char estado_mostrar[10000];
    char auxiliar[100];
	int i,j,k; //indices
	int aux,auxdos;
	int identificador;

	int indice_enlace;

	//cTopology grafo;
	cModule * submod;
	cTopology::Node *nodo;

    cModule *modulo_auxiliar;
    cTopology::Node *nodo_auxiliar;
    cTopology::Node *origennod, *destinonod;
    int num_enlace_salida_nodo;


	if(stage==0)
	{
	    num_nodos=(int)par("num_nodos");
		num_lng_ond=(int)par("num_lng_ond");
		num_tx_por_edge_router=(int)par("num_tx_por_edge_router");


		netTopology.extractByNedTypeName((cStringTokenizer("simuladorWRON.src.CoreRouters.CoreRouter").asVector()));


		num_enlaces=0;

		for(i=0;i<num_nodos;i++)
		{
			submod = getParentModule()->getParentModule()->getSubmodule("nodo",i);
			nodo= netTopology.getNodeFor(submod);
			num_enlaces+= nodo->getNumOutLinks();
		}



		//num_enlaces=num_enlaces/num_lng_ond; //en realidad no tenemos un enlace para cada long de onda, sino que por el mismo

		EV << "Num enlaces " << num_enlaces << endl;


		tabla_enlaces.resize(num_enlaces); //inicializamos la tabla a cero

		for(i=0;i<(num_enlaces);i++)
		{
			tabla_enlaces[i].resize(4,0);
			tabla_enlaces[i][0]=i;
		}



		indice_enlace=0;


		EV<<"--------------------"<<endl;
		EV<<"--Tabla de enlaces-- "<<endl;
        EV<<"--------------------"<<endl;

		for(i=0;i<num_nodos;i++)
		{
			submod = getParentModule()->getParentModule()->getSubmodule("nodo",i);
			identificador=submod->getId(); //identificador para cada valor de i identifica a uno de los core routers
			nodo= netTopology.getNodeFor(submod);
			aux= nodo->getNumOutLinks(); // aux almacena el nmero de conexiones de salida que tiene cada core router

			for(j=0;j<aux;j++) // para cada una de las conexiones de salida
			{
				auxdos=nodo->getLinkOut(j)->getRemoteNode()->getModule()->getId(); // para cada nodo y cada una de sus conexiones de salida,
										   // auxdos identifica el nodo remoto al que est�conetado.

				if(nodo->getLinkOut(j)->getLocalGate()->getIndex()==0)
				{
					tabla_enlaces[indice_enlace][1] = identificador;
					tabla_enlaces[indice_enlace][2] = auxdos;
					tabla_enlaces[indice_enlace][3] = nodo->getLinkOut(j)->getLocalGate()->getId();
					EV<<indice_enlace<<" : "<<getSimulation()->getModule(tabla_enlaces[indice_enlace][1])->getIndex()<<" -- "<<getSimulation()->getModule(tabla_enlaces[indice_enlace][2])->getIndex()<<endl;
					indice_enlace++;
				} // para cada enlace conocemos el origen y el destino del mismo almacenado en tabla_enlaces
			}
		}

       for(i=0;i<num_enlaces;i++) EV << tabla_enlaces[i][0] <<"\t"<< getSimulation()->getModule(tabla_enlaces[i][1])->getFullName() <<"\t"<< getSimulation()->getModule(tabla_enlaces[i][2])->getFullName() <<"\t"<< tabla_enlaces[i][3] << endl;

//		 buildPathsTable();  ///Construction of Network Shortest Paths


	        // Inicializamos la tabla de estado
	        estado.resize(num_enlaces);
	        for(i=0;i<(signed)estado.size();i++)estado[i].resize(num_lng_ond,0);


		// Inicializamos la tabla de tiempos de ocupacion
		tiempos.resize(num_enlaces);
		for(i=0;i<(signed)tiempos.size();i++)tiempos[i].resize(num_lng_ond, 0.0);


		tablatxrx.resize(num_nodos);
		for(i=0;i<(signed)tablatxrx.size();i++)tablatxrx[i].resize(2,num_tx_por_edge_router);

//		sprintf(estado_mostrar,"\n");

		sprintf(estado_mostrar,"ESTADO DE LOS CANALES\n");
		strcat(estado_mostrar,"      \t");

		for(i=0;i<num_lng_ond;i++)
		{
		    sprintf(auxiliar,"%4d",i);
		    strcat(estado_mostrar,auxiliar);
		}
		strcat(estado_mostrar,"\n\n");

		for(i=0;i<num_enlaces;i++)
		{
		    sprintf(auxiliar,"%2d->%2d  ",getSimulation()->getModule(tabla_enlaces[i][1])->getIndex(),getSimulation()->getModule(tabla_enlaces[i][2])->getIndex());
		    strcat(estado_mostrar,auxiliar);
		    for(j=0;j<num_lng_ond;j++)
		    {
		         sprintf(auxiliar,"%4d",estado[i][j]);
		         strcat(estado_mostrar,auxiliar);
		    }
		    strcat(estado_mostrar,"\n");
		}

//		strcat(estado_mostrar,EV << tabla_enlaces[i][0] <<"\t"<< simulation.getModule(tabla_enlaces[i][1])->getFullName() <<"\t"<< simulation.getModule(tabla_enlaces[i][2])->getFullName() <<"\t"<< tabla_enlaces[i][3] << endl;



		cDisplayString& dispStr = getParentModule()->getParentModule()->getSubmodule("texto")->getDisplayString();
		dispStr.insertTag("t");
		dispStr.setTagArg("t",0,estado_mostrar);

		cDisplayString& dispStrdos  = getParentModule()->getParentModule()->getSubmodule("textodos")->getDisplayString();
        dispStrdos.insertTag("t");
        dispStrdos.setTagArg("t",0," ");



        for (i=0;i<num_nodos;i++)
        {
            cDisplayString& dispStrtres = getParentModule()->getParentModule()->getSubmodule("nodo",i)->getDisplayString();
            dispStrtres.insertTag("t");
            sprintf(auxiliar," %d / %d",tablatxrx[i][0],tablatxrx[i][1]);
            dispStrtres.setTagArg("t",0,auxiliar);
            dispStrtres.setTagArg("t",1,"r");
        }

        enlaces_en_topologia.resize(num_enlaces);


            for(i=0;i<netTopology.getNumNodes();i++)
            {
                nodo_auxiliar=netTopology.getNode(i);
                num_enlace_salida_nodo=nodo_auxiliar->getNumOutLinks();


                for(j=0;j<num_enlace_salida_nodo;j++)
                {

                    if(nodo_auxiliar->getLinkOut(j)->isEnabled())
                    {
                        for(k=0;k<num_enlaces;k++)
                        {
                            if((nodo_auxiliar->getModule()->getId()==tabla_enlaces[k][1])&&(nodo_auxiliar->getLinkOut(j)->getLocalGate()->getId()==tabla_enlaces[k][3]))
                            {
                                enlaces_en_topologia[k]=nodo_auxiliar->getLinkOut(j);
                            }
                        }
                        nodo_auxiliar->getLinkOut(j)->disable();
                    }
                }
            }


            tabla_distancia.resize(num_nodos);
            for (i=0;i<(signed)tabla_distancia.size();i++)tabla_distancia[i].resize(num_nodos);

            tabla_num_caminos.resize(num_nodos);
            for (i=0;i<(signed)tabla_num_caminos.size();i++)tabla_num_caminos[i].resize(num_nodos);

            for (i=0;i<num_nodos;i++)
            {
                for(j=0;j<num_nodos;j++)
                {
                    tabla_num_caminos[i][j]=0;
                }
            }

            enlaces_caminos_fisicos.resize(num_nodos);
            for (i=0;i<(signed)enlaces_caminos_fisicos.size();i++)enlaces_caminos_fisicos[i].resize(num_nodos);


            for(i=0;i<num_enlaces;i++)
            {
                enlaces_en_topologia[i]->enable();
            }


//
//
//            for(j=0;j<num_nodos;j++)
//            {
//
//                modulo_auxiliar = getParentModule()->getParentModule()->getSubmodule("nodo",j);
//                destinonod= netTopology.getNodeFor(modulo_auxiliar);
//
//                netTopology.calculateUnweightedSingleShortestPathsTo( destinonod );
//
//                for(i=0;i<num_nodos;i++)
//                {
//                    modulo_auxiliar = getParentModule()->getParentModule()->getSubmodule("nodo",i);
//                    origennod= netTopology.getNodeFor(modulo_auxiliar);
//
//
//                    tabla_num_caminos[i][j]=(int)origennod->getNumPaths();
//                    if(i!=j)tabla_distancia[i][j].resize(tabla_num_caminos[i][j]);
//                    else tabla_distancia[i][j].resize(1);
//                    tabla_distancia[i][j][0]=(int)origennod->getDistanceToTarget();
////
////                    if( (tabla_distancia[i][j][0]>0) && (tabla_distancia[i][j][0]!=HUGE_VAL) )
////                    {
////                        enlaces_caminos_fisicos[i][j].resize((int)origennod->getNumPaths());
////
////                        for(k=0;k<(int)origennod->getNumPaths();k++)
////                        {
////                            enlaces_caminos_fisicos[i][j][k].resize((int)tabla_distancia[i][j][0],-1);
////
////                            nodo_auxiliar=origennod;
////
////                            indice=0;
////                            while(nodo_auxiliar!=destinonod)
////                            {
////                                for(m=0;m<num_enlaces;m++)
////                                {
////                                    if(nodo_auxiliar->getPath(k)==enlaces_en_topologia[m])
////                                    {
////                                        enlaces_caminos_fisicos[i][j][k][indice]=m;
////                                        m=num_enlaces;
////                                    }
////                                }
////
////                                    indice++;
////                                    nodo_auxiliar = nodo_auxiliar->getPath(0)-> getRemoteNode();
////                            }
////
////
////                        }
////
////
////                    }
//
//                }
//            }

            //Precalculation of paths between nodes
            for(i=0; i<num_nodos; i++)
            {
                for(j=0; j<num_nodos; j++)
                {
                    if(i!=j)
                    {
                        calculateRoutes(i,j);
                        enlaces_caminos_fisicos[i][j].resize(linksMatrix.size());

                        tabla_num_caminos[i][j]=(int)enlaces_caminos_fisicos[i][j].size();
                        tabla_distancia[i][j].resize(tabla_num_caminos[i][j]);

                        for(k=0; k<linksMatrix.size(); k++)
                        {
                            tabla_distancia[i][j][k]=(int)linksMatrix[k].size();

                            for(int l=0; l<linksMatrix[k].size(); l++)
                            {
                                enlaces_caminos_fisicos[i][j][k].push_back(linksMatrix[k][l]);
                            }
                        }
                    }
                    else tabla_distancia[i][j].resize(1);
                }
            }

//
//            EV.printf("\nDISTANCIAS_ESTADO\n\n");
//
//            for(i=0;i<num_nodos;i++)
//            {
//                for(j=0;j<num_nodos;j++)
//                {
//                    EV.printf("%2d\t",tabla_distancia[i][j][0]);
//                }
//                EV.printf("\n");
//            }
//
//
//
//            EV.printf("\nCAMINOS_ESTADO\n\n");
//
//            for(i=0;i<num_nodos;i++)
//            {
//                    for(j=0;j<num_nodos;j++)
//                    {
//
//                            EV.printf("%2d\t",tabla_num_caminos[i][j]);
//                    }
//                    EV.printf("\n");
//            }
















	}
}

void Estado::finish()
{
	// TODO - Generated method body
}


int Estado::numPaths(int source,int destination)
{
    return (tabla_num_caminos[source][destination]);
}

int Estado::pathDistance(int source,int destination,int path)
{
    return (tabla_distancia[source][destination][path]);
}

int Estado::linkInPath(int source,int destination,int path, int hop)
{
    return (enlaces_caminos_fisicos[source][destination][path][hop]);
}

bool Estado::checkChannelAvailability(int link,int wavelength)
{
    if(estado[link][wavelength]==0)return(true);
    else return (false);

}

bool Estado::checkTxAvailability(int node)
{
    if(tablatxrx[node][0]>0)return(true);
    else return (false);

}

bool Estado::checkRxAvailability(int node)
{
    if(tablatxrx[node][1]>0)return(true);
    else return (false);

}






void Estado::buildPathsTable()
{
    int i,j,k,l,m,index;
    cModule *physicalNet = getParentModule()->getParentModule();
    cModule *auxiliarModule;
    cTopology::Node *auxiliarNode;
    cTopology::Node *sourceNode, *destinationNode;

    int numLinkOutputNode;
    cTopology grafo;

    // nedTopology is a graph of the network

    netTopology.extractByNedTypeName((cStringTokenizer("simuladorWRON.src.CoreRouters.CoreRouter").asVector()));
    fibresLinks.resize(num_enlaces);
    topologyNodes.resize(num_enlaces);
    // Fibres_links table is completed with links in the graph nedTopology
    for(i=0;i<grafo.getNumNodes();i++)
    {
        auxiliarNode=grafo.getNode(i);
        numLinkOutputNode=auxiliarNode->getNumOutLinks();


        for(j=0;j<numLinkOutputNode;j++)
        {

            if(auxiliarNode->getLinkOut(j)->isEnabled())
            {
                for(k=0;k<num_enlaces;k++)
                {
                    if((auxiliarNode->getModule()->getId()==tabla_enlaces[k][1])&&(auxiliarNode->getLinkOut(j)->getLocalGate()->getId()==tabla_enlaces[k][3]))
                    {
                        fibresLinks[k]=auxiliarNode->getLinkOut(j);
                        topologyNodes[k]=auxiliarNode;
                    }
                }
                auxiliarNode->getLinkOut(j)->disable();
            }
        }
    }


    // The distance between nodes table and the number of paths is initialized
            distanceBetweenNodes.resize(netTopology.getNumNodes());
            for (i=0;i<(signed)distanceBetweenNodes.size();i++)distanceBetweenNodes[i].resize(netTopology.getNumNodes());

            for (i=0;i<netTopology.getNumNodes();i++)
            {
                for(j=0;j<netTopology.getNumNodes();j++)
                {
                    distanceBetweenNodes[i][j]=HUGE_VAL;
                }
            }

            // EVery fibre link in the graph is enabled to discover the shortest paths
            for(i=0;i<num_enlaces;i++)
            {
                fibresLinks[i]->enable();
            }

            // The fibres that should be transverse to follow the shortest paths between each pair of nodes is saved in the table
            // fibres_in_shortest_paths[num_edge_router(source)][num_edge_router(destination)][num_shortest_paths][distance]
            for(j=0;j<netTopology.getNumNodes();j++)
            {
                auxiliarModule = physicalNet->getSubmodule("nodo",j);
                destinationNode= netTopology.getNodeFor(auxiliarModule);

                netTopology.calculateUnweightedSingleShortestPathsTo( destinationNode );

                for(i=0;i<netTopology.getNumNodes();i++)
                {
                    auxiliarModule = physicalNet->getSubmodule("nodo",i);
                    sourceNode= netTopology.getNodeFor(auxiliarModule);

                    distanceBetweenNodes[i][j]=(int)sourceNode->getDistanceToTarget();

                }

            }
            for(i=0;i<num_enlaces;i++)
            {
                fibresLinks[i]->disable();
            }







    //Precalculation of paths between nodes
    fibresInShortestPaths.resize(num_nodos);
    for(i=0; i<num_nodos; i++)
    {
        fibresInShortestPaths[i].resize(num_nodos);
        for(j=0; j<num_nodos; j++)
        {
            if(i!=j)
            {
                calculateRoutes(i,j);
                fibresInShortestPaths[i][j].resize(linksMatrix.size());
                for(k=0; k<linksMatrix.size(); k++)
                {
                    for(l=0; l<linksMatrix[k].size(); l++)
                    {
                        fibresInShortestPaths[i][j][k].push_back(linksMatrix[k][l]);
                    }
                }
            }
        }
    }

}



void Estado::calculateRoutes(int source, int destination)
{
    int i,j;
    cModule *physicalNet = getParentModule()->getParentModule();


    route.clear();
    routesMatrix.clear();


    //CONNECTIONS BETWEEN NODES
    connection();

    //ROUTES CALCULATION: NODES
    bool usedNodes[num_nodos];//Vector of nodes to calculate routes
    for(i=0;i<num_nodos;i++) usedNodes[i]=false;//EVery nodes is not being used

    route.push_back(source);

    if(source!=destination)
    {
        backTracking(source,destination,usedNodes,source);
        arrangeRoutes();
        translateNodesIntoLinks();
    }

//    printf("\n");
//
//      for(i=0;i<linksMatrix.size();i++)
//      {
//          for(j=0;j<linksMatrix[i].size();j++)
//          {
//              printf("%d\t",linksMatrix[i][j]);
//          }
//          printf("\n");
//      }

}

void Estado::backTracking(int source, int destination, bool usedNodes[], int currentNode)
{
    int i;
    usedNodes[currentNode]=true;


    for(i=0;i<num_nodos;i++)
    {
        if (usedNodes[i]==false )
        {

            usedNodes[i]=true;
            route.push_back(i);

            if(connections[currentNode][i]==1)
            {
                if(i==destination)
                {
                    routesMatrix.push_back(route);
                }
                else
                {
                    backTracking(source,destination, usedNodes,i); //FUNCION
                }
            }

            usedNodes[i]=false;
            route.pop_back();

        }

    }
}

void Estado::connection()
{
    int i;


    //Connections Matrix Creation
    connections.clear();
    connections.resize(num_nodos);

    for(i=0;i<num_nodos;i++) connections[i].resize(num_nodos,0);

    for(i=0;i<num_enlaces;i++)
    {

            connections[getSimulation()->getModule(tabla_enlaces[i][1])->getIndex()][getSimulation()->getModule(tabla_enlaces[i][2])->getIndex()]=1;

           // std::cout<<"Conexiones :"<<simulation.getModule(tabla_enlaces[i][1])->getIndex()<<" - "<<simulation.getModule(tabla_enlaces[i][2])->getIndex()<<endl;
    }
}

void Estado::translateNodesIntoLinks()
{
    linksMatrix.clear();
    for( int r=0;r<(signed int)routesMatrix.size();r++)
        {
           linksVector.clear();

            for (int l=0;l<(signed int)routesMatrix[r].size()-1;l++)
            {
                for (int m=0;m<num_enlaces;m++)
                {
                    if (routesMatrix[r][l]==getSimulation()->getModule((int)tabla_enlaces[m][1])->getIndex() && routesMatrix[r][l+1]==getSimulation()->getModule((int)tabla_enlaces[m][2])->getIndex())
                    {
                        linksVector.push_back((int)tabla_enlaces[m][0]);
                        m=num_enlaces;
                    }
                }
            }
            linksMatrix.push_back(linksVector);
        }
}

void Estado::arrangeRoutes()
{
    std::vector <int> vectorAux;
    vectorAux.clear();
    int k,l;

    //PUT ROUTES IN ORDER: FROM SHORTEST TO LONGUEST
    for (int m=0;m<routesMatrix.size()-1;m++)
    {
        for (k=m+1;k<routesMatrix.size();k++)
        {
            if(routesMatrix[k].size()< routesMatrix[m].size())
            {
                for(l=0;l<(signed int)routesMatrix[k].size();l++)  vectorAux.push_back(routesMatrix[k][l]);
                //  enlaces_caminos_fisicos[i][j][k].resize(enlaces_caminos_fisicos[i][j][m].size());

                routesMatrix[k].resize(routesMatrix[m].size());
                for(l=0;l<(signed int)routesMatrix[m].size();l++) routesMatrix[k][l]=routesMatrix[m][l];

                //  enlaces_caminos_fisicos[i][j][m].resize(vectorAux.size());
                routesMatrix[m].resize(vectorAux.size());
                for(l=0;l<(signed int)vectorAux.size();l++) routesMatrix[m][l]=vectorAux[l];
            }
            vectorAux.clear();
        }
    }
}



