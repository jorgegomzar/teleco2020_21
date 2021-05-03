///////////////////////////////////////////////////////////////////
// This software is copyrighted by Optical Communications Group. //
// University of Valladolid (UVa)                                //
//                                                               //
// WRON simulator                                                //
// has been developed by Optical Communications Group.           //
// University of Valladolid (UVa)                                //
// Contact e-mail: rduran@tel.uva.es,natalia.fernandez@tel.uva.es //
//                                                               //
// Escuela Técnica Superior de Ingenieros de Telecomunicación    //
// Campus Miguel Delibes                                         //
// Universidad de Valladolid                                     //
// Paseo de Belén, 15                                            //
// 47011 Valladolid, Spain                                       //
//                                                               //
// This file is part of CHRON simulator,                         //
// an optical network simulation tool                            //
// based on OMNeT++/OMNEST discrete-event simulation framework.  //
//                                                               //
// Authoring:                                                    //
// Natalia Fernández Sordo (natalia.fernandez@tel.uva.es)        //
// Ramón J. Durán Barroso (rduran@tel.uva.es)                    //
// Ignacio de Miguel Jiménez (ignacio.miguel@tel.uva.es)         //
///////////////////////////////////////////////////////////////////

#include "cDelayLengthChannel.h"




using std::ostream;

Register_Class(cDelayLengthChannel);
Define_Channel(cDelayLengthChannel);

cDelayLengthChannel::cDelayLengthChannel()
{
    length=0;
    numEdfas=0;
}

cDelayLengthChannel::~cDelayLengthChannel()
{
}



void cDelayLengthChannel::setLength(double d)
{
	length=d;
}

double cDelayLengthChannel::getLength()
{
	length=par("length");
	return (length);
}

void cDelayLengthChannel::setEdfas(int d)
{
	numEdfas=d;
}

int cDelayLengthChannel::getEdfas()
{
	numEdfas=par("edfas");
	return (numEdfas);
}

