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

#include "Logic/Maps/TerrainTile.h"
#include "Logic/Maps/GridMap.h"

namespace Graphics 
{
	CTerrain::CTerrain(Ogre::SceneManager* sceneMgr, std::list<Logic::CTerrainTile*>* terrainList, Logic::CGridMap* terrainMap)
	{
		_sceneMgr = sceneMgr;
		_terrainMap = terrainMap;
		_worldSize = _terrainMap->getMapSize();
		_mapSize = 257.0f;
		_terrainsImported = false;

		_nTerrains = terrainList->size();
		_terrainList = new Logic::CTerrainTile*[_nTerrains];

		int i = 0;
		std::list<Logic::CTerrainTile*>::iterator terrain_tile = terrainList->begin();
		for (int i = 0; i < _nTerrains; ++i)
		{
			_terrainList[i] = (*terrain_tile);
			++terrain_tile;
		}

		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

		// TerrainSystem initialization..
		printf("Terrain: Creating new terrain.\n");
		_terrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

		_terrainGroup = OGRE_NEW Ogre::TerrainGroup(_sceneMgr, Ogre::Terrain::ALIGN_X_Z, _mapSize, _worldSize);
		_terrainGroup->setFilenameConvention(Ogre::String("DamnedSunsetTerrain"), Ogre::String("dat"));
		_terrainGroup->setOrigin(Ogre::Vector3::ZERO);

		configureTerrainDefaults();

		for (long x = 0; x <= 0; ++x)
			for (long y = 0; y <= 0; ++y)
				defineTerrain(x, y);

		// sync load since we want everything in place when we start
		_terrainGroup->loadAllTerrains(true);

		if (_terrainsImported)
		{
			printf("Terrain: terrain imported, blending it.\n");
			Ogre::TerrainGroup::TerrainIterator ti = _terrainGroup->getTerrainIterator();
			while(ti.hasMoreElements())
			{
				Ogre::Terrain* t = ti.getNext()->instance;
				initBlendMaps(t);
			}
		}

		_terrainGroup->freeTemporaryResources();

		while (_terrainGroup->isDerivedDataUpdateInProgress());
		_terrainGroup->saveAllTerrains(true);

	} // CTerrain

	//--------------------------------------------------------

	CTerrain::~CTerrain()
	{
		OGRE_DELETE _terrainGroup;
		OGRE_DELETE _terrainGlobals;

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
		Ogre::String filename = _terrainGroup->generateFilename(x, y);

		if (Ogre::ResourceGroupManager::getSingleton().resourceExists(_terrainGroup->getResourceGroup(), filename))
		{
			printf("Terrain: coordinate data loaded from file.\n");
			_terrainGroup->defineTerrain(x, y);
		}
		else
		{
			//@TODO: Cuando esté en release mostrar un error en vez de generar el terreno.
			printf("Terrain: Generating a new terrain in that coord.\n");
			Ogre::Image img;
			getTerrainImage(x % 2 != 0, y % 2 != 0, img);
			_terrainGroup->defineTerrain(x, y, &img);
			_terrainsImported = true;
		}
	}

	//-------------------------------------------------------------------------------------

	void CTerrain::initBlendMaps(Ogre::Terrain* terrain)
	{
		Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
		Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
		Ogre::Real minHeight0 = 1;
		Ogre::Real fadeDist0 = 1;
		Ogre::Real minHeight1 = 3;
		Ogre::Real fadeDist1 = 2;
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
				*pBlend1++ = 0;//val;
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
		_terrainGlobals->setMaxPixelError(8);
		// testing composite map
		_terrainGlobals->setCompositeMapDistance(3000);

		// Important to set these so that the terrain knows what to use for derived (non-realtime) data
		_terrainGlobals->setLightMapDirection(Vector3(0.0, -1.0, 0.0));
		_terrainGlobals->setCompositeMapAmbient(Ogre::ColourValue(0.2, 0.2, 0.2));
		_terrainGlobals->setCompositeMapDiffuse(Ogre::ColourValue::White);
		_terrainGlobals->setCastsDynamicShadows(true);

		// Configure default import settings for if we use imported image
		Ogre::Terrain::ImportData& defaultimp = _terrainGroup->getDefaultImportSettings();
		defaultimp.terrainSize = _mapSize;
		defaultimp.worldSize = _worldSize;
		defaultimp.inputScale = 600;
		defaultimp.minBatchSize = 33;
		defaultimp.maxBatchSize = 65;

		// textures
		defaultimp.layerList.resize(_nTerrains);
		for (int i = 0; i < _nTerrains; ++i)
		{
			defaultimp.layerList[i].worldSize = _terrainList[i]->getTextureSize();
			defaultimp.layerList[i].textureNames.push_back(_terrainList[i]->getDifuseMap());
			defaultimp.layerList[i].textureNames.push_back(_terrainList[i]->getNormalMap());
		}

	}

} // namespace Graphics
