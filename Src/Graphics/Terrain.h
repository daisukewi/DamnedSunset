//---------------------------------------------------------------------------
// Terrain.h
//---------------------------------------------------------------------------

/**
@file Terrain.h

Contiene la declaraci�n de la clase que define un terreno.

@see Graphics::CTerrain

@author Daniel Flamenco
@date Marzo, 2012
*/

#ifndef __Graphics_Terrain_H
#define __Graphics_Terrain_H

#include <list>
#include <OgrePrerequisites.h>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class TerrainGlobalOptions;
	class TerrainGroup;
	class Terrain;
	class Light;
	class FrameEvent;
	class SceneManager;
}

namespace Logic
{
	class CTerrainTile;
	class CGridMap;
}

namespace Graphics 
{
	
	/*
	@ingroup graphicsGroup

	@author Daniel Flamenco
	@date Marzo, 2012
	*/
	class CTerrain 
	{
	public:

		CTerrain(Ogre::SceneManager* sceneMgr, std::list<Logic::CTerrainTile*>* terrainList, Logic::CGridMap* terrainMap);

		~CTerrain();

		bool wasTerrainsImported();

		float getHeightAtWorldPosition(Ogre::Vector3 vPos);

	private:

		Ogre::TerrainGlobalOptions* _terrainGlobals;

		Ogre::TerrainGroup* _terrainGroup;

		Ogre::SceneManager* _sceneMgr;

		Ogre::Root* _ogreRoot;

		Ogre::Real _mapSize, _worldSize;

		bool _terrainsImported;

		Logic::CTerrainTile** _terrainList;
		int _nTerrains;

		Logic::CGridMap* _terrainMap;

		void defineTerrain(long x, long y);

		void initBlendMaps(Ogre::Terrain* terrain);

		void configureTerrainDefaults();

		void configureShadows();

	}; // class CTerrain

} // namespace Graphics

#endif // __Graphics_Terrain_H
