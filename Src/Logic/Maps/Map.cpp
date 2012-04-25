/**
@file Map.cpp

Contiene la implementación de la clase CMap, Un mapa lógico.

@see Logic::Map

@author David Llansó
@date Agosto, 2010
*/

#include "Map.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/TerrainTile.h"
#include "EntityFactory.h"
#include "GridMap.h"

#include "Map/MapParser.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"
#include "Graphics/Terrain.h"

#include "AI/Server.h"

#include "ScriptManager/Server.h"


#include <cassert>

namespace Logic {
	
	CMap* CMap::createMapFromFile(const std::string &mapFilename, const std::string &archFilename)
	{
		// Parseamos el fichero
		if(!Map::CMapParser::getSingletonPtr()->parseFile(mapFilename, archFilename))
		{
			assert(!"No se ha podido parsear el mapa.");
			return false;
		}

		// Si se ha realizado con éxito el parseo creamos el mapa.
		CMap *map = new CMap(mapFilename);

		// Extraemos las casillas del parseo.
		Map::CMapParser::TTileMatrix tileMatrix = Map::CMapParser::getSingletonPtr()->getTileMatrix();

		// Extraemos las entidades del parseo.
		Map::CMapParser::TEntityList entityList = Map::CMapParser::getSingletonPtr()->getEntityList();
		// Obtenemos la factoría.
		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		// Obtengo la entidad de tipo "Grid" para poder inicializar el mapa antes de empezar a poner entidades.
		Map::CEntity *gridEntity = Map::CMapParser::getSingletonPtr()->getEntity("Grid");
		if (!gridEntity)
		{
			assert(!"No se ha podido inicializar el mapa porque no se han podido obtener sus atributos.");
			return false;
		}

		int width = gridEntity->hasAttribute("width") ? gridEntity->getIntAttribute("width") : 0;
		int height = gridEntity->hasAttribute("height") ? gridEntity->getIntAttribute("height") : 0;
		int grid_size = gridEntity->hasAttribute("grid_size") ? gridEntity->getIntAttribute("grid_size") : 0;

		// Con la entidad de tipo "Grid" inicializo el mapa pasándole las dimensiones y el tamaño de celda.
		if ((width != 0) && (height != 0) && (grid_size != 0))
		{
			map->getGridMap()->initMap(width, height, grid_size);
		
		} else {
			assert(!"No se han encontrado dimensiones y/o tamaño del grid del mapa.");
			return false;
		}

		// @TODO Rellenar las casillas de tipo Grid del mapa con la info de tileMatrix
		// @TODO cocinar el gridMap para que recoja las celdas ocupadas por el terreno abrupto.
		map->getGridMap()->FillTileData(&tileMatrix);

		Map::CMapParser::TEntityList::const_iterator it, end;
		it = entityList.begin();
		end = entityList.end();

		// Creamos todas las entidades lógicas.
		for(; it != end; it++)
		{
			// Me salto la entidad de tipo "Grid" porque ya la he procesado anteriormente para hacer la inicialización del mapa.
			if (!((*it)->getType() == "Grid"))
			{
				if (!entityFactory->createEntity((*it),map)) 
				{
					CTerrainTile* terrain_tile = new CTerrainTile((*it)->getType());
					terrain_tile->FillData(*it);
				}
			}
		}

		// Crea el terreno con la info de las casillas del Grid.
		map->createTerrain(height * grid_size);

		return map;

	} // createMapFromFile

	//--------------------------------------------------------

	CMap::CMap(const std::string &name)
	{
		_name = name;
		_scene = Graphics::CServer::getSingletonPtr()->createScene(name);
		_gridMap = new CGridMap();
		_terrainList = new std::list<CTerrainTile*>();

		// Se le añade el mapa al servidor de IA para tener una referencia
		// y poder calcular rutas con A*
		AI::CServer::getSingletonPtr()->getNavigationMap()->setGridMap(_gridMap);

	} // CMap

	//--------------------------------------------------------

	CMap::~CMap()
	{
		destroyAllEntities();

		AI::CServer::getSingletonPtr()->getNavigationMap()->setGridMap(NULL);
		delete(_gridMap);
		delete(_terrainList);

		if(Graphics::CServer::getSingletonPtr())
			Graphics::CServer::getSingletonPtr()->removeScene(_scene);

	} // ~CMap

	//--------------------------------------------------------

