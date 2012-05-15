/**
@file LUA_SpawnEnemy.cpp

Contiene la implementación del mensaje de spawnear enemigo que sirve como intermediario entre lua y C++.

@author Alberto Plaza
@date Abril, 2012
*/

#include "LUA_SpawnEnemy.h"

#include "Logic/Entity/Messages/SpawnEnemy.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include <cassert>

namespace ScriptManager
{

	LUA_MSpawnEnemy::LUA_MSpawnEnemy()
	{
		LUA_IMessage();

		_numEnemies = 1;

		_type = "LUA_MSpawnEnemy";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void LUA_MSpawnEnemy::setNumEnemies(int numEnemies)
	{
		_numEnemies = numEnemies;

	} // setNumEnemies

	//---------------------------------------------------------

	int LUA_MSpawnEnemy::getNumEnemies()
	{
		return _numEnemies;

	} // getNumEnemies

	//---------------------------------------------------------

	void LUA_MSpawnEnemy::send()
	{
		//assert(_entityTo == Logic::EntityID::UNASSIGNED && "No se ha indicado a que entidad se envía el mensaje");
		if (_entityTo == Logic::EntityID::UNASSIGNED)
		{
			assert(!"No se ha indicado a que entidad se envía el mensaje");
			return;
		}

		Logic::MSpawnEnemy *m = new Logic::MSpawnEnemy();
		m->setNumEnemies(_numEnemies);
		Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entityTo)->emitMessage(m);

		//delete(this);

	} // send

	//---------------------------------------------------------

} // namespace Logic