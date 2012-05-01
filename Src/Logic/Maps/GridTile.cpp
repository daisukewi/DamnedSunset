/**
@file GridTile.h

Contiene la implementación de la clase CGridTile, Las celdas de un mapa lógico.

@see Logic::GridTile

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "GridTile.h"
#include "TerrainTile.h"

namespace Logic {

	unsigned int CGridTile::GetRow()
	{
		return _row;
	}

	//--------------------------------------------------------

	unsigned int CGridTile::GetCol()
	{
		return _col;
	}

	//--------------------------------------------------------

	void CGridTile::SetTerrain(CTerrainTile* terrain)
	{
		_terrain = terrain;

	}

	//--------------------------------------------------------

	void CGridTile::SetBuilding(CEntity* building)
	{
		_building = building;
	}

	//--------------------------------------------------------

	void CGridTile::DeleteBuilding()
	{
		_building = NULL;
	}

	//--------------------------------------------------------

	CEntity* CGridTile::GetBuilding()
	{
		return _building;
	}

	//--------------------------------------------------------

	bool CGridTile::IsPopulated()
	{
		return _building != NULL;
	}

	//--------------------------------------------------------

	void CGridTile::AddUnit(CEntity* entity)
	{
		/*_entityList.insert(std::pair<TEntityID, CEntity*>(entity->getEntityID(), entity));*/
	}

	//--------------------------------------------------------

	void CGridTile::DeleteUnit(CEntity* entity)
	{
		/*_entityList.erase(entity->getEntityID());*/
	}

	//--------------------------------------------------------

	int CGridTile::GetAStarCost()
	{
		return _terrain->getAStarCost();

	}

	//--------------------------------------------------------

	bool CGridTile::CanPassThrow()
	{
		return _terrain->getAStarCost() >= 0 && !IsPopulated();

	}

	//--------------------------------------------------------

} // namespace Logic