/**
@file ActivateReduceDamage.cpp

Contiene la implementación del mensaje enviado para activar la habilidad de reducción de daño

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