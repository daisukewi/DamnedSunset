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
		for (int i = 0; i < _nMapRows; ++i)
		{
			for (int j = 0; j < _nMapCols; ++j)
				delete(_gridMap[i][j]);
			delete(_gridMap[i]);
		}
		delete(_gridMap);
	}

	//--------------------------------------------------------

	void CGridMap::initMap(int width, int height, int gridSize)
	{
		_nMapCols = width;
		_nMapRows = height;
		_mapWidth = width * gridSize;
		_mapHeight = height * gridSize;

		_halfMapWidth = _mapWidth / 2;
		_halfMapHeight = _mapHeight / 2;
		_gridSize = Math::Log2(gridSize);
		_halfGrid = gridSize / 2;

		// Reserva memoria para almacenar el mapa lógico y inicializa cada casilla.
		_gridMap = new TGridTile*[_nMapRows];
		for (int i = 0; i < _nMapRows; ++i)
		{
			_gridMap[i] = new TGridTile[_nMapCols];
			for (int j = 0; j < _nMapCols; ++j)
				_gridMap[i][j] = new CGridTile(i, j);
		}

	} // initMap

	//--------------------------------------------------------

	const Vector2 CGridMap::getAbsoluteGridPos(const Vector2 pos)
	{
		TGridTile tile = getTileFromPosition(pos.x, pos.y);
		Vector2 modulePos;
		modulePos.x = (int)(tile->GetCol() << _gridSize) + _halfGrid - _halfMapWidth;
		modulePos.y = (int)(tile->GetRow() << _gridSize) + _halfGrid - _halfMapHeight;

		return modulePos;

	} // getAbsoluteGridPos

	//--------------------------------------------------------

	const Vector2 CGridMap::getRelativeMapPos( unsigned int row, unsigned int col )
	{
		Vector2 relativePos;
		relativePos.x = (int)(col << _gridSize) + _halfGrid - _halfMapWidth;
		relativePos.y = (int)(row << _gridSize) + _halfGrid - _halfMapHeight;

		return relativePos;

	} // getRelativeMapPos

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromPosition(const float x, const float y)
	{
		int col = (int)(x + _halfMapWidth) >> _gridSize;
		int row = (int)(y + _halfMapHeight) >> _gridSize;

		assert(row >= 0 && row < _nMapRows && col >= 0 && col < _nMapCols);

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
		return row * _nMapCols + col;

	} // getIndexTileFromCoord

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromIndex(const unsigned int index)
	{
		int row = index / _nMapCols;
		int col = index % _nMapCols;

		assert(row >= 0 && row < _nMapRows && col >= 0 && col < _nMapCols);

		return getTileFromCoord(row, col);

	} // getTileFromIndex

	//--------------------------------------------------------

	Vector3 CGridMap::getTilePositionFromIndex(const unsigned int index)
	{
		TGridTile tile = getTileFromIndex(index);

		Vector3 tilePos;
		tilePos.x = (int)(tile->GetCol() << _gridSize) + _halfGrid - _halfMapWidth;
		tilePos.y = 1.0f;
		tilePos.z = (int)(tile->GetRow() << _gridSize) + _halfGrid - _halfMapHeight;

		return tilePos;

	} // getTilePositionFromIndex

	//--------------------------------------------------------

	std::list<unsigned int> CGridMap::getAdjacencyGrids(const int index)
	{
		TGridTile tile = getTileFromIndex(index);
		std::list<unsigned int>* neighbours = new std::list<unsigned int>();
		if (tile->GetCol() > 0)
			neighbours->push_back(index - 1);
		if (tile->GetCol() < _nMapCols - 1)
			neighbours->push_back(index + 1);
		if (tile->GetRow() > 0)
			neighbours->push_back(index - _nMapCols);
		if (tile->GetRow() < _nMapRows - 1)
			neighbours->push_back(index + _nMapCols);
		

		return (*neighbours);

	} // getAdjacencyGrids

	//--------------------------------------------------------

	int CGridMap::getNumGrids()
	{
		return ( _nMapCols * _nMapRows );
	}

	//--------------------------------------------------------

	void CGridMap::PrintMap()
	{
		printf("--------Map Dump ---------\n");
		printf("Size: %f, %f\n", _mapWidth, _mapHeight);
		printf("Grids: %d, %d\n\n", _nMapCols, _nMapRows);
		for (int i = 0; i < _nMapRows; ++i)
		{
			printf("|");
			for (int j = 0; j < _nMapCols; ++j)
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
		printf("Grids: %d, %d\n\n", _nMapCols, _nMapRows);
		for (int i = _nMapRows - 1; i >= 0; --i)
		{
			//printf("%3d |", getIndexTileFromCoord(i, _nMapCols - 1));
			printf("|");
			for (int j = _nMapCols - 1; j >= 0; --j)
			{
				char empty = getTileFromCoord(i, j)->IsPopulated() ? 'i' : '-';
				for (std::vector<void*>::iterator it = path->begin(); it != path->end(); it++) {
					TGridTile tile = getTileFromIndex((int)(*it));
					if (tile->GetRow() == i && tile->GetCol() == j)
						empty = '*';
				}
				printf(" %c", empty);
			}
			//printf("| %d\n", getIndexTileFromCoord(i, 0));
			printf(" |\n");
		}
	}


} // namespace Logic