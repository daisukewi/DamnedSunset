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

		if(entityInfo->hasAttribute("building_size"))
		{
			Vector2 size = entityInfo->getVector2Attribute("building_size");
			_buildingWidth = size.x;
			_buildingHeight = size.y;

			FillMapCells();
		}

		return true;

	} // spawn

	//---------------------------------------------------------

	CMapBuilding::~CMapBuilding()
	{
		FreeMapCells();

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
		TGridTile current_tile = _entity->getMap()->getTileFromPosition(_entity->getPosition().x, _entity->getPosition().z);
		_startRow = current_tile->GetRow() - _buildingHeight / 2;
		_startCol = current_tile->GetCol() - _buildingWidth / 2;

		_endRow = _startRow + _buildingHeight;
		_endCol = _startCol + _buildingWidth;

		for (int row = _startRow; row < _endRow; row ++)
			for (int col = _startCol; col < _endCol; col++)
				_entity->getMap()->getTileFromCoord(row, col)->SetBuilding(_entity);

	} // FillMapCells

	//---------------------------------------------------------

	void CMapBuilding::FreeMapCells()
	{
		for (int row = _startRow; row < _endRow; row ++)
			for (int col = _startCol; col < _endCol; col++)
				_entity->getMap()->getTileFromCoord(row, col)->DeleteBuilding();

	} // FreeMapCells

} // namespace Logic

