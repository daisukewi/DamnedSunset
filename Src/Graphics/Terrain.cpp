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

#include <stdio.h>


namespace Graphics 
{
	CTerrain::CTerrain(Ogre::SceneManager* sceneMgr, int width, int height)
	{
		mSceneMgr = sceneMgr;
		_worldSize = width;
		_mapSize = _worldSize / 2;

		mTerrainsImported = false;

		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

		// TerrainSystem initialization..
		printf("Terrain: Creating new terrain.\n");
		mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

		mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
		mTerrainGroup->setFilenameConvention(Ogre::String("DamnedSunsetTerrain"), Ogre::String("dat"));
		mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

		configureTerrainDefaults();

		for (long x = 0; x <= 0; ++x)
			for (long y = 0; y <= 0; ++y)
				defineTerrain(x, y);

		// sync load since we want everything in place when we start
		mTerrainGroup->loadAllTerrains(true);

		if (mTerrainsImported)
		{
			printf("Terrain: terrain imported, blending it.\n");
			Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
			while(ti.hasMoreElements())
			{
				Ogre::Terrain* t = ti.getNext()->instance;
				initBlendMaps(t);
			}
		}

		mTerrainGroup->freeTemporaryResources();

	} // CTerrain

	//--------------------------------------------------------

	CTerrain::~CTerrain()
	{
		OGRE_DELETE mTerrainGroup;
		OGRE_DELETE mTerrainGlobals;

	} // ~CTerrain

	//--------------------------------------------------------

	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
	{
		img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		if (flipX)
			img.flipAroundY();
		if (flipY)
			img.flipAroundX();
	}

	//-------------------------------------------------------------------------------------

	void CTerrain::defineTerrain(long x, long y)
	{
		//std::cout << "Terrain: Defining terrain for x: " << x << " & y: " << y;
		Ogre::String filename = mTerrainGroup->generateFilename(x, y);
		if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
		{
			printf("Terrain: coordinate data loaded from file.\n");
			mTerrainGroup->defineTerrain(x, y);
		}
		else
		{
			printf("Terrain: Generating a new terrain in that coord.\n");
			Ogre::Image img;
			getTerrainImage(x % 2 != 0, y % 2 != 0, img);
			mTerrainGroup->defineTerrain(x, y, &img);
			mTerrainsImported = true;
		}
	}

	//-------------------------------------------------------------------------------------

	void CTerrain::initBlendMaps(Ogre::Terrain* terrain)
	{
		Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
		Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
		Ogre::Real minHeight0 = 60;
		Ogre::Real fadeDist0 = 20;
		Ogre::Real minHeight1 = 130;
		Ogre::Real fadeDist1 = 15;
		float* pBlend0 = blendMap0->getBlendPointer();
		float* pBlend1 = blendMap1->getBlendPointer();
		for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
		{
			for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
			{
				Ogre::Real tx, ty;

				blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
				Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
				Ogre::Real val = (height - minHeight0) / fadeDist0;
				val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
				*pBlend0++ = val;

				val = (height - minHeight1) / fadeDist1;
				val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
				*pBlend1++ = val;
			}
		}
		blendMap0->dirty();
		blendMap1->dirty();
		blendMap0->update();
		blendMap1->update();
	}

	//-------------------------------------------------------------------------------------

	void CTerrain::configureTerrainDefaults()
	{
		printf("Terrain: Configuring terrain parameters.\n");

		// Configure global
		mTerrainGlobals->setMaxPixelError(8);
		// testing composite map
		mTerrainGlobals->setCompositeMapDistance(3000);

		// Important to set these so that the terrain knows what to use for derived (non-realtime) data
		mTerrainGlobals->setLightMapDirection(Vector3(0.55, -0.3, 0.75));
		mTerrainGlobals->setCompositeMapAmbient(Ogre::ColourValue(0.2, 0.2, 0.2));
		mTerrainGlobals->setCompositeMapDiffuse(Ogre::ColourValue::White);

		// Configure default import settings for if we use imported image
		Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
		defaultimp.terrainSize = 513;
		defaultimp.worldSize = 12000.0f;
		defaultimp.inputScale = 600;
		defaultimp.minBatchSize = 33;
		defaultimp.maxBatchSize = 65;
		// textures
		defaultimp.layerList.resize(3);
		defaultimp.layerList[0].worldSize = 100;
		defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
		defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
		defaultimp.layerList[1].worldSize = 30;
		defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
		defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
		defaultimp.layerList[2].worldSize = 200;
		defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
		defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	}


} // namespace Graphics
