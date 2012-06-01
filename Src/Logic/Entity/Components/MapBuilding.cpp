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

			_endRow = _startRow - _buildingHeight;
			_endCol = _startCol - _buildingWidth;

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

