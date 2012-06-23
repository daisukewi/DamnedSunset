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
		_mapSize = 129.0f;
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
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(1);

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

	float CTerrain::getHeightAtWorldPosition(Ogre::Vector3 vPos)
	{
		return _terrainGroup->getHeightAtWorldPosition(vPos);
	}

	//--------------------------------------------------------

	bool CTerrain::wasTerrainsImported()
	{
		return _terrainsImported;
	}

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
		int nBlendMaps = _nTerrains - 1;
		Ogre::TerrainLayerBlendMap** blendMaps = new Ogre::TerrainLayerBlendMap*[_nTerrains];
		float** pBlend = new float*[nBlendMaps];

		for (int i = 0; i < nBlendMaps; ++i)
		{
			blendMaps[i] = terrain->getLayerBlendMap(i + 1);
			pBlend[i] = blendMaps[i]->getBlendPointer();
		}

		Ogre::Real fadeDist = 1;

		for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
		{
			for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
			{
				Ogre::Real tx, ty;

				blendMaps[0]->convertImageToTerrainSpace(x, y, &tx, &ty);
				Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);

				int j = 0;
				for (int i = 0; i < nBlendMaps; ++i)
				{
					if (_terrainList[j]->isBaseTexture()) j += 1;
					Ogre::Real val = (height - _terrainList[j]->getBlendHeight()) / fadeDist;
					val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
					if (height > _terrainList[j]->getBlendHeightMax()) val = (Ogre::Real)0;
					*pBlend[i]++ = val;
					++j;
				}
			}
		}

		for (int i = 0; i < nBlendMaps; ++i)
			blendMaps[i]->dirty();
		for (int i = 0; i < nBlendMaps; ++i)
			blendMaps[i]->update();
	}

	//-------------------------------------------------------------------------------------

	void CTerrain::configureTerrainDefaults()
	{
		printf("Terrain: Configuring terrain parameters.\n");

		// Configure global
		_terrainGlobals->setMaxPixelError(8);
		// testing composite map
		_terrainGlobals->setCompositeMapDistance(6000);

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
		int i = 0, j = 1;
		while (i < _nTerrains)
		{
			if (_terrainList[i]->isBaseTexture())
			{
				defaultimp.layerList[0].worldSize = _terrainList[i]->getTextureSize();
				defaultimp.layerList[0].textureNames.push_back(_terrainList[i]->getDifuseMap());
				defaultimp.layerList[0].textureNames.push_back(_terrainList[i]->getNormalMap());
			}
			else
			{
				defaultimp.layerList[j].worldSize = _terrainList[i]->getTextureSize();
				defaultimp.layerList[j].textureNames.push_back(_terrainList[i]->getDifuseMap());
				defaultimp.layerList[j].textureNames.push_back(_terrainList[i]->getNormalMap());
				++j;
			}
			++i;
		}

	}

} // namespace Graphics
