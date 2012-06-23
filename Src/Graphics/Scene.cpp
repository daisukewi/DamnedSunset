//---------------------------------------------------------------------------
// Scene.cpp
//---------------------------------------------------------------------------

/**
@file Scene.cpp

Contiene la implementaci�n de la clase contenedora de los elementos
de una escena.

@see Graphics::CScene

@author David Llans�
@date Julio, 2010
*/

#include "Scene.h"
#include "Camera.h"
#include "Server.h"
#include "StaticEntity.h"
#include "Terrain.h"

#include "Logic/Maps/TerrainTile.h"
#include "Logic/Maps/GridMap.h"
#include "BaseSubsystems/Server.h"

#include <assert.h>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreStaticGeometry.h>
#include <OgreColourValue.h>

namespace Graphics 
{
	CScene::CScene(const std::string& name) : _viewport(0), 
			_staticGeometry(0), _directionalLight(0), _terrain(0)
	{
//#if defined(_DEBUG)
//		_root->loadPlugin("Plugin_CgProgramManager_d");        
//		_root->loadPlugin("Plugin_OctreeSceneManager_d");
//#else
//		_root->loadPlugin("Plugin_CgProgramManager");        
//		_root->loadPlugin("Plugin_OctreeSceneManager");
//#endif

		_root = BaseSubsystems::CServer::getSingletonPtr()->getOgreRoot();
		_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, name);
		_camera = new CCamera(name,this);
		_name = name;

	} // CScene

	//--------------------------------------------------------

	CScene::~CScene() 
	{
		deactivate();

		if (_terrain)
			delete _terrain;

		_sceneMgr->destroyStaticGeometry(_staticGeometry);
		delete _camera;
		_root->destroySceneManager(_sceneMgr);

	} // ~CScene

	//--------------------------------------------------------

	bool CScene::addEntity(CEntity* entity)
	{
		if(!entity->attachToScene(this))
			return false;
		_dynamicEntities.push_back(entity);
		return true;

	} // addEntity

	//--------------------------------------------------------

	bool CScene::addStaticEntity(CStaticEntity* entity)
	{
		if(!entity->attachToScene(this))
			return false;
		_staticEntities.push_back(entity);
		return true;

	} // addStaticEntity

	//--------------------------------------------------------

	void CScene::removeEntity(CEntity* entity)
	{
		entity->deattachFromScene();
		_dynamicEntities.remove(entity);

	} // addEntity

	//--------------------------------------------------------

	void CScene::removeStaticEntity(CStaticEntity* entity)
	{
		entity->deattachFromScene();
		_staticEntities.remove(entity);

	} // addStaticEntity

	//--------------------------------------------------------

	void CScene::activate()
	{
		buildStaticGeometry();
		// HACK en pruebas
		_viewport = BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow()
						->addViewport(_camera->getCamera());
		_viewport->setBackgroundColour(Ogre::ColourValue::Black);

		_sceneMgr->setAmbientLight(Ogre::ColourValue(0.75f, 0.75f, 0.96f));

		// Adem�s de la luz ambiente creamos una luz direccional que 
		// hace que se vean mejor los vol�menes de las entidades.
		_directionalLight = _sceneMgr->createLight("directional light");
		_directionalLight->setDiffuseColour(.5f,.5f,.5f);
		_directionalLight->setSpecularColour(.5f,.5f,.5f);
		_directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		_directionalLight->setDirection(0, -150, 0);
		_directionalLight->setType(Ogre::Light::LT_POINT);
		_directionalLight->setPosition(0, 500, 0);

	} // activate

	//--------------------------------------------------------

	void CScene::deactivate()
	{
		if(_directionalLight)
		{
			_sceneMgr->destroyLight(_directionalLight);
			_directionalLight = 0;
		}
		if(_viewport)
		{
			BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow()->
					removeViewport(_viewport->getZOrder());
			_viewport = 0;
		}

	} // deactivate
	
	//--------------------------------------------------------
	
	void CScene::tick(float secs)
	{	
		TEntityList::const_iterator it = _dynamicEntities.begin();
		TEntityList::const_iterator end = _dynamicEntities.end();
		for(; it != end; it++)
			(*it)->tick(secs);

	} // tick

	//--------------------------------------------------------

	void CScene::setLightDirection(const float x, const float y, const float z)
	{
		_directionalLight->setDirection(x, y, z);

	} // setLightDirection

	//--------------------------------------------------------

	void CScene::setAmbientLight(const float r, const float g, const float b)
	{
		_sceneMgr->setAmbientLight(Ogre::ColourValue(r, g, b));

	} // setAmbientLight

	//--------------------------------------------------------

	CTerrain* CScene::generateTerrain(std::list<Logic::CTerrainTile*>* terrainList, Logic::CGridMap* terrainMap)
	{
		if (_terrain)
			delete(_terrain);

		_terrain = new CTerrain(_sceneMgr, terrainList, terrainMap);

		return _terrain;

	} // generateTerrain

	//--------------------------------------------------------


	void CScene::removeBillboardset(Ogre::BillboardSet* b) {
		_sceneMgr->destroyBillboardSet(b);
	}


	void CScene::buildStaticGeometry()
	{
		if(!_staticGeometry && !_staticEntities.empty())
		{
			_staticGeometry = 
					_sceneMgr->createStaticGeometry("static");

			TStaticEntityList::const_iterator it = _staticEntities.begin();
			TStaticEntityList::const_iterator end = _staticEntities.end();
			for(; it != end; it++)
				(*it)->addToStaticGeometry();

			_staticGeometry->build();
		}

	} // buildStaticGeometry

} // namespace Graphics
