/**
@file LUA_MAttackDistance.cpp

LUA

Contiene la implementación del mensaje de ataque a una entidad.

@author Alberto Ortega
@date Mayo, 2012
*/

#include "LUA_AttackDistance.h"
#include "Logic/Entity/Messages/AttackDistance.h"

#include "Logic/Maps/Map.h"

#include "Logic/Server.h"

#include <assert.h>

namespace ScriptManager
{

	LUA_MAttackDistance::LUA_MAttackDistance()
	{
		LUA_IMessage();

		_type = "LUA_MAttackDistance";

	} // MAttackDistance

	//---------------------------------------------------------

	void LUA_MAttackDistance::setEntity(unsigned int entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	unsigned int LUA_MAttackDistance::getEntity()
	{
		return _entity;

	} // getEntity


	void LUA_MAttackDistance::send()
	{
		assert(_entityTo != Logic::EntityID::UNASSIGNED && "No se ha indicado a que entidad se envía el mensaje");
		
		Logic::MAttackDistance *message = new Logic::MAttackDistance();
		message->setContinue(_continue);
		message->setAttack(_attack);
		message->setEntityID(_entity);
		message->setEntity(Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entity));
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entityTo)->emitMessage(message);

		//delete(this);

	} // send


	//---------------------------------------------------------

} // namespace Logic