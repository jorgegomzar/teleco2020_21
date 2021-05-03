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

#include "Control_Dynamic_RWA.h"

Define_Module(Control_Dynamic_RWA);

int Control_Dynamic_RWA::numInitStages() const{return 2;}

void Control_Dynamic_RWA::initialize(int stage)
{
	cModule *c_modulo_estado;
	if(stage==1)
	{
		c_modulo_estado = getParentModule()->getParentModule()->getParentModule()->getSubmodule("estado");
		modulo_estado = check_and_cast<Estado *>(c_modulo_estado);

		num_nodos=(int)par("num_nodos");
		num_txrx_por_edge_router=(int)par("num_tx_por_edge_router");
		num_lng_ond=(int)par("num_lng_ond");
		num_enlaces = modulo_estado->num_enlaces;

		num_muestras=0;
	}
}

void Control_Dynamic_RWA::handleMessage(cMessage *msg)
{

	PeticionLightpath *mensaje_peticion;
	RutaYLong *ruta_y_long_encontrada;
	char estado_mostrar[10000];
	char auxiliar[100];
	char auxiliardos[500];
	int origen; //Nodo origen
	int destino; //Nodo destino
	int longitud_de_onda;

	int longitud_onda_proteccion;

	int i,j;


	for(i=0;i<modulo_estado->num_enlaces;i++)
	{
	    cDisplayString& dispStrcuatro = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("nodo",getSimulation()->getModule(modulo_estado->tabla_enlaces[i][1])->getIndex())->gate(modulo_estado->tabla_enlaces[i][3])->getDisplayString();
	    dispStrcuatro.parse("ls=black,1");
    }


	switch (msg->getKind())
	{

		case PETICION_LIGHTPATH:
		{
		    mensaje_peticion = check_and_cast<PeticionLightpath *>(msg);


			origen = mensaje_peticion->getNodo_origen();
			destino = mensaje_peticion->getNodo_destino();

			cDisplayString& dispStrdos = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("textodos")->getDisplayString();
		    sprintf(auxiliardos,"Petición %d->%d en proceso\n",origen,destino);
		    dispStrdos.setTagArg("t",0,auxiliardos);
		    dispStrdos.setTagArg("t",2,"black");

			send(mensaje_peticion,"out_rwa");

			break;

		}


		case RUTA_Y_LONG_ONDA:
		{
			ruta_y_long_encontrada = check_and_cast<RutaYLong *>(msg);

			longitud_de_onda=ruta_y_long_encontrada->getLongitud_onda();


			if(longitud_de_onda>=0)
			{

				num_muestras++;
				if(num_muestras>TRANSIENT_PERIOD)probabilidad_no_establecimiento.analizar(0);
				if( (probabilidad_no_establecimiento.convergio()) || (num_muestras>=(MAX_MUESTRAS+TRANSIENT_PERIOD)) )endSimulation();

				origen = ruta_y_long_encontrada->getNodo_origen();
				destino = ruta_y_long_encontrada->getNodo_destino();

				modulo_estado->tablatxrx[origen][0]--;
				modulo_estado->tablatxrx[destino][1]--;
//				ev << "Ruta " << ruta_y_long_encontrada->getRuta(0) << endl;
//				ev << "origen " << simulation.getModule(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(0)][1])->getIndex() << endl;
//				ev << "puerta " << modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(0)][3] << endl;
				//cDisplayString& dispStrtres = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("nodo",simulation.getModule(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(0)][1])->getIndex())->gate(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(0)][3])->getDisplayString();
                //dispStrtres.parse("ls=red");

				for(i=0;i<(int)ruta_y_long_encontrada->getRutaArraySize();i++)
				{
				    cDisplayString&dispStrtres = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("nodo",getSimulation()->getModule(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(i)][1])->getIndex())->gate(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta(i)][3])->getDisplayString();
				    dispStrtres.parse("ls=green,5");
				    sprintf(auxiliar,"W = %d",longitud_de_onda);
				    dispStrtres.setTagArg("t",0,auxiliar);
				    dispStrtres.setTagArg("t",3,"green");


					modulo_estado->estado[ruta_y_long_encontrada->getRuta(i)][longitud_de_onda]=1;
				}


				if(ruta_y_long_encontrada->getProteccion_activada())
				{
	                for(i=0;i<(int)ruta_y_long_encontrada->getRuta_proteccionArraySize();i++)
	                {
	                    cDisplayString&dispStrtres = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("nodo",getSimulation()->getModule(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta_proteccion(i)][1])->getIndex())->gate(modulo_estado->tabla_enlaces[ruta_y_long_encontrada->getRuta_proteccion(i)][3])->getDisplayString();
	                    dispStrtres.parse("ls=red,5");
	                    sprintf(auxiliar,"W = %d",ruta_y_long_encontrada->getLongitud_onda_proteccion());
	                    dispStrtres.setTagArg("t",0,auxiliar);
	                    dispStrtres.setTagArg("t",3,"red");


	                    modulo_estado->estado[ruta_y_long_encontrada->getRuta_proteccion(i)][ruta_y_long_encontrada->getLongitud_onda_proteccion()]=1;
	                }
				}
				ruta_y_long_encontrada->setKind(LIBERAR_LIGHTPATH);
				scheduleAt(simTime()+ruta_y_long_encontrada->getTiempo_servicio(),ruta_y_long_encontrada);

	            cDisplayString& dispStrdos = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("textodos")->getDisplayString();
	                sprintf(auxiliardos,"Petición %d->%d ESTABLECIDA\n",origen,destino);
	                dispStrdos.setTagArg("t",0,auxiliardos);
	                dispStrdos.setTagArg("t",2,"green3");

			}
			else
			{
                origen = ruta_y_long_encontrada->getNodo_origen();
                destino = ruta_y_long_encontrada->getNodo_destino();

                cDisplayString& dispStrdos = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("textodos")->getDisplayString();
                sprintf(auxiliardos,"Petición %d->%d BLOQUEADA\n",origen,destino);
                dispStrdos.setTagArg("t",0,auxiliardos);
                dispStrdos.setTagArg("t",2,"red");

				num_muestras++;
				if(num_muestras>TRANSIENT_PERIOD)probabilidad_no_establecimiento.analizar(1);
				if( (probabilidad_no_establecimiento.convergio()) || (num_muestras>=(MAX_MUESTRAS+TRANSIENT_PERIOD)) )endSimulation();

				delete(ruta_y_long_encontrada);
			}

			break;

		}
		case LIBERAR_LIGHTPATH:
		{
			ruta_y_long_encontrada = check_and_cast<RutaYLong *>(msg);

			origen = ruta_y_long_encontrada->getNodo_origen();
			destino = ruta_y_long_encontrada->getNodo_destino();
			longitud_de_onda=ruta_y_long_encontrada->getLongitud_onda();

            cDisplayString& dispStrdos = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("textodos")->getDisplayString();
            sprintf(auxiliardos,"Petición %d->%d liberada\n",origen,destino);
            dispStrdos.setTagArg("t",0,auxiliardos);
            dispStrdos.setTagArg("t",2,"black");

			for(i=0;i<(int)ruta_y_long_encontrada->getRutaArraySize();i++)
			{
				modulo_estado->estado[ruta_y_long_encontrada->getRuta(i)][longitud_de_onda]=0;
			}

            if(ruta_y_long_encontrada->getProteccion_activada())
            {
                for(i=0;i<(int)ruta_y_long_encontrada->getRuta_proteccionArraySize();i++)
                {
                    modulo_estado->estado[ruta_y_long_encontrada->getRuta_proteccion(i)][ruta_y_long_encontrada->getLongitud_onda_proteccion()]=0;
                }


            }
			modulo_estado->tablatxrx[origen][0]++;
			modulo_estado->tablatxrx[destino][1]++;


			delete(ruta_y_long_encontrada);

			break;
		}



	};



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
        sprintf(auxiliar,"%2d->%2d  ",getSimulation()->getModule(modulo_estado->tabla_enlaces[i][1])->getIndex(),getSimulation()->getModule(modulo_estado->tabla_enlaces[i][2])->getIndex());
        strcat(estado_mostrar,auxiliar);
        for(j=0;j<num_lng_ond;j++)
        {
             sprintf(auxiliar,"%4d",modulo_estado->estado[i][j]);
             strcat(estado_mostrar,auxiliar);
        }
        strcat(estado_mostrar,"\n");
    }

//      strcat(estado_mostrar,ev << tabla_enlaces[i][0] <<"\t"<< simulation.getModule(tabla_enlaces[i][1])->getFullName() <<"\t"<< simulation.getModule(tabla_enlaces[i][2])->getFullName() <<"\t"<< tabla_enlaces[i][3] << endl;



    cDisplayString& dispStr = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("texto")->getDisplayString();
    dispStr.setTagArg("t",0,estado_mostrar);



    for (i=0;i<num_nodos;i++)
    {
        cDisplayString& dispStrcinco = getParentModule()->getParentModule()->getParentModule()->getParentModule()->getSubmodule("nodo",i)->getDisplayString();
        dispStrcinco.insertTag("t");
        sprintf(auxiliar," %d / %d",modulo_estado->tablatxrx[i][0],modulo_estado->tablatxrx[i][1]);
        dispStrcinco.setTagArg("t",0,auxiliar);
        dispStrcinco.setTagArg("t",1,"r");
    }




}





void Control_Dynamic_RWA::finish()
{
	FILE *fichero_resultados;

	cModule *red_fisica = getParentModule()->getParentModule()->getParentModule()->getParentModule();

	fichero_resultados = fopen("./resultados/resultados.txt","a");
	//ev << ftell(fichero_resultados);

	if(ftell(fichero_resultados)==0)fprintf(fichero_resultados,"       Red\t    Num nodos\t Num Tx/Rx\t Num lng onda\t         Método RWA      \t Carga \t      Prob. bloqueo\t Inter confi\t Fecha y hora\n");
	fprintf(fichero_resultados,"%10s\t", red_fisica->getFullName());
	fprintf(fichero_resultados,"%10d\t", (int)par("num_nodos"));
	fprintf(fichero_resultados,"%8d\t", (int) par("num_tx_por_edge_router"));
    fprintf(fichero_resultados,"%10d\t", (int) par("num_lng_ond"));
	fprintf(fichero_resultados,"%30s\t", par("dynamic_RWA_algorithm").stringValue());
	fprintf(fichero_resultados,"%10f\t", (double)par("dynamic_load"));
	fprintf(fichero_resultados,"%10e\t", (double)probabilidad_no_establecimiento.valor_media());
	fprintf(fichero_resultados,"%10e\t", (double)probabilidad_no_establecimiento.desviacion());


	  time_t tiempo = time(0);
	  struct tm *tlocal = localtime(&tiempo);
	  char output[128];
	  strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
	  fprintf(fichero_resultados,"%s\n",output);

	fclose(fichero_resultados);
}
