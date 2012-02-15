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
			_buildingSize = entityInfo->getVector2Attribute("building_size");
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

	void CMapBuilding::FillMapCells()
	{
		TGridTile current_tile = _entity->getMap()->getTileFromPosition(_entity->getPosition().x, _entity->getPosition().z);
		int start_row = current_tile->GetRow() - _buildingSize.x / 2;
		int start_col = current_tile->GetCol() - _buildingSize.y / 2;

		int end_row = start_row + _buildingSize.y;
		int end_col = start_col + _buildingSize.x;

		for (int row = start_row; row < end_row; row ++)
			for (int col = start_col; col < end_col; col++)
				_entity->getMap()->getTileFromCoord(row, col)->SetBuilding(_entity);

	}

	void CMapBuilding::FreeMapCells()
	{
		TGridTile current_tile = _entity->getMap()->getTileFromPosition(_entity->getPosition().x, _entity->getPosition().z);
		int start_row = current_tile->GetRow() - _buildingSize.x / 2;
		int start_col = current_tile->GetCol() - _buildingSize.y / 2;

		int end_row = start_row + _buildingSize.y;
		int end_col = start_col + _buildingSize.x;

		for (int row = start_row; row < end_row; row ++)
			for (int col = start_col; col < end_col; col++)
				_entity->getMap()->getTileFromCoord(row, col)->DeleteBuilding();
	}

} // namespace Logic

