/***********************************************************/
//
// Archivo:   analisis.cpp
// Programa:
// Objetivo:  Analisis de simulaciones
// Autores:	  Ignacio de Miguel Jimenez
//			  David Rodriguez Alfayate
// Version:   1.1
//            21-Nov-00
// Variaciones: Solucionado un bug. Si se enviaban todos los
// datos iguales, ej: 20, 20, 20, ... la media no salía 20.
// ahora ya está solucionado. (I. de Miguel)
/***********************************************************/

#include "analisis.h"

Analisis::Analisis()
{
	tam_lote[PAR]=3;
	tam_lote[IMPAR]=2;
	converge=0;
	Max_muestras[PAR]=1200;
	Max_muestras[IMPAR]=800;
	muestras[PAR]=0;
	muestras[IMPAR]=0;
	pos_lote[PAR]=0;
	pos_lote[IMPAR]=0;
	medias[PAR][0]=0;
	medias[IMPAR][0]=0;
	lote[PAR]=lote[IMPAR]=0;
	media_total=0;
	numerador_sy2=0;
	iter=0;
	finbloque=0;
}
	
// Esta funcion implementa el analisis simultaneo (+ o -) de las
// muestras que se van recogiendo.
bool Analisis::analizar(const long double &elem)
{
	// elem es el elemento a analizar.
	// Lo que tenemos que hacer es simplemente calcular las medias
	// correspondientes a las iteraciones pares y las impares
	bool iteracion_finalizada=0;
	long double rohatold;
	int fin;
	// Ponemos finbloque a 0, en simulacion sabra lo que hay que hacer.
	finbloque=0;
	medias[PAR][lote[PAR]]+=elem;
	medias[IMPAR][lote[IMPAR]]+=elem;
	pos_lote[PAR]+=1;
	pos_lote[IMPAR]+=1;
	// Verificamos ahora si hemos completado algun lote.
	if(pos_lote[PAR]==tam_lote[PAR]) {
		// Dividimos por el tamaño del lote:
		medias[PAR][lote[PAR]]/=tam_lote[PAR];
		// Incrementamos el lote, (en una unidad)
		lote[PAR]+=1;
		pos_lote[PAR]=0;
		if(lote[PAR]<NUM_LOTES) medias[PAR][lote[PAR]]=0; // Ponemos este elemento a 0.
	}
	if(pos_lote[IMPAR]==tam_lote[IMPAR]) {
		medias[IMPAR][lote[IMPAR]]/=tam_lote[IMPAR];
		lote[IMPAR]+=1;
		pos_lote[IMPAR]=0;
		if(lote[IMPAR]<NUM_LOTES) medias[IMPAR][lote[IMPAR]]=0;
	}
	muestras[PAR]+=1;
	muestras[IMPAR]+=1;

	// Verificamos si hemos llegado al numero máximo de muestras
	// que correspondian al bloque que estamos analizando.
	if(muestras[PAR]==Max_muestras[PAR]) {
		// Indicamos que se ha producido un fin de lote. Para que
		// se tomen soluciones en el simulador:
		finbloque=1;
		iter++;
		calcular_rohat(PAR);
		// El numero de muestras en la siguiente iteracion par es el
		// doble del actual:
		Max_muestras[PAR]*=2;
		tam_lote[PAR]=Max_muestras[PAR]/NUM_LOTES;
		calcular_medias(PAR); // Comentario 1. /* <1> */
		// Tenemos que dividir por 2 el lote en que nos encontramos
		lote[PAR]/=2;
		medias[PAR][lote[PAR]]=0;
		// Vamos a comprobar el valor calculado de la correlacion.
		if(rohat<=0) {
			// Si estamos por debajo del umbral de confianza todo OK
			if(chequear_gamma()) {
				fin=1;
			}
			else fin=0;
		}
		else {
			if(0<rohat && rohat<UMBRAL) {
				// Tenemos que reorganizar el array de medias, la primera
				// mitad del array debe contener medias de 2*l muestras
				// por su parte la segunda mitad es indiferente.
				/* <1> */
				// Pero por otra parte esta operacion hay que hacerla para
				// el siguiente bloque par, por esto la hacemos al principio
				// de la comprobacion y ganamos tiempo. Comentario 1

				// Lo unico que haremos sera entonces calcular la correlacion
				rohatold=rohat;	
				calcular_rohat(PAR,MITAD); // Pero solo de la primera mitad de
										   // las medias.
				if(rohat<rohatold && chequear_gamma()) {
					// Umbral de confianza, hemos acabado la tarea.
					fin=1;
				}
				else fin=0;
			}
			else fin=0;
		}
		cout << "Iteracion: " << iter << "\n";
		cout << "   -> Resultado: "; resultado(); cout << "\n";		// Tenemos que calcular la funcion de autocorrelacion.
        iteracion_finalizada=1;
		// Si fin vale 1, hemos acabado la tarea con lo cual ponemos el
		// parametro converge a 1. y volvemos al programa de llamada.
		if(fin) {
			converge=1;
			return iteracion_finalizada;
		}
	}
	// Ahora toca realizar exactamente lo mismo pero en esta ocasion
	// para la iteracion IMPAR
	if(muestras[IMPAR]==Max_muestras[IMPAR]) {
		finbloque=1;
		iter++;
		calcular_rohat(IMPAR);
		Max_muestras[IMPAR]*=2;
		tam_lote[IMPAR]=Max_muestras[IMPAR]/NUM_LOTES;
		calcular_medias(IMPAR);
		lote[IMPAR]/=2;
		medias[IMPAR][lote[IMPAR]]=0;
		
		if(rohat<=0) {
			if(chequear_gamma()) {
				fin=1;
			}
			else fin=0;
		}		
		else {
			if(0<rohat && rohat<UMBRAL) {
				rohatold=rohat;
				calcular_rohat(IMPAR,MITAD);
				if(rohat<rohatold && chequear_gamma()) {
					fin=1;
				}
				else fin=0;
			}
			else fin=0;
		}
		cout << "Iteracion: " << iter << "\n";
		cout << "   -> Resultado: "; resultado(); cout << "\n";		// Tenemos que calcular la funcion de autocorrelacion.
        iteracion_finalizada=1;
		if(fin) {
			converge=1;
			return iteracion_finalizada;
		}
	}
	return iteracion_finalizada;
}

