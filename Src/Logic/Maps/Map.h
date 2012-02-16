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

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Logic 
{
	class CEntity;
}

namespace Graphics 
{
	class CScene;
}

// Declaración de la clase
namespace Logic
{

	const int GRID_SIZE = 10;
	const int MAP_HGRIDS = 10;
	const int MAP_VGRIDS = 10;
	const float MAP_WIDTH = 100.0f;
	const float MAP_HEIGHT = 100.0f;

	/**
	Clase que contiene el tipo de datos de un tile del mapa.
	Tiene una serie de atributos que se utilizan para almacenar
	las entidades y el terreno que tiene cada casilla del mapa.

	@author Daniel Flamenco González
	@date Febrero, 2012
	*/
	class CGridTile
	{
	public:
		/**
		Constructor.
		*/
		CGridTile (unsigned int row, unsigned int col) : _row(row), _col(col), _terrain(0), _building(NULL) {}

		/**
		Destructor.
		*/
		~CGridTile() {}

		/**
		Devuelve la fila en la que se encuentra la casilla dentro de la tabla.
		*/
		unsigned int GetRow() { return _row; }

		/**
		Devuelve la columna en la que se encuentra la casilla dentro de la tabla.
		*/
		unsigned int GetCol() { return _col; }

		/**
		Pone el tipo de terreno de la casilla.
		*/
		void SetTerrain(int terrainType) { _terrain = terrainType; }

		/**
		Obtiene el tipo de terreno de la casilla.
		*/
		int GetTerrain() { return _terrain; }

		/**
		Establece el edificio que se encuentra en la casilla.
		*/
		void SetBuilding(CEntity* building) { _building = building; }

		/**
		Elimina el edificio que tiene la casilla.
		*/
		void DeleteBuilding() { _building = NULL; }

		/**
		Obtiene el edificio que se encuentra en la casilla.

		Devuelve NULL si no hay edificio.
		*/
		CEntity* GetBuilding() { return _building; }

		/**
		Indica si la casilla está ocupada por un edificio o tiene
		alguna unidad en ella.

		@return true Si hay un edificio construido, o cuando hay una unidad
		en la casilla.
		*/
		bool IsPopulated() { return _building != NULL || !_entityList.empty(); }

		/**
		Añade una nueva entidad a la casilla.
		*/
		void AddUnit(CEntity* entity) { _entityList.insert(std::pair<TEntityID, CEntity*>(entity->getEntityID(), entity)); }

		/**
		Elimina una entidad de la casilla.
		*/
		void DeleteUnit(CEntity* entity) { _entityList.erase(entity->getEntityID()); }

	private:

		/**
		Atributos que indican la columna y la fila en las que se encuentra
		la casilla dentro de la tabla.
		*/
		int _row, _col;

		/**
		Atributo que almacena el tipo de terreno que hay en la casilla.
		*/
		int _terrain;

		/**
		Atributo para almacenar la entidad de un edificio.
		*/
		CEntity* _building;

		/**
		Lista de agentes que se encuentran en la casilla.
		*/
		std::map<TEntityID, CEntity*> _entityList;

	};

	typedef CGridTile* TGridTile;

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
		Método factoría que carga un mapa de fichero. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param filename Nombre del archivo a cargar.
		@return Mapa generado.
		*/
		static CMap *createMapFromFile(const std::string &filename);

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

		/**
		Devuelve la escena gráfica correspondiente a este mapa.

		@return Escena con las entidades gráficas.
		*/
		Graphics::CScene *getScene() { return _scene; }

		/**
		Devuelve la posición modulada en el grid del mapa, de las
		coordenadas pasadas por argumento.
		*/
		Vector2 getAbsoluteGridPos(const Vector2 pos);

		/**
		Devuelve la casilla que le corresponde a una posición 2D del mapa.
		*/
		TGridTile getTileFromPosition(const float x, const float y);

		/**
		Devuelve la casilla que le corresponde a las coordenadas de la tabla.
		*/
		TGridTile CMap::getTileFromCoord(const int row, const int col);

		static void setAtributosArquetipos(Map::CEntity* entidad, Map::CMapParser::TEntityList & entityList);
		
	private:
		

		/**
		Tipo tabla de entidades de mapa.
		*/
		typedef std::map<TEntityID,CEntity*> TEntityMap;

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
		TGridTile** _gridMap;

	}; // class CMap

} // namespace Logic

#endif // __Logic_Map_H
