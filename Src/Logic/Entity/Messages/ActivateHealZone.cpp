/**
@file ActivateHealZone.cpp

Contiene la implementaci�n del mensaje enviado para activar la habilidad de curaci�n de da�o en una zona

@author Alberto Ortega
@date Agosto, 2012
*/

#include "ActivateHealZone.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MActivateHealZone::MActivateHealZone()
	{
		IMessage();

		_type = "MActivateHealZone";
	
	} // MActivateHealZone

} // namespace Logic