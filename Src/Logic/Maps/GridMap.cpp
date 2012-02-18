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
const int MAP_HGRIDS = 10;
const int MAP_VGRIDS = 10;
const float MAP_WIDTH = 100.0f;
const float MAP_HEIGHT = 100.0f;

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

	Vector2 CGridMap::getAbsoluteGridPos(const Vector2 pos)
	{
		Vector2 modulePos;
		modulePos.x = ( (int)pos.x / GRID_SIZE - 0.5 ) * GRID_SIZE;
		modulePos.y = ( (int)pos.y / GRID_SIZE - 0.5 ) * GRID_SIZE;

		return modulePos;

	} // getAbsoluteGridPos

	//--------------------------------------------------------

	TGridTile CGridMap::getTileFromPosition(const float x, const float y)
	{
		int row = (int)(x + MAP_WIDTH / 2) / GRID_SIZE;
		int col = (int)(y + MAP_HEIGHT / 2) / GRID_SIZE;

		assert(row >= 0 && row < MAP_HGRIDS && col >= 0 && col < MAP_VGRIDS);

		return getTileFromCoord(row, col);

	} // getGridFromPosition

	//--------------------------------------------------------

	TGridTile CGridMap::getTileFromCoord(const int row, const int col)
	{
		return _gridMap[row][col];

	} // getTileFromCoord

} // namespace Logic