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

#include "CoreRouter.h"

Define_Module(CoreRouter);

void CoreRouter::initialize()
{
	// TODO - Generated method body
}

void CoreRouter::handleMessage(cMessage *msg)
{
	char mensaje[30];
	int origen,destino;
	PeticionLightpath *mensaje_peticion;
	mensaje_peticion = check_and_cast<PeticionLightpath *>(msg);

	origen = mensaje_peticion->getNodo_origen();
	destino = mensaje_peticion->getNodo_destino();

	sprintf(mensaje,"Lightpath de %d a %d",origen,destino);
	bubble(mensaje);


    sendDirect(msg,getParentModule()->getSubmodule("nodo_control")->getSubmodule("WRON_Dinamica")->getSubmodule("nodo_control_dynamic_WRON"),"in");


//	cDisplayString& dispStr = getDisplayString();
//	dispStr.insertTag("t");
//	dispStr.setTagArg("t",0,mensaje);
//	//dispStr.parse("t=Packets sent: 18;tt=Additional tooltip information");
//
//
//	cDisplayString& parentDispStr = getParentModule()->getDisplayString();
////	parentDispStr.parse("bgi=maps/europe;bgg=100,2");
//	//dispStr.parse("t=HIHI");



//	dispStr.parse("a=1,2;p=alpha,,3");
//	dispStr.insertTag("x");
//	dispStr.setTagArg("x",0,"joe");
//	dispStr.setTagArg("x",2,"jim");
//	dispStr.setTagArg("p",0,"beta");

	//bubble("Hola");
//	ev << dispStr.str(); // result: "x=joe,,jim;a=1,2;p=beta,,3"


	//	dispStr.parse("i=device/cellphone");

	// TODO - Generated method body
}

