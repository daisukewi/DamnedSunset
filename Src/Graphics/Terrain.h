//---------------------------------------------------------------------------
// Terrain.h
//---------------------------------------------------------------------------

/**
@file Terrain.h

Contiene la declaración de la clase que define un terreno.

@see Graphics::CTerrain

@author Daniel Flamenco
@date Marzo, 2012
*/

#ifndef __Graphics_Terrain_H
#define __Graphics_Terrain_H

#include <list>
#include <OgrePrerequisites.h>

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class TerrainGlobalOptions;
	class TerrainGroup;
	class Terrain;
	class Light;
	class FrameEvent;
	class SceneManager;
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
		CTerrain(Ogre::SceneManager* sceneMgr, int terrainSize);
		~CTerrain();

	private:
		Ogre::TerrainGlobalOptions* mTerrainGlobals;
		Ogre::TerrainGroup* mTerrainGroup;
		Ogre::SceneManager* mSceneMgr;
		Ogre::Root* mRoot;
		Ogre::Real _mapSize, _worldSize;
		bool mTerrainsImported;

		void defineTerrain(long x, long y);
		void initBlendMaps(Ogre::Terrain* terrain);
		void configureTerrainDefaults();
		


	}; // class CTerrain

} // namespace Graphics

#endif // __Graphics_Terrain_H
