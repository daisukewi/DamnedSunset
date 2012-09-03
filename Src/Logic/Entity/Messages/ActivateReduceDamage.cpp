/**
@file ActivateReduceDamage.cpp

Contiene la implementaci�n del mensaje enviado para activar la habilidad de reducci�n de da�o

@author Alberto Ortega
@date Agosto, 2012
*/

#include "ActivateReduceDamage.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MActivateReduceDamage::MActivateReduceDamage()
	{
		IMessage();

		_type = "MActivateReduceDamage";
	
	} // MActivateReduceDamage

} // namespace Logic