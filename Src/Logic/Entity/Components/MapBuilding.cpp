/**
@file MapBuilding.cpp

Contiene la implementaci�n del componente que se comunica con
el mapa l�gico para ocupar y desocupar las casillas necesarias
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

		if(entityInfo->hasAttribute("building_size"))
		{
			Vector2 size = entityInfo->getVector2Attribute("building_size");
			_buildingWidth = size.x;
			_buildingHeight = size.y;

			//map->getGridMap()->PrintMap();
		}

		if(entityInfo->hasAttribute("grid_position"))
		{
			Vector2 currentTilePos = entityInfo->getVector2Attribute("grid_position");
			_startRow = currentTilePos.y;
			_startCol = currentTilePos.x;

			_endRow = _startRow + _buildingHeight;
			_endCol = _startCol + _buildingWidth;

			Vector2 relativePosition = map->getGridMap()->getRelativeMapPos(_startRow, _startCol);
			Vector2 diagonalSize = map->getGridMap()->getRelativeMapPos(_endRow, _endCol) - relativePosition;

			relativePosition += diagonalSize / diagonalSize.length();

			_entity->setPosition(Vector3(relativePosition.x, 0.0f, relativePosition.y), true);

		}
		else if(entityInfo->hasAttribute("position"))
		{
			// Ponemos la nueva posici�n del edificio en el centro de la casilla que le corresponda.
			Vector3 oldpos = entityInfo->getVector3Attribute("position");
			Vector2 newPos = map->getGridMap()->getAbsoluteGridPos(Vector2 (oldpos.x, oldpos.z));
			_entity->setPosition(Vector3(newPos.x, oldpos.y, newPos.y), true);

			TGridTile currentTile = map->getGridMap()->getTileFromPosition(newPos.x, newPos.y);
			_startRow = currentTile->GetRow() - _buildingHeight / 2;
			_startCol = currentTile->GetCol() - _buildingWidth / 2;

			_endRow = _startRow + _buildingHeight;
			_endCol = _startCol + _buildingWidth;

		}

		FillMapCells();

		return true;

	} // spawn

	//---------------------------------------------------------

	CMapBuilding::~CMapBuilding()
	{
		// No liberar las celdas aqu�. Mandar un mensaje cuando el
		// edificio sea destruido y llamar entonces a la funci�n.
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

