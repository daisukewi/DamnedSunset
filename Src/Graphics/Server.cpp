//---------------------------------------------------------------------------
// Server.cpp
//---------------------------------------------------------------------------

/**
@file Server.cpp

Contiene la implementación de la clase principal de gráficos, la que permite crear
la ventana, etc.

@see Graphics::CServer

@author David Llansó
@date Julio, 2010
*/

#include "Server.h"
#include "Scene.h"

#include "BaseSubsystems/Server.h"
#include "BaseSubsystems/Math.h"


#include "Graphics\Scene.h"
#include "Graphics\Camera.h"
#include "Graphics\Terrain.h"

#include <assert.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include "OgreParticleSystem.h"
#include "OgreSceneNode.h"

namespace Graphics 
{
	CServer *CServer::_instance = 0;

	CServer::CServer() : _root(0), _renderWindow(0), _activeScene(0), _dummyScene(0), _numParticles(30)
	{
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");

		_instance = this;

		for (int i =0; i < _numParticles;i++){
			_particleNode[i] = 0;
		}

		_countParticles = 0;
		_particleToDelete = 0;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer() 
	{
		assert(_instance);

		_instance = 0;

	} // ~CServer

	//--------------------------------------------------------

	bool CServer::Init() 
	{
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");

		new CServer();

		if (!_instance->open())
		{
			Release();
			return false;
		}

		return true;

	} // Init

	//--------------------------------------------------------

	void CServer::Release()
	{
		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		if(!BaseSubsystems::CServer::getSingletonPtr())
			return false;

		_root = BaseSubsystems::CServer::getSingletonPtr()->getOgreRoot();

		_renderWindow = BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow();

		// Creamos la escena dummy para cuando no hay ninguna activa.
		_dummyScene = createScene("dummy_scene");
		
		// Por defecto la escena activa es la dummy
		setScene(_dummyScene);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		if(_activeScene)
		{
			_activeScene->deactivate();
			_activeScene = 0;
		}
		while(!_scenes.empty())
		{
			removeScene(_scenes.begin());
		}

	} // close

	//--------------------------------------------------------
		
	typedef std::pair<std::string,CScene*> TStringScenePar;

	CScene* CServer::createScene(const std::string& name)
	{
		//Nos aseguramos de que no exista ya una escena con este nombre.
		assert(_scenes.find(name)==_scenes.end() && 
			"Ya se ha creado una escena con este nombre.");

		CScene *scene = new CScene(name);
		TStringScenePar ssp(name,scene);
		_scenes.insert(ssp);
		return scene;

	} // createScene

	//--------------------------------------------------------

	void CServer::removeScene(CScene* scene)
	{
		// Si borramos la escena activa tenemos que quitarla.
		if(_activeScene == scene)
			_activeScene = 0;
		_scenes.erase(scene->getName());
		delete scene;

	} // removeScene

	//--------------------------------------------------------

	void CServer::removeScene(const std::string& name)
	{
		CScene* scene = (*_scenes.find(name)).second;
		removeScene(scene);

	} // removeScene

	//--------------------------------------------------------

	void CServer::removeScene(TScenes::const_iterator iterator)
	{
		CScene* scene = (*iterator).second;
		// Si borramos la escena activa tenemos que quitarla.
		if(_activeScene == scene)
			_activeScene = 0;
		_scenes.erase(iterator);
		delete scene;

	} // removeScene

	//--------------------------------------------------------

	void CServer::setScene(CScene* scene)
	{
		// En caso de que hubiese una escena activa la desactivamos.
		if(_activeScene)
			_activeScene->deactivate();

		if(scene)
		{
			// Sanity check. Nos aseguramos de que la escena pertenezca 
			// al servidor. Aunque nadie más puede crear escenas...
			assert((*_scenes.find(scene->getName())).second == scene && 
				"Esta escena no pertenece al servidor");

			_activeScene = scene;
		}
		// Si se añade NULL ponemos la escena dummy.
		else
			_activeScene = _dummyScene;

		_activeScene->activate();

	} // createScene

	//--------------------------------------------------------

	void CServer::setScene(const std::string& name)
	{
		// En caso de que hubiese una escena activa la desactivamos.
		if(_activeScene)
			_activeScene->deactivate();

		// Nos aseguramos de que exista una escena con este nombre.
		assert(_scenes.find(name) != _scenes.end() && 
			"Ya se ha creado una escena con este nombre.");
		_activeScene = (*_scenes.find(name)).second;

		_activeScene->activate();

	} // createScene

	//--------------------------------------------------------

	CTerrain* CServer::generateTerrain(CScene* scene, int width, int height)
	{
		CTerrain* terrain = new CTerrain(scene->getSceneMgr(), width, height);
		return terrain;

	} // generateTerrain

	//--------------------------------------------------------

	void CServer::tick(float secs) 
	{
		if(_activeScene != _dummyScene)
			_activeScene->tick(secs);
		if(_root)
		{
			// Actualizamos todas las ventanas de reenderizado.
			Ogre::WindowEventUtilities::messagePump();
			// Reenderizamos un frame
			_root->renderOneFrame(secs);
		}
	} // tick

	//--------------------------------------------------------

	Ray CServer::getCameraToViewportRay(float screenx, float screeny)
	{
		if (_activeScene)
		{
			Graphics::CCamera* camera =  _activeScene->getCamera();
			Ray mouseRay = camera->getCamera()->getCameraToViewportRay(screenx,screeny);
			return mouseRay;
		}
		
	} //getCameraToViewportRay

	void CServer::createParticleEffect(std::string &effect, Vector3 &point)
	{
		assert(!_particleNode[_countParticles] && "No existe espacio para crear más efectos de partículas.");

		std::stringstream auxString1;
		auxString1 << effect << "_name" << _countParticles;
		
		//crear la partícula
		_particleSystem[_countParticles] = _activeScene->getSceneMgr()->createParticleSystem(auxString1.str(), effect);
		//Ogre::SceneNode* particleNode = _activeScene->getSceneMgr()->getRootSceneNode()->createChildSceneNode(effect + "_node");
		
		//Crear el nodo de escena que contendrá la partícula
		std::stringstream auxString2;
		auxString2 << effect <<"_node"<<_countParticles;
		_particleNode[_countParticles] = _activeScene->getSceneMgr()->getRootSceneNode()->createChildSceneNode(auxString2.str());
		_particleNode[_countParticles]->setPosition(point);
		_particleNode[_countParticles]->attachObject(_particleSystem[_countParticles]);

		_countParticles++;
		if(_countParticles == _numParticles)
			_countParticles = 0;

		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(5000, this);
	}

	void CServer::timeElapsed()
	{
		_particleNode[_particleToDelete]->detachAllObjects();
		_activeScene->getSceneMgr()->destroySceneNode(_particleNode[_particleToDelete]);
		_particleNode[_particleToDelete] = 0;

		_activeScene->getSceneMgr()->destroyParticleSystem(_particleSystem[_particleToDelete]);
		_particleSystem[_particleToDelete] = 0;

		_particleToDelete++;
		if (_particleToDelete == _numParticles)
			_particleToDelete = 0;
	}

} // namespace Graphics
