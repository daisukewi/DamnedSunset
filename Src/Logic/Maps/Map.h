/**
@file Map.h

Contiene la declaración de la clase CMap, Un mapa lógico.

@see Logic::Map

@author David Llansó
@date Agosto, 2010
*/
#ifndef __Logic_Map_H
#define __Logic_Map_H

#include <map>
#include "EntityID.h"
#include "Map/MapParser.h"
#include "Logic/Entity/Entity.h"
#include "GridMap.h"
#include "GridTile.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Logic 
{
	class CEntity;
	class CTerrainTile;
}

namespace Graphics 
{
	class CScene;
	class CTerrain;
}

// Declaración de la clase
namespace Logic
{

	/**
	Clase que representa un mapa lógico.
	<p>
	Esta clase se encarga de almacenar todas las entidades del mapa, tanto 
	aquellas que tienen representación gráfica y se ven como entidades
	puramente lógicas. Gestiona la activación y desactivación de éstas y
	tiene también métodos para buscar entidades, tanto por su nombre como 
	por su tipo y por su identificador.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CMap
	{
	public:


		/**
		Tipo tabla de entidades de mapa.
		*/
		typedef std::map<TEntityID,CEntity*> TEntityMap;


		/**
		Método factoría que carga un mapa de fichero. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param mapFilename Nombre del archivo de mapa a cargar.
		@param archFilename Nombre del archivo de arquetipos de las entidades a cargar.
		@return Mapa generado.
		*/
		static CMap *createMapFromFile(const std::string &mapFilename, const std::string &archFilename);

		/**
		Constructor.

		@param name Nombre que se le da a este mapa.
		*/
		CMap (const std::string &name);

		/**
		Destructor.
		*/
		~CMap();
		
		/**
		Activa el mapa. Invocará al método activate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true al invocador si todas las entidades se
		activaron sin problemas.
		*/
		bool activate();

		/**
		Desactiva el mapa. Invocará al método deactivate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Función llamada en cada frame para que se realicen las funciones
		de actualización adecuadas.
		<p>
		Llamará a los métodos tick() de todas las entidades.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		void tick(unsigned int msecs);

		/**
		Añade una nueva entidad al mapa. Si la entidad ya estaba incluida
		no se hace nada.

		@param entity Entidad a añadir.
		*/
		void addEntity(CEntity *entity);

		/**
		Elimina una entidad del mapa. Si la entidad no estaba incluida
		no se hace nada. La función desactiva previamente la entidad si
		ésta se encontraba activa.

		@note El mapa no se hace responsable de eliminar (con delete) la
		entidad.

		@param entity Entidad a eliminar.
		*/
		void removeEntity(CEntity *entity);

		/**
		Elimina y destruye todas las entidades del mapa dejando la lista 
		de entidades vacía.
		*/
		void destroyAllEntities();

		/**
		Recupera una entidad del mapa a partir de su ID.

		@param entityID ID de la entidad a recuperar.
		@return Entidad con el ID pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByID(TEntityID entityID);

		/**
		Recupera una entidad del mapa a partir de su nombre.

		@param name nombre de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. Útil si se tienen varias entidades con el mismo
		nombre y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByName(const std::string &name, CEntity *start = 0);

		/**
		Recupera una entidad del mapa a partir de su tipo.

		@param type nombre del tipo de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. Útil si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByType(const std::string &type, CEntity *start = 0);
		
		/*
		Recupera una entidad del mapa a partir de su tag

		@param tag tag de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. Útil si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CEntity *getEntityByTag(const std::string &tag, CEntity *start = 0);

		/**
		Crea un nuevo terreno en el mapa con las dimensiones pasadas
		como parámetro.

		@param mapSize tamaño del mapa donde se generará el terreno (M x N)
		*/
		void createTerrain(int mapSize);

		/**
		Añade un nuevo tipo de terreno a la lista de tiles de terreno del mapa.

		@param terrain_tile nuevo tipo de terrenopara añadir a la lista.
		*/
		void addTerrainTile (CTerrainTile* terrain_tile);

		/**
		Devuelve la escena gráfica correspondiente a este mapa.

		@return Escena con las entidades gráficas.
		*/
		Graphics::CScene *getScene() { return _scene; }

		/**
		Devuelve la escena gráfica correspondiente a este mapa.

		@return Escena con las entidades gráficas.
		*/
		CGridMap *getGridMap() { return _gridMap; }

	
		/**
		Envia un mensaje a todas las entidades excepto a la que se pase por parámetro

		@param mensaje a enviar
		@param entidad a la que no se quiere que se envíe el mensaje. Normalmente la misma que lo envía.
		*/
		void sendMessageAll(IMessage *message, Logic::CEntity *entity);


		/**
		Devuelve el map de las entidades

		@return entityMap
		*/
		TEntityMap* getEntityMap(){ return &_entityMap; }

	private:

		/**
		tabla con las entidades del mapa localizadas por su ID.
		*/
		TEntityMap _entityMap;

		/**
		Nombre del mapa.
		*/
		std::string _name;

		/**
		Escena gráfica donde se encontrarán las representaciones gráficas de
		las entidades.
		*/
		Graphics::CScene* _scene;

		/**
		Grid de tiles donde se almacena el mapa lógico del escenario.
		*/
		CGridMap* _gridMap;

		/**
		Lista con los diferentes terrenos que contiene el mapa.
		*/
		std::list<CTerrainTile*>* _terrainList;

	}; // class CMap

} // namespace Logic

#endif // __Logic_Map_H
