/**
@file IsSelectable.cpp

Contiene la implementación del mensaje enviado para preguntar a una entidad si es seleccionable

@author Alberto Ortega
@date Enero, 2012
*/

#include "IsSelectable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MIsSelectable::MIsSelectable()
	{
		IMessage();

		_type = "MIsSelectable";
	
	} // MIsSelectable

	SelectablePetition MIsSelectable::getMessageType()
	{
		return _petition;
	}

	void MIsSelectable::setMessageType(SelectablePetition petitionType)
	{
		_petition = petitionType;
	}

	void MIsSelectable::setSenderEntity(CEntity* sender)
	{
		_senderID = sender->getEntityID();
	}

	CEntity* MIsSelectable::getSenderEntity()
	{
		return Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_senderID);
	}

} // namespace Logic