/**
@file GridTile.h

Contiene la implementación de la clase CTerrainTile que contiene
la informacion de una celda del terreno.

@see Logic::TerrainTile

@author Daniel Flamenco
@date Abril, 2012
*/

#include "TerrainTile.h"

#include "Map/MapEntity.h"

namespace Logic {

	std::string CTerrainTile::getName()
	{
		return _name;
	}

	void CTerrainTile::FillData(Map::CEntity* terrain_info)
	{
		if (terrain_info->hasAttribute("cost"))
			_aStarCost = terrain_info->getIntAttribute("cost");

		if (terrain_info->hasAttribute("difuse_texture"))
			_difuseMap = terrain_info->getStringAttribute("difuse_texture");

		if (terrain_info->hasAttribute("normal_texture"))
			_normalMap = terrain_info->getStringAttribute("normal_texture");
	}
}