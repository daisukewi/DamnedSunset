/**
@file EnemiesGenerator.cpp

Contiene la implementaci�n del componente que controla la generaci�n 
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

namespace Logic
{
	IMP_FACTORY(CEnemiesGenerator);
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("position"))
			_origen = entityInfo->getVector3Attribute("position");

		if(entityInfo->hasAttribute("periodo"))
			_periodo = entityInfo->getIntAttribute("periodo");

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
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CEnemiesGenerator::process(IMessage *message)
	{

	} // process
	
	//---------------------------------------------------------

	void CEnemiesGenerator::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		// Cada 500 ticks creamos un enemigo.
		_ticks += 1;
		if (_ticks >= _periodo)
		{
			_ticks = 0;
			_enemy += 1;

			Map::CEntity * enemyInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Enemy");
			std::stringstream name;
			name << "Enemy" << _enemy;
			enemyInfo->setName(name.str());
						
			std::stringstream pos;
			pos << _origen.x << ' ' << _origen.y << ' ' << _origen.z;
			enemyInfo->setAttribute("position", pos.str());

			Logic::CEntity *enemy = Logic::CEntityFactory::getSingletonPtr()->createEntity(enemyInfo, _entity->getMap());
		}

	} // tick

} // namespace Logic
