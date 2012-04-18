//---------------------------------------------------------------------------
// Terrain.cpp
//---------------------------------------------------------------------------

/**
@file Terrain.cpp

Contiene la implementación de la clase que define un terreno

@see Graphics::CTerrain

@author Daniel Flamenco
@date Marzo, 2012
*/

#include "Terrain.h"

#include "Server.h"
#include "Scene.h"

#include <assert.h>
#include <OgreRoot.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>


namespace Graphics 
{
	CTerrain::CTerrain()
	{
		//mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

		//mSceneMgr = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr();

		//mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
		//mTerrainGroup->setFilenameConvention(Ogre::String("DamnedSunsetTerrain"), Ogre::String("dat"));
		//mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

		//configureTerrainDefaults();

		//for (long x = 0; x <= 0; ++x)
		//	for (long y = 0; y <= 0; ++y)
		//		defineTerrain(x, y);

		//// sync load since we want everything in place when we start
		//mTerrainGroup->loadAllTerrains(true);

		//if (mTerrainsImported)
		//{
		//	Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		//	while(ti.hasMoreElements())
		//	{
		//		Ogre::Terrain* t = ti.getNext()->instance;
		//		initBlendMaps(t);
		//	}
		//}

		//mTerrainGroup->freeTemporaryResources();

	} // CTerrain

	//--------------------------------------------------------

	CTerrain::~CTerrain()
	{
		

	} // ~CTerrain

	//--------------------------------------------------------

	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
	{

	}
	//-------------------------------------------------------------------------------------
	void CTerrain::defineTerrain(long x, long y)
	{

	}
	//-------------------------------------------------------------------------------------
	void CTerrain::initBlendMaps(Ogre::Terrain* terrain)
	{

	}
	//-------------------------------------------------------------------------------------
	void CTerrain::configureTerrainDefaults()
	{
		//// Configure global
		//mTerrainGlobals->setMaxPixelError(8);
		//// testing composite map
		//mTerrainGlobals->setCompositeMapDistance(3000);

		////TODO: Fix this hack... and all hacks xD
		//Ogre::Light* light = mSceneMgr->getLight("directional light");

		//// Important to set these so that the terrain knows what to use for derived (non-realtime) data
		//mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
		//mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
		//mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

		//// Configure default import settings for if we use imported image
		//Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
		//defaultimp.terrainSize = 513;
		//defaultimp.worldSize = 12000.0f;
		//defaultimp.inputScale = 600;
		//defaultimp.minBatchSize = 33;
		//defaultimp.maxBatchSize = 65;
		//// textures
		//defaultimp.layerList.resize(3);
		//defaultimp.layerList[0].worldSize = 100;
		//defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
		//defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
		//defaultimp.layerList[1].worldSize = 30;
		//defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
		//defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
		//defaultimp.layerList[2].worldSize = 200;
		//defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
		//defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	}


} // namespace Graphics
