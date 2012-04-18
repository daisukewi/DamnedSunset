/**
@file LUA_AttackEntity.cpp

LUA

Contiene la implementación del mensaje de ataque a una entidad.

@author Alberto Ortega
@date Abril, 2012
*/

#include "LUA_AttackEntity.h"

#include "Logic/Entity/Messages/AttackEntity.h"
#include <cassert>

#include "BaseSubsystems/Math.h"

#include "Logic/Maps/Map.h"

#include "Logic/Server.h"

#include "Logic/Maps/EntityID.h"

namespace ScriptManager
{

	LUA_MAttackEntity::LUA_MAttackEntity()
	{
		LUA_IMessage();

		_type = "LUA_MAttackEntity";

	} // MAttackEntity

	//---------------------------------------------------------

	void LUA_MAttackEntity::setEntity(unsigned int entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	unsigned int LUA_MAttackEntity::getEntity()
	{
		return _entity;

	} // getEntity

	//---------------------------------------------------------

	void LUA_MAttackEntity::send()
	{
		assert(_entityTo == Logic::EntityID::UNASSIGNED && "No se ha indicado a que entidad se envía el mensaje");

		
		Logic::MAttackEntity *message = new Logic::MAttackEntity();
		message->setAttack(_attack);
		message->setEntity(Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entity));
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entityTo)->emitMessage(message);

	}

} // namespace Logic