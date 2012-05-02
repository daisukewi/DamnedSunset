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
			// Crear la tabla del spawner actual.
			std::stringstream scriptCreate;
			scriptCreate << "spawners[" << entityInfo->getIntAttribute("ID") << "] = {}";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());

			// Relleno la tabla con el ID de la entidad.
			std::stringstream script;
			script << "spawners[" << entityInfo->getIntAttribute("ID") << "].entityID = " << _entity->getEntityID();
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
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
			_spawn++;

	} // process
	
	//---------------------------------------------------------

	Logic::CEntity* CEnemiesGenerator::spawnEnemy()
	{
		Map::CEntity *enemyInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Enemy");
		std::stringstream name;
		name << "Enemy" << _enemy << "_" << _entity->getEntityID();
		enemyInfo->setName(name.str());

		int offsetX = rand() % 4 + 1;
		int offsetY = rand() % 4 + 1;
						
		std::stringstream pos;
		pos << _origen.x + offsetX << ' ' << _origen.y + offsetY << ' ';
		enemyInfo->setAttribute("grid_position", pos.str());

		Logic::CEntity *ent = Logic::CEntityFactory::getSingletonPtr()->createEntity(enemyInfo, _entity->getMap());
		ent->activate();

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

		if (_spawn > 0)
		{
			_spawn--;

			spawnEnemy();
		}

	} // tick

	//---------------------------------------------------------

} // namespace Logic

