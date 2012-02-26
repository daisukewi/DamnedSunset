/**
@file GridMap.h

Contiene la declaraci�n de la clase CGridMap, Un mapa de celdas l�gico.

@see Logic::GridMap

@author Daniel Flamenco
@date Febrero, 2012
*/
#ifndef __Logic_GridMap_H
#define __Logic_GridMap_H

#include "Logic/Entity/Entity.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
}

// Declaraci�n de la clase
namespace Logic
{
	
	/**
	Clase que contiene el tipo de datos de un tile del mapa.
	Tiene una serie de atributos que se utilizan para almacenar
	las entidades y el terreno que tiene cada casilla del mapa.

	@author Daniel Flamenco Gonz�lez
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
		Indica si la casilla est� ocupada por un edificio o tiene
		alguna unidad en ella.

		@return true Si hay un edificio construido, o cuando hay una unidad
		en la casilla.
		*/
		bool IsPopulated() { return _building != NULL; }

		/**
		A�ade una nueva entidad a la casilla.
		NOT IMPLEMENTED
		*/
		void AddUnit(CEntity* entity) { /*_entityList.insert(std::pair<TEntityID, CEntity*>(entity->getEntityID(), entity));*/ }

		/**
		Elimina una entidad de la casilla.
		NOT IMPLEMENTED
		*/
		void DeleteUnit(CEntity* entity) { /*_entityList.erase(entity->getEntityID());*/ }

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
		//std::map<TEntityID, CEntity*> _entityList;

	};

	/**
	Tipo de las celdas de un mapa.
	*/
	typedef CGridTile* TGridTile;



	/**
	Clase que representa un mapa de celdas l�gico.
	<p>
	Esta clase se encarga de almacenar la representaci�n l�gica del
	mapa del juego. Gestiona las casillas que est�n ocupadas y las
	libera cuando se le pide.

	@ingroup logicGroup
	@ingroup mapGroup

	@author Daniel Flamenco
	@date Febrero, 2012
	*/
	class CGridMap
	{
	public:

		/**
		Constructor.
		*/
		CGridMap();

		/**
		Destructor.
		*/
		~CGridMap();

		/**
		Devuelve la posici�n modulada en el grid del mapa, de las
		coordenadas pasadas por argumento.
		*/
		const Vector2 getAbsoluteGridPos(const Vector2 pos);

		/**
		De vuelve un Vector2 con las coordenadas del centro de
		la casilla que se encuentra	en la fila y la columna dadas.
		*/
		const Vector2 getRelativeMapPos( unsigned int row, unsigned int col );

		/**
		Devuelve la casilla que le corresponde a una posici�n 2D del mapa.
		*/
		const TGridTile getTileFromPosition(const float x, const float y);

		/**
		Devuelve la casilla que le corresponde a las coordenadas de la tabla.
		*/
		const TGridTile getTileFromCoord(const int row, const int col);

		/**
		Devuelve la casilla que corresponde a un �ndice de la tabla.
		*/
		const TGridTile getTileFromIndex(const unsigned int index);

		/**
		Devuelve la posici�n de una casilla que corresponde a un 
		�ndice de la tabla.
		*/
		Vector3 getTilePositionFromIndex(const unsigned int index);

		/*
		Devuelve el �ndice de una casilla que contiene la posici�n dada.
		*/
		int getIndexTileFromPosition( Vector3 position );

		/*
		Devuelve una lista con las casillas adyacentes a la casilla dada.
		*/
		std::list<unsigned int> getAdjacencyGrids(const int index);

		/*
		Devuelve el n�mero de casillas que tiene el mapa l�gico.
		*/
		int getNumGrids();

		/*
		Imprime una representaci�n del mapa en la pantalla.
		*/
		void PrintMap();

		/**
		Imprime una representaci�n del mapa en la pantalla.
		En esta representaci�n se imprime tambi�n la ruta calculada
		con el algoritmo A*.
		*/
		void PrintMapWithRoute( std::vector<void*>* path );

	private:

		/*
		Devuelve el �ndice de una casilla que se encuentra en las coordenadas dadas.
		*/
		int getIndexTileFromCoord( const int row, const int col );
		
		typedef TGridTile** TGridMap;

		/**
		Grid de tiles donde se almacena el mapa l�gico del escenario.
		*/
		TGridMap _gridMap;

	};

}

#endif // __Logic_GridMap_H