void Analisis::calcular_medias(int iteracion)
{
	// El parametro iteracion indica si tratamos con una operacion
	// PAR o IMPAR.

	register int i;
	register int k=0;
	// Caso especial
	for(i=0;i<NUM_LOTES/2;i++) {
		// Como puede verse vamos de 2 bloques en dos bloques
		medias[iteracion][i]=medias[iteracion][k]+medias[iteracion][k+1];
		medias[iteracion][i]/=2;
		k+=2;
	}
	return;
}

int Analisis::calcular_rohat(int iteracion,int que_parte)
{
	// el parametro iteracion nos indica si tratamos con iteraciones
	// pares o impares. En otro plano el parametro que_parte indica
	// si vamos a tratar con todos los lotes (NUM_LOTES) o solo con
	// la mitad de ellos
	int num_lotes=NUM_LOTES/que_parte;
	rohat=-0.5*(calcular_ro(iteracion,num_lotes,1)+calcular_ro(iteracion,num_lotes,2))+2*calcular_ro(iteracion,num_lotes,0);
	return 1;
	// El orden impuesto es fundamental para que se conserve el
	// correcto valor de parámetros tales como media_global...
}

long double Analisis::calcular_ro(int iteracion,int num_lotes,int indicador)
{
	int desde=0;
	int hasta=num_lotes;
	long double numerador=0;
	long double denominador=0;
	long double viejo=0;
	long double aux=0;
	register int i;
	switch (indicador) {
		case 1:
			hasta >>= 1;
			break;
		case 2:
			desde = num_lotes >> 1;
			break;
	}
	// Mediante la funcion media introducimos en media_total el valor
	// medio de las medias.
	media(iteracion,desde,hasta);
	denominador=viejo=medias[iteracion][desde]-media_total;
	denominador*=denominador;
	for(i=desde+1;i<=hasta-1;i++) {
		aux=medias[iteracion][i]-media_total;
		numerador+=viejo*aux;
		denominador+=aux*aux;
		viejo=aux;
	}
	numerador_sy2=denominador;
	if(!denominador) {
		return 0;
		//cerr << "Division por 0 en calcular_ro " << "\n";	
		//exit(DIV_CERO);	
	}
	numerador/=denominador;
	return numerador;
}

void Analisis::media(int iteracion,int desde, int hasta)
{
	register int i=0;
	media_total=0;
	for(i=desde;i<hasta;i++) {
		media_total+=medias[iteracion][i];
	}
	media_total/=(hasta-desde);
}	

int Analisis::chequear_gamma()
{
	long double delta;
	delta=t_STUDENT*sqrt(numerador_sy2/(NUM_LOTES*(NUM_LOTES-1)));
	if(media_total==0) {
		return 0; // Si la media total es 0 decimos que NO ha
				  // convergido
	}
	delta/=fabs(media_total);
	// Comparamos delta con el umbral.
	if(delta>GAMMA) return 0;
	// Si llegamos aqui se ha superado el umbral.
	return 1;
}

void Analisis::resultado()
{
	cout << media_total << "+-" << t_STUDENT*sqrt(numerador_sy2/(NUM_LOTES*(NUM_LOTES-1)));
}	

istream & operator >> (istream & ent, Analisis & anls)
{
	return ent;
}

ostream & operator << (ostream & sal, Analisis anls)
{
	return sal;
}
