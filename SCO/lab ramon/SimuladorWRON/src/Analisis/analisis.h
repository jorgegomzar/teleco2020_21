/***********************************************************/
//
// Archivo:   analisis.h
// Programa:
// Objetivo:  Declaracion de las clases necesarias para la
//			  realizacion del analisis de la simulacion.
// Autores:	  Ignacio de Miguel Jimenez
//			  David Rodriguez Alfayate
// Version:   1.1
//            21-Nov-00
// Variaciones: Solucionado un bug. Si se enviaban todos los
// datos iguales, ej: 20, 20, 20, ... la media no salía 20.
// ahora ya está solucionado. (I. de Miguel)
/***********************************************************/

#ifndef __ANALISIS_H
#define __ANALISIS_H

#include <cstring>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <sys/types.h>
#include <typeinfo>


#ifndef __MATH_H
#include <math.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream>
#endif

#ifndef __FSTREAM_H
#include <fstream>
#endif

#ifndef __SETJMP_H
#include <setjmp.h>
#endif

#ifndef NUM_LOTES 
#define NUM_LOTES 400
#endif

#ifndef PAR
#define PAR 1
#endif

#ifndef IMPAR
#define IMPAR 0
#endif

#define MITAD 2

#define DIV_CERO 3
#define UMBRAL   0.4
#define GAMMA    0.075

#define t_STUDENT        1.960

using namespace std;

class Analisis
{
	long double medias[2][NUM_LOTES];	// Para guardar las medias del
									// resultado del analisis.
	long double rohat;			// Correlacion.
	int pos_lote[2];		// Posicion del lote donde nos
							// encontramos.
	int tam_lote[2];		// tamanno del lote.
	int lote[2];			// lote actual.
	long muestras[2];		// Muestras por lote totales.
	int iter;				// Numero de iteracion
	int converge;			// Converge o no.
	long double media_total;		// Media de todos los lotes.
	long double numerador_sy2;	// Numerador y denominador en dos funciones.
	long Max_muestras[2];   // Numero maximo de muestras en its. pares e impares.
	int finbloque;			// Indica si se ha producido un fin de bloque.
	int errores; 			// El numero de media_total 0
						    // consecutivo.
	int errores2;			// Otro indicador de errores.
	jmp_buf error;			// Salto no
public:
	Analisis();
	bool analizar(const long double &elem); // Annade un elemento a la lista.
	int convergio() {return converge;}  // Devuelve 1 si OK, 0 en caso contrario.
	long double valor_rohat() {return rohat;} // Devuelve la autocorrelacion.
	void resultado();			// Imprime el resultado del analisis.
	long double valor_media() {return media_total; } // Devuelve la media.
	int num_iter() { return iter; }
	int Fin_bloque() { return finbloque; }
	long double desviacion() {
							return t_STUDENT*sqrt(numerador_sy2/(NUM_LOTES*(NUM_LOTES-1)));
						}
protected:
	void calcular_medias(int); // Calcula las medias de los lotes.
	int calcular_rohat(int,int x=1);	// Calcula  la correlacion.
	long double calcular_ro(int,int,int);    // Calcula una 1 estimacion de la correlacion
	void media(int,int,int);    		// Calcula la media de todas las 
					   					// medias de 'desde' a 'hasta'
	int chequear_gamma();	// Verifica si se ha superado el umbral.

	friend istream & operator>> (istream & ent, Analisis & anls);
	friend ostream & operator<< (ostream & sal, Analisis anls);

};

#endif

