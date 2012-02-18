/**
@file MapUnit.cpp

Contiene la implementación del componente que se comunica con
el mapa lógico para ocupar y desocupar las casillas necesarias
que ocupe una unidad.
 
@see Logic::CMapUnit
@see Logic::IComponent

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "MapUnit.h"

#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"


namespace Logic 
{
	IMP_FACTORY(CMapUnit);
	
	//---------------------------------------------------------

	bool CMapUnit::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("unit_size"))
		{
			Vector2 size = entityInfo->getVector2Attribute("unit_size");
			_unitWidth = size.x;
			_unitHeight = size.y;

		} else {
			_unitWidth = 1;
			_unitHeight = 1;
		}

		// Añade la unidad a la casilla que pertenece.
		TGridTile current_tile = _entity->getMap()->getGridMap()->getTileFromPosition(_entity->getPosition().x, _entity->getPosition().z);
		_currentRow = current_tile->GetRow() - _unitHeight / 2;
		_currentCol = current_tile->GetCol() - _unitWidth / 2;
		_entity->getMap()->getGridMap()->getTileFromCoord(_currentRow, _currentCol)->AddUnit(_entity);

		return true;

	} // spawn

	//---------------------------------------------------------

	/*
	CMapUnit::~CMapBuilding()
	{
		// No liberar las celdas aquí. Mandar un mensaje cuando el
		// edificio sea destruido y llamar entonces a la función.
		
		FreeMapCells();
		

	} // destructor
	*/
	
	//---------------------------------------------------------

	bool CMapUnit::activate()
	{
		return true;

	} // activate
	
	//---------------------------------------------------------

	void CMapUnit::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CMapUnit::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CMapUnit::process(IMessage *message)
	{

	} // process
	
	//---------------------------------------------------------

	void CMapUnit::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		//UpdateMapCells();
		
	} // tick

	//---------------------------------------------------------

	void CMapUnit::UpdateMapCells()
	{
		TGridTile current_tile = _entity->getMap()->getGridMap()->getTileFromPosition(_entity->getPosition().x, _entity->getPosition().z);
		unsigned int newRow = current_tile->GetRow() - _unitHeight / 2;
		unsigned int newCol = current_tile->GetCol() - _unitWidth / 2;

		if (newRow != _currentRow || newCol != _currentCol)
		{
			FreeMapCells();
			_entity->getMap()->getGridMap()->getTileFromCoord(newRow, newCol)->AddUnit(_entity);

			_currentRow = newRow;
			_currentCol = newCol;
		}

	} // UpdateMapCells

	//---------------------------------------------------------

	void CMapUnit::FreeMapCells()
	{
		_entity->getMap()->getGridMap()->getTileFromCoord(_currentRow, _currentCol)->DeleteUnit(_entity);

	} // FreeMapCells

} // namespace Logic

