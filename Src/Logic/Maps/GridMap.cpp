/**
@file GridMap.h

Contiene la implementación de la clase CGridMap, Un mapa de celdas lógico.

@see Logic::GridMap

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "GridMap.h"

#include "Logic/Entity/Entity.h"

namespace Logic {

	CGridMap::CGridMap()
	{

	} // CGridMap

	//--------------------------------------------------------

	CGridMap::~CGridMap()
	{
		// Libera la memoria utilizada para almacenar el mapa lógico.
		for (int i = 0; i < _mapVGrids; ++i)
		{
			for (int j = 0; j < _mapHGrids; ++j)
				delete(_gridMap[i][j]);
			delete(_gridMap[i]);
		}
		delete(_gridMap);

	} // ~CGridMap

	//--------------------------------------------------------

	void CGridMap::initMap(int width, int height, int gridSize)
	{
		_mapHGrids = height;
		_mapVGrids = width;
		_gridSize = gridSize;
		_mapHeight = _mapHGrids * _gridSize;
		_mapWidth = _mapVGrids * _gridSize;

		// Reserva memoria para almacenar el mapa lógico y inicializa cada casilla.
		_gridMap = new TGridTile*[_mapVGrids];
		for (int i = 0; i < _mapVGrids; ++i)
		{
			_gridMap[i] = new TGridTile[_mapHGrids];
			for (int j = 0; j < _mapHGrids; ++j)
				_gridMap[i][j] = new CGridTile(i, j);
		}

	} // initMap

	//--------------------------------------------------------

	const Vector2 CGridMap::getAbsoluteGridPos(const Vector2 pos)
	{
		TGridTile tile = getTileFromPosition(pos.x, pos.y);
		Vector2 modulePos;
		modulePos.x = tile->GetCol() * _gridSize + _gridSize * 0.5 - _mapWidth / 2;
		modulePos.y = tile->GetRow() * _gridSize + _gridSize * 0.5 - _mapHeight / 2;

		return modulePos;

	} // getAbsoluteGridPos

	//--------------------------------------------------------

	const Vector2 CGridMap::getRelativeMapPos( unsigned int row, unsigned int col )
	{
		Vector2 relativePos;
		relativePos.x = col * _gridSize + _gridSize * 0.5 - _mapWidth / 2;
		relativePos.y = row * _gridSize + _gridSize * 0.5 - _mapHeight / 2;

		return relativePos;

	} // getRelativeMapPos

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromPosition(const float x, const float y)
	{
		int col = (int)(x + _mapWidth / 2) / _gridSize;
		int row = (int)(y + _mapHeight / 2) / _gridSize;

		assert(row >= 0 && row < _mapVGrids && col >= 0 && col < _mapHGrids);

		return getTileFromCoord(row, col);

	} // getGridFromPosition

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromCoord(const int row, const int col)
	{
		return _gridMap[row][col];

	} // getTileFromCoord

	//--------------------------------------------------------

	int CGridMap::getIndexTileFromPosition( Vector3 position )
	{
		TGridTile tile = getTileFromPosition(position.x, position.z);

		return getIndexTileFromCoord(tile->GetRow(), tile->GetCol());
	}

	//--------------------------------------------------------

	int CGridMap::getIndexTileFromCoord( const int row, const int col )
	{
		return row * _mapHGrids + col;

	} // getIndexTileFromCoord

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromIndex(const unsigned int index)
	{
		int row = index / _mapHGrids;
		int col = index % _mapHGrids;

		assert(row >= 0 && row < _mapVGrids && col >= 0 && col < _mapHGrids);

		return getTileFromCoord(row, col);

	} // getTileFromIndex

	//--------------------------------------------------------

	Vector3 CGridMap::getTilePositionFromIndex(const unsigned int index)
	{
		TGridTile tile = getTileFromIndex(index);

		Vector3 tilePos;
		tilePos.x = tile->GetCol() * _gridSize + 0.5 * _gridSize - _mapWidth / 2;
		tilePos.y = 1.0f;
		tilePos.z = tile->GetRow() * _gridSize + 0.5 * _gridSize - _mapHeight / 2;

		return tilePos;

	} // getTilePositionFromIndex

	//--------------------------------------------------------

	std::list<unsigned int> CGridMap::getAdjacencyGrids(const int index)
	{
		TGridTile tile = getTileFromIndex(index);
		std::list<unsigned int>* neighbours = new std::list<unsigned int>();
		if (tile->GetCol() > 0)
			neighbours->push_back(index - 1);
		if (tile->GetCol() < _mapHGrids - 1)
			neighbours->push_back(index + 1);
		if (tile->GetRow() > 0)
			neighbours->push_back(index - _mapHGrids);
		if (tile->GetRow() < _mapVGrids - 1)
			neighbours->push_back(index + _mapHGrids);
		

		return (*neighbours);

	} // getAdjacencyGrids

	//--------------------------------------------------------

	int CGridMap::getNumGrids()
	{
		return ( _mapHGrids * _mapVGrids );
	}

	//--------------------------------------------------------

	void CGridMap::PrintMap()
	{
		printf("--------Map Dump ---------\n");
		printf("Size: %f, %f\n", _mapWidth, _mapHeight);
		printf("Grids: %d, %d\n\n", _mapHGrids, _mapVGrids);
		for (int i = 0; i < _mapVGrids; ++i)
		{
			printf("|");
			for (int j = 0; j < _mapHGrids; ++j)
			{
				printf(" %s", getTileFromCoord(i, j)->IsPopulated() ? "i" : "-");
			}
			printf("|\n");
		}
	}

	void CGridMap::PrintMapWithRoute( std::vector<void*>* path )
	{
		printf("--------Map Dump ---------\n");
		printf("Size: %f, %f\n", _mapWidth, _mapHeight);
		printf("Grids: %d, %d\n\n", _mapHGrids, _mapVGrids);
		for (int i = _mapVGrids - 1; i >= 0; --i)
		{
			printf("%3d |", getIndexTileFromCoord(i, _mapHGrids - 1));
			for (int j = _mapHGrids - 1; j >= 0; --j)
			{
				char empty = getTileFromCoord(i, j)->IsPopulated() ? 'i' : '-';
				for (std::vector<void*>::iterator it = path->begin(); it != path->end(); it++) {
					TGridTile tile = getTileFromIndex((int)(*it));
					if (tile->GetRow() == i && tile->GetCol() == j)
						empty = '*';
				}
				printf(" %c", empty);
			}
			printf("| %d\n", getIndexTileFromCoord(i, 0));
		}
	}


} // namespace Logic