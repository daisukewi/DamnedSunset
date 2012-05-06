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

#include "Physics/PhysicTerrain.h"

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

		// Rellena las casillas de tipo Grid del mapa con la info de tileMatrix.
		map->getGridMap()->FillTileData(map, tileMatrix);

		// Preparo las tablas de lua para que las entidades las rellenen en sus respectivos spawns.
		ScriptManager::CServer::getSingletonPtr()->executeScript("players = {}");
		ScriptManager::CServer::getSingletonPtr()->executeScript("spawners = {}");
		ScriptManager::CServer::getSingletonPtr()->executeScript("enemies = {}");

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
					map->addTerrainTile(terrain_tile);
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
		Graphics::CTerrain* terrain = _scene->generateTerrain(_terrainList, _gridMap);

		//if (!terrain->wasTerrainsImported())
		return;
		
		//////////////////////////////////////////////////////////////////////////
		/////   BAKING THE PHYSICS TERRAIN
		//////////////////////////////////////////////////////////////////////////

		// Create a vertex buffer for the terrain physics
		int nVertexCount = _gridMap->getMapSize();

		Vector3* aVertex = new Vector3[ nVertexCount ];

		// And an index buffer to define the triangles:
		int nNumSquares = (_gridMap->getMapWidth() - 1) * (_gridMap->getMapHeight() - 1);
		int nNumTriangles = nNumSquares * 2;
		int nNumIndiciesPerTriangle = 3;
		int nIndexCount = nNumTriangles * nNumIndiciesPerTriangle;

		// According to a post I read, NxTriangleMesh uses 16-bit indicies,
		// so anything more than that will overflow.
		assert( nVertexCount <= 65536 );  // 2^16

		unsigned int* aIndex = new unsigned int[ nIndexCount ];   

		// Make sure we got valid triangle data.
		if ( nVertexCount < 3 || nIndexCount < 3 || !aVertex || !aIndex )
		{
			assert( false );
			return;
		}
		// Triangles need 3 indicies, right?
		assert( nIndexCount % 3 == 0 );

		// Populate our vertex and index buffers
		int nTerrainSize = 257; 
		float fStep = _gridMap->getMapSize() / (nTerrainSize - 1);

		// Vertex Data
		for ( int z = 0; z <= _gridMap->getMapHeight() - 1; ++z )
		{
			for ( int x = 0; x <= _gridMap->getMapWidth() - 1; ++x )
			{
				// Extract the vertex data from the graphical terrain, and populate the
				// physics NxTriangleMesh buffers created above.
				Vector3 v3Terrain( x * fStep, 0.f, z * fStep );
				v3Terrain.y = terrain->getHeightAtWorldPosition( v3Terrain );
				// - Make sure we stay within our bounds and start at index 0 by subtracting i_xStart and i_zStart
				aVertex[ x + z ] = v3Terrain;
			}
		}

		// Index Data
		unsigned int* ptr = aIndex;
		for ( int z=0; z < _gridMap->getMapHeight() - 1; ++z )
		{
			for ( int x=0; x < _gridMap->getMapWidth() - 1; ++x )
			{
				// The Ogre 1.8 terrain uses different tessilation for each row.
				// See comments in OgreTerrain.cpp
				//      6---7---8
				//      | \ | \ |
				//      3---4---5
				//      | / | / |
				//      0---1---2

				// We need our x and z to be the 0-based indicies into our vertex array
				int xIndex = x;
				int zIndex = z;

				// This switches up the tessilation every row:
				if ( z%2==0 )
				{
					// Note:  need to be careful about the triangle winding here,
					// if you get it wrong (as I originally did), you will fall through the terrain.
					*ptr++ = ( xIndex   + zIndex     );
					*ptr++ = ( xIndex+1 + (zIndex+1) );
					*ptr++ = ( xIndex+1 + zIndex     );

					*ptr++ = ( xIndex   + zIndex     );
					*ptr++ = ( xIndex   + (zIndex+1) );
					*ptr++ = ( xIndex+1 + (zIndex+1) );
				}
				else
				{
					*ptr++ = ( xIndex   + zIndex     );
					*ptr++ = ( xIndex   + (zIndex+1) );
					*ptr++ = ( xIndex+1 + zIndex     );

					*ptr++ = ( xIndex   + (zIndex+1) );
					*ptr++ = ( xIndex+1 + (zIndex+1) );
					*ptr++ = ( xIndex+1 + zIndex     );
				}
			}
		}
		
		Physics::CPhysicTerrain phys_terrain(nVertexCount, nIndexCount, aVertex, aIndex);

	} // createTerrain

} // namespace Logic
