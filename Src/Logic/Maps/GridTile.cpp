/**
@file GridTile.h

Contiene la implementación de la clase CGridTile, Las celdas de un mapa lógico.

@see Logic::GridTile

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "GridTile.h"

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

	void CGridTile::SetTerrain(int terrainType)
	{
		_terrain = terrainType;
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

	void CGridTile::FillData()
	{
		//Map::CMapParser::TTileMatrix tileMatrix){}
	}

	//--------------------------------------------------------

} // namespace Logic