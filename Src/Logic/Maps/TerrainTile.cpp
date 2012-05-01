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
#include "Map/MapTile.h"

namespace Logic
{

	void CTerrainTile::FillData(Map::CEntity* terrain_info)
	{
		if (terrain_info->hasAttribute("cost"))
			_aStarCost = terrain_info->getIntAttribute("cost");

		if (terrain_info->hasAttribute("texture_size"))
			_textureSize = terrain_info->getIntAttribute("texture_size");

		if (terrain_info->hasAttribute("difuse_texture"))
			_difuseMap = terrain_info->getStringAttribute("difuse_texture");

		if (terrain_info->hasAttribute("normal_texture"))
			_normalMap = terrain_info->getStringAttribute("normal_texture");

	} // FillData

	//--------------------------------------------------------

	void CTerrainTile::FillData(Map::CTile* terrain_info)
	{
		if (terrain_info->hasAttribute("cost"))
			_aStarCost = terrain_info->getIntAttribute("cost");

		if (terrain_info->hasAttribute("texture_size"))
			_textureSize = terrain_info->getIntAttribute("texture_size");

		if (terrain_info->hasAttribute("difuse_texture"))
			_difuseMap = terrain_info->getStringAttribute("difuse_texture");

		if (terrain_info->hasAttribute("normal_texture"))
			_normalMap = terrain_info->getStringAttribute("normal_texture");

	} // FillData

	//--------------------------------------------------------

	std::string CTerrainTile::getName()
	{
		return _name;

	} // getName

	//--------------------------------------------------------

	int CTerrainTile::getAStarCost()
	{
		return _aStarCost;

	} // getAStarCost

	//--------------------------------------------------------

	std::string CTerrainTile::getDifuseMap()
	{
		return _difuseMap;

	} // getDifuseMap

	//--------------------------------------------------------

	std::string CTerrainTile::getNormalMap()
	{
		return _normalMap;

	} // getNormalMap

	//--------------------------------------------------------

	int CTerrainTile::getTextureSize()
	{
		return _textureSize;

	} // getTextureSize
}