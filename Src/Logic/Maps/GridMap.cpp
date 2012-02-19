/**
@file GridMap.h

Contiene la implementación de la clase CGridMap, Un mapa de celdas lógico.

@see Logic::GridMap

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "GridMap.h"

#include "Logic/Entity/Entity.h"

// HACK. Debería leerse de algún fichero de configuración
const int GRID_SIZE = 10;
const float MAP_WIDTH = 200.0f;
const float MAP_HEIGHT = 200.0f;
const int MAP_HGRIDS = (int)MAP_WIDTH / GRID_SIZE;
const int MAP_VGRIDS = (int)MAP_HEIGHT / GRID_SIZE;

namespace Logic {

	CGridMap::CGridMap()
	{
		// Reserva memoria para almacenar el mapa lógico y inicializa cada casilla.
		_gridMap = new TGridTile*[MAP_VGRIDS];
		for (int i = 0; i < MAP_VGRIDS; ++i)
		{
			_gridMap[i] = new TGridTile[MAP_HGRIDS];
			for (int j = 0; j < MAP_HGRIDS; ++j)
				_gridMap[i][j] = new CGridTile(i, j);
		}

	} // CGridMap

	//--------------------------------------------------------

	CGridMap::~CGridMap()
	{
		// Libera la memoria utilizada para almacenar el mapa lógico.
		for (int i = 0; i < MAP_VGRIDS; ++i)
		{
			for (int j = 0; j < MAP_HGRIDS; ++j)
				delete(_gridMap[i][j]);
			delete(_gridMap[i]);
		}
		delete(_gridMap);
	}

	//--------------------------------------------------------

	const Vector2 CGridMap::getAbsoluteGridPos(const Vector2 pos)
	{
		TGridTile tile = getTileFromPosition(pos.x, pos.y);
		Vector2 modulePos;
		modulePos.x = tile->GetCol() * GRID_SIZE + GRID_SIZE * 0.5 - MAP_WIDTH / 2;
		modulePos.y = tile->GetRow() * GRID_SIZE + GRID_SIZE * 0.5 - MAP_HEIGHT / 2;

		return modulePos;

	} // getAbsoluteGridPos

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromPosition(const float x, const float y)
	{
		int row = (int)(x + MAP_WIDTH / 2) / GRID_SIZE;
		int col = (int)(y + MAP_HEIGHT / 2) / GRID_SIZE;

		assert(row >= 0 && row < MAP_VGRIDS && col >= 0 && col < MAP_HGRIDS);

		return getTileFromCoord(row, col);

	} // getGridFromPosition

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromCoord(const int row, const int col)
	{
		return _gridMap[col][row];

	} // getTileFromCoord

	//--------------------------------------------------------

	int CGridMap::getIndexTileFromCoord( Vector3 position )
	{
		TGridTile tile = getTileFromPosition(position.x, position.z);

		return tile->GetRow() * MAP_HGRIDS + tile->GetCol();
	}

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromIndex(const unsigned int index)
	{
		int row = index / MAP_HGRIDS;
		int col = index % MAP_HGRIDS;

		assert(row >= 0 && row < MAP_VGRIDS && col >= 0 && col < MAP_HGRIDS);

		return getTileFromCoord(row, col);

	} // getTileFromIndex

	//--------------------------------------------------------

	Vector3 CGridMap::getTilePositionFromIndex(const unsigned int index)
	{
		TGridTile tile = getTileFromIndex(index);

		Vector3 tilePos;
		tilePos.x = tile->GetCol() * GRID_SIZE + 0.5 * GRID_SIZE - MAP_WIDTH / 2;
		tilePos.y = 1.0f;
		tilePos.z = tile->GetRow() * GRID_SIZE + 0.5 * GRID_SIZE - MAP_HEIGHT / 2;

		return tilePos;

	} // getTilePositionFromIndex

	//--------------------------------------------------------

	std::list<unsigned int> CGridMap::getAdjacencyGrids(const int index)
	{
		TGridTile tile = getTileFromIndex(index);
		std::list<unsigned int>* neighbours = new std::list<unsigned int>();
		if (tile->GetRow() > 0)
			neighbours->push_back(index - MAP_HGRIDS);
		if (tile->GetRow() < MAP_HGRIDS - 1)
			neighbours->push_back(index + MAP_HGRIDS);
		if (tile->GetCol() > 0)
			neighbours->push_back(index - 1);
		if (tile->GetCol() < MAP_VGRIDS - 1)
			neighbours->push_back(index + 1);
		

		return (*neighbours);

	} // getAdjacencyGrids

	//--------------------------------------------------------

	int CGridMap::getNumGrids()
	{
		return ( MAP_HGRIDS * MAP_VGRIDS );
	}

	//--------------------------------------------------------

	void CGridMap::PrintMap()
	{
		printf("--------Map Dump ---------\n");
		printf("Size: %f, %f\n", MAP_WIDTH, MAP_HEIGHT);
		printf("Grids: %d, %d\n\n", MAP_HGRIDS, MAP_VGRIDS);
		for (int i = MAP_VGRIDS - 1; i >= 0; --i)
		{
			printf("|");
			for (int j = MAP_HGRIDS - 1; j >= 0; --j)
			{
				printf(" %s", getTileFromCoord(i, j)->IsPopulated() ? "#" : "-");
			}
			printf("|\n");
		}
	}


} // namespace Logic