/**
@file EnemiesGenerator.cpp

Contiene la implementación del componente que controla la generación 
de enemigos en el mapa.
 
@see Logic::CEnemiesGenerator
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/

#include "EnemiesGenerator.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/SpawnEnemy.h"
#include "Logic/Entity/Messages/EnemyCreated.h"

#include <stdlib.h>
#include <sstream>

namespace Logic
{
	IMP_FACTORY(CEnemiesGenerator);
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("grid_position"))
			_origen = entityInfo->getVector2Attribute("grid_position");

		if(entityInfo->hasAttribute("periodo"))
			_periodo = entityInfo->getIntAttribute("periodo");

		if(entityInfo->hasAttribute("automaticSpawn"))
			_automaticSpawn = entityInfo->getBoolAttribute("automaticSpawn");
		else
			_automaticSpawn = false;

		if(entityInfo->hasAttribute("ID"))
		{
			_ID = entityInfo->getIntAttribute("ID");

			// Crear la tabla del spawner actual.
			std::stringstream scriptCreate;
			scriptCreate << "spawners[" << _ID << "] = {}";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());

			// Relleno la tabla con el ID de la entidad.
			std::stringstream script;
			script << "spawners[" << _ID << "].entityID = " << _entity->getEntityID();
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			// Creo la tabla de enemigos.
			std::stringstream scriptCreateEnemies;
			scriptCreateEnemies << "spawners[" << _ID << "].enemies = {}";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreateEnemies.str().c_str());

			// Inicializo el tiempo de cada spawner.
			std::stringstream scriptTime;
			scriptTime << "spawners[" << _ID << "].spawnTime = 0";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptTime.str().c_str());

			// Inicializo el conteo de enemigos que hay que mandar a atacar de cada spawner.
			std::stringstream scriptAttack;
			scriptAttack << "spawners[" << _ID << "].attackEnemies = 0";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptAttack.str().c_str());
		}

		std::srand(time(NULL));

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CEnemiesGenerator::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::accept(IMessage *message)
	{
		return !message->getType().compare("MSpawnEnemy");

	} // accept
	
	//---------------------------------------------------------

	void CEnemiesGenerator::process(IMessage *message)
	{
		if (!message->getType().compare("MSpawnEnemy"))
		{
			MSpawnEnemy *m = static_cast <MSpawnEnemy*> (message);
			_spawn += m->getNumEnemies();
		}

	} // process
	
	//---------------------------------------------------------

	Logic::CEntity* CEnemiesGenerator::spawnEnemy()
	{
		Map::CEntity *enemyInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Enemy");
		std::stringstream name;
		name << "Enemy" << _enemy << "_" << _entity->getEntityID();
		enemyInfo->setName(name.str());

		int offsetX = 0;//rand() % 4 + 1;
		int offsetY = 0;//rand() % 4 + 1;
						
		std::stringstream pos;
		pos << _origen.x + offsetX << ' ' << _origen.y + offsetY << ' ';
		enemyInfo->setAttribute("grid_position", pos.str());

		Logic::CEntity *ent = Logic::CEntityFactory::getSingletonPtr()->createEntity(enemyInfo, _entity->getMap());
		ent->activate();

		// Añado un nuevo enemigo a la tabla de enemigos creados por el spawner.
		std::stringstream script;
		script << "spawners[" << _ID << "].enemies[" << _enemy << "] = { ID = " << ent->getEntityID() << ", }";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

		//Avisar a los player de la creación del enemigo para que actualicen el componente de percepción y el controlador de la IA
		/*MEnemyCreated *m = new MEnemyCreated();
		Logic::CEntity *player = _entity->getMap()->getEntityByType("Player");
		m->setCreatedEnemy(ent);
		while (player != NULL)
		{
			player->emitMessage(m);
			player = _entity->getMap()->getEntityByType("Player", player);
		}*/

		_enemy++;

		return ent;

	} // spawnEnemy

	//---------------------------------------------------------

	void CEnemiesGenerator::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (_automaticSpawn)
		{
			// Si está activado el spawn automático, se spawnea un enemigo cada período de tiempo.
			_time += msecs;
			if (_time >= _periodo)
			{
				_time = 0;
				
				spawnEnemy();
			}
		}

		// Para no saturar la lógica del juego spawneo un enemigo a la vez en cada tick.
		if (_spawn > 0)
		{
			_spawn--;

			spawnEnemy();
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

