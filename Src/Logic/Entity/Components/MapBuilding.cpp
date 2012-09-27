/**
@file MapBuilding.cpp

Contiene la implementación del componente que se comunica con
el mapa lógico para ocupar y desocupar las casillas necesarias
que ocupe un edificio.
 
@see Logic::CMapBuilding
@see Logic::IComponent

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "MapBuilding.h"

#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "ScriptManager/Server.h"


namespace Logic 
{
	IMP_FACTORY(CMapBuilding);
	
	//---------------------------------------------------------

	bool CMapBuilding::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("dimension"))
		{
			Vector2 size = entityInfo->getVector2Attribute("dimension");
			_buildingWidth = size.x;
			_buildingHeight = size.y;

		}

		if(entityInfo->hasAttribute("grid_position"))
		{
			Vector2 currentTilePos = entityInfo->getVector2Attribute("grid_position");
			_startRow = currentTilePos.y;
			_startCol = currentTilePos.x;

			_endRow = _startRow + _buildingHeight;
			_endCol = _startCol + _buildingWidth;

		}

		std::stringstream script;
		script << "buildings[" << _entity->getEntityID() << "] = {} ";
		script << "buildings[" << _entity->getEntityID()  << "].attackEnemy = -1 ";
		script << "buildings[" << _entity->getEntityID()  << "].activate = 0 ";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		
		std::stringstream script2;
		script2	<< "buildings[" << _entity->getEntityID() << "].posX = " << _entity->getPosition().x << " "
				<< "buildings[" << _entity->getEntityID() << "].posY = " << _entity->getPosition().y << " "
				<< "buildings[" << _entity->getEntityID() << "].posZ = " << _entity->getPosition().z;
		ScriptManager::CServer::getSingletonPtr()->executeScript(script2.str().c_str());

		if(entityInfo->hasAttribute("enemyBuilding") && entityInfo->getBoolAttribute("enemyBuilding"))
		{
			// Crear la tabla del edificio actual.
			std::stringstream scriptCreate;
			scriptCreate << "enemyBuildings[" << _entity->getEntityID() << "] = {}";
			ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());

			if(entityInfo->hasAttribute("hasSpawners") && entityInfo->getBoolAttribute("hasSpawners"))
			{
				// Crear la tabla de los spawners del edificio actual.
				std::stringstream scriptCreateSpawn;
				scriptCreateSpawn << "enemyBuildings[" << _entity->getEntityID() << "].spawners = {}";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreateSpawn.str().c_str());

				int i = 1;
				std::ostringstream spawner;
				spawner << "spawner" << i ;
				while (entityInfo->hasAttribute(spawner.str()))
				{
					// Voy añadiendo los spawners uno a uno.
					std::stringstream scriptAddSpawn;
					scriptAddSpawn << "enemyBuildings[" << _entity->getEntityID() << "].spawners[" << i << "] = { ID = " << entityInfo->getIntAttribute(spawner.str()) << ", }";
					ScriptManager::CServer::getSingletonPtr()->executeScript(scriptAddSpawn.str().c_str());

					i++;
					spawner.str("");
					spawner << "spawner" << i;
				}
			}
		}

		FillMapCells();

		return true;

	} // spawn

	//---------------------------------------------------------

	CMapBuilding::~CMapBuilding()
	{
		// No liberar las celdas aquí. Mandar un mensaje cuando el
		// edificio sea destruido y llamar entonces a la función.
		/*
		FreeMapCells();
		*/

	} // destructor
	
	//---------------------------------------------------------

	bool CMapBuilding::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CMapBuilding::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CMapBuilding::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CMapBuilding::process(IMessage *message)
	{

	} // process
	
	//---------------------------------------------------------

	void CMapBuilding::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
	} // tick

	//---------------------------------------------------------

	void CMapBuilding::FillMapCells()
	{
		for (int row = _startRow; row < _endRow; ++row)
			for (int col = _startCol; col < _endCol; ++col)
				_entity->getMap()->getGridMap()->getTileFromCoord(row, col)->SetBuilding(_entity);

	} // FillMapCells

	//---------------------------------------------------------

	void CMapBuilding::FreeMapCells()
	{
		for (int row = _startRow; row < _endRow; row ++)
			for (int col = _startCol; col < _endCol; col++)
				_entity->getMap()->getGridMap()->getTileFromCoord(row, col)->DeleteBuilding();

	} // FreeMapCells

} // namespace Logic

