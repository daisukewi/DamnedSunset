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
		CTerrain();
		~CTerrain();

	private:
		Ogre::TerrainGlobalOptions* mTerrainGlobals;
		Ogre::TerrainGroup* mTerrainGroup;
		Ogre::SceneManager* mSceneMgr;
		bool mTerrainsImported;

		void defineTerrain(long x, long y);
		void initBlendMaps(Ogre::Terrain* terrain);
		void configureTerrainDefaults();

	protected:
		virtual void createFrameListener(void);
		virtual void destroyScene(void);

	}; // class CTerrain

} // namespace Graphics

#endif // __Graphics_Terrain_H
