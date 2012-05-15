/**
@file Server.cpp

Contiene la implementaci�n de la clase CServer, Singleton que se encarga de
la gesti�n de la l�gica del juego.

@see Logic::CServer

@author David Llans�
@date Agosto, 2010
*/

#include "Server.h"
#include "Logic/Maps/Map.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapParser.h"

#include "BaseSubsystems/Math.h"

#include "GUI/Server.h"
#include "Graphics/Server.h"
#include "Physics/Server.h"

#include <cassert>

namespace Logic {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer() : _map(0)
	{
		_instance = this;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicializaci�n de Logic::CServer no permitida!");

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
		assert(_instance && "Logic::CServer no est� inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		// Inicializamos el parser de mapas.
		if (!Map::CMapParser::Init())
			return false;

		// Inicializamos la factor�a de entidades.
		if (!Logic::CEntityFactory::Init())
			return false;

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		unLoadLevel();

		Logic::CEntityFactory::Release();
		
		Map::CMapParser::Release();

	} // close

	//--------------------------------------------------------

	bool CServer::loadLevel(const std::string &mapFilename, const std::string &archFilename)
	{
		// solo admitimos un mapa cargado, si iniciamos un nuevo nivel 
		// se borra el mapa anterior.
		unLoadLevel();

		if(_map = CMap::createMapFromFile(mapFilename, archFilename))
		{
			//_map->getGridMap()->ShowDebugTiles(_map);

			return true;
		}

		return false;

	} // loadLevel

	//--------------------------------------------------------

	void CServer::unLoadLevel()
	{
		if(_map)
		{
			_map->deactivate();
			delete _map;
			_map = 0;
		}
		_player = 0;

	} // unLoadLevel

	//---------------------------------------------------------

	bool CServer::activateMap() 
	{
		return _map->activate();

	} // activateMap

	//---------------------------------------------------------

	void CServer::deactivateMap() 
	{
		_map->deactivate();

	} // deactivateMap

	//---------------------------------------------------------

	void CServer::tick(unsigned int msecs) 
	{
		// Eliminamos las entidades que se han marcado para ser eliminadas.
		Logic::CEntityFactory::getSingletonPtr()->deleteDefferedEntities();

		_map->tick(msecs);

	} // tick

	//---------------------------------------------------------

	Logic::CEntity* CServer::raycastFromViewport (Ogre::Vector3* point, unsigned groups, float maxDist) const
	{
		Vector2 mousePos = GUI::CServer::getSingletonPtr()->getMouseRelPos();
		// Lanzar un rayo desde la camara hasta el plano del escenario.
		Ray mouseRay = Graphics::CServer::getSingletonPtr()->getCameraToViewportRay(mousePos.x, mousePos.y);

		return Physics::CServer::getSingletonPtr()->raycastGroup(mouseRay, point, (Physics::TPhysicGroup)groups, maxDist);
	}

} // namespace Logic
