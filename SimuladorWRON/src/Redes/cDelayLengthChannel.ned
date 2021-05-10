///////////////////////////////////////////////////////////////////
// This software is copyrighted by Optical Communications Group. //
// University of Valladolid	(UVa)								 //
//																 //
// WRON simulator   											 //
// has been developed by Optical Communications Group.	 		 //
// University of Valladolid (UVa)		 						 //
// Contact e-mail: rduran@tel.uva.es,natalia.fernandez@tel.uva.es //
//																 //
// Escuela Técnica Superior de Ingenieros de Telecomunicación	 //
// Campus Miguel Delibes										 //
// Universidad de Valladolid									 //
// Paseo de Belén, 15											 //
// 47011 Valladolid, Spain										 //
//																 //
// This file is part of CHRON simulator, 						 //
// an optical network simulation tool							 //
// based on OMNeT++/OMNEST discrete-event simulation framework.  //
//																 //
// Authoring:													 //
// Natalia Fernández Sordo (natalia.fernandez@tel.uva.es)		 //
// Ramón J. Durán Barroso (rduran@tel.uva.es)					 //
// Ignacio de Miguel Jiménez (ignacio.miguel@tel.uva.es)		 //
///////////////////////////////////////////////////////////////////


package simuladorWRON.src.Redes;
import ned.*;

//
// TODO auto-generated type
//
channel cDelayLengthChannel extends ned.DatarateChannel
{
    double length @unit(km);
    int edfas;
    @class("cDelayLengthChannel");
}
