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


#ifndef __CDATARATELENGTHCHANNEL_H_
#define __CDATARATELENGTHCHANNEL_H_

#include <omnetpp.h>

using namespace omnetpp;






/**
 * Channel that models delay, bit error rate and data rate.
 *
 * @ingroup SimCore
 */
class SIM_API cDelayLengthChannel : public  cDatarateChannel //implies noncopyable
{
private:
double length;
	int numEdfas;

public:
	cDelayLengthChannel();
	   virtual ~cDelayLengthChannel();
		   virtual void setLength(double d);
		   virtual double getLength();
		   virtual void setEdfas(int d);
		   virtual int getEdfas();



};



#endif


