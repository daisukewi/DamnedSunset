/**
@file IsActuable.cpp

Contiene la implementación del mensaje enviado para preguntar a una entidad
si se puede interactuar con ella o no.

@see Logic::IMessage

@author Daniel Flamenco
@date Mayo, 2012
*/

#include "IsActuable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MIsActuable::MIsActuable()
	{
		IMessage();

		_type = "MIsActuable";
	
	} // MIsActuable

	ActuablePetition MIsActuable::getMessageType()
	{
		return _petition;
	}

	void MIsActuable::setMessageType(ActuablePetition petitionType)
	{
		_petition = petitionType;
	}

	void MIsActuable::setSenderEntity(CEntity* sender)
	{
		_senderID = sender->getEntityID();
	}

	CEntity* MIsActuable::getSenderEntity()
	{
		return Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_senderID);
	}

} // namespace Logic