	bool CMap::activate()
	{
		Graphics::CServer::getSingletonPtr()->setScene(_scene);

		TEntityMap::const_iterator it, end;
		end = _entityMap.end();
		it = _entityMap.begin();

		bool correct = true;

		// Activamos todas las entidades registradas en el mapa.
		for(; it != end; it++)
			correct = (*it).second->activate() && correct;

		return correct;

	} // getEntity

	//--------------------------------------------------------

	void CMap::deactivate()
	{
		TEntityMap::const_iterator it, end;
		end = _entityMap.end();
		it = _entityMap.begin();

		// Desactivamos todas las entidades activas registradas en el mapa.
		for(; it != end; it++)
			if((*it).second->isActivated())
				(*it).second->deactivate();

		Graphics::CServer::getSingletonPtr()->setScene(0);

	} // getEntity

	//---------------------------------------------------------

	void CMap::tick(unsigned int msecs) 
	{
		TEntityMap::const_iterator it;

		for( it = _entityMap.begin(); it != _entityMap.end(); ++it )
			(*it).second->tick(msecs);

	} // tick

	//--------------------------------------------------------

	typedef std::pair<TEntityID,CEntity*> TEntityPair;

	void CMap::addEntity(CEntity *entity)
	{
		if(_entityMap.count(entity->getEntityID()) == 0)
		{
			TEntityPair elem(entity->getEntityID(),entity);
			_entityMap.insert(elem);
		}

	} // addEntity

	//--------------------------------------------------------

	void CMap::removeEntity(CEntity *entity)
	{
		if(_entityMap.count(entity->getEntityID()) != 0)
		{
			if(entity->isActivated())
				entity->deactivate();
			entity->_map = 0;
			_entityMap.erase(entity->getEntityID());
		}

	} // removeEntity

	//--------------------------------------------------------

	void CMap::destroyAllEntities()
	{
		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		TEntityMap::const_iterator it, end;
		it = _entityMap.begin();
		end = _entityMap.end();

		// Eliminamos todas las entidades. La factoría se encarga de
		// desactivarlas y sacarlas previamente del mapa.
		while(it != end)
		{
			CEntity* entity = (*it).second;
			it++;
			entityFactory->deleteEntity(entity);
		}

		_entityMap.clear();

	} // removeEntity

	//--------------------------------------------------------

	CEntity* CMap::getEntityByID(TEntityID entityID)
	{
		if(_entityMap.count(entityID) == 0)
			return 0;
		return (*_entityMap.find(entityID)).second;

	} // getEntityByID

	//--------------------------------------------------------

	CEntity* CMap::getEntityByName(const std::string &name, CEntity *start)
	{
		TEntityMap::const_iterator it, end;
		end = _entityMap.end();

		// Si se definió entidad desde la que comenzar la búsqueda 
		// cogemos su posición y empezamos desde la siguiente.
		if (start)
		{
			it = _entityMap.find(start->getEntityID());
			// si la entidad no existe devolvemos NULL.
			if(it == end)
				return 0;
			it++;
		}
		else
			it = _entityMap.begin();

		for(; it != end; it++)
		{
			// si hay coincidencia de nombres devolvemos la entidad.
			if (!(*it).second->getName().compare(name))
				return (*it).second;
		}
		// si no se encontró la entidad devolvemos NULL.
		return 0;

	} // getEntityByName

	//--------------------------------------------------------

	CEntity* CMap::getEntityByType(const std::string &type, CEntity *start)
	{
		TEntityMap::const_iterator it, end;
		end = _entityMap.end();

		// Si se definió entidad desde la que comenzar la búsqueda 
		// cogemos su posición y empezamos desde la siguiente.
		if (start)
		{
			it = _entityMap.find(start->getEntityID());
			// si la entidad no existe devolvemos NULL.
			if(it == end)
				return 0;
			it++;
		}
		else
			it = _entityMap.begin();

		for(; it != end; it++)
		{
			// si hay coincidencia de nombres devolvemos la entidad.
			if (!(*it).second->getType().compare(type))
				return (*it).second;
		}
		// si no se encontró la entidad devolvemos NULL.
		return 0;

	} // getEntityByType

	//--------------------------------------------------------

	void CMap::addTerrainTile(CTerrainTile* terrain_tile)
	{
		_terrainList->push_back(terrain_tile);
	}

	//--------------------------------------------------------

	void CMap::createTerrain(int mapSize)
	{
		_scene->generateTerrain(_terrainList, mapSize);

	} // generateTerrain

} // namespace Logic
