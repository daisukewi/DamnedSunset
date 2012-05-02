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
#include "Map/MapParser.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
	class CGridTile;
}

// Declaraci�n de la clase
namespace Logic
{
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
		Inicializa el mapa con el valor de anchura y altura pasados como par�metros e inicializa cada una de las casillas.

		@param width anchura del mapa.
		@param height altura del mapa.
		@param gridSize tama�o de cada celda del mapa.
		*/
		void initMap(int width, int height, int gridSize);

		/**
		Devuelve el tamapo del mapa l�gico.
		*/
		int getMapSize();

		/**
		Devuelve las dimensiones del mapa l�gico.
		*/
		int getMapWidth();
		int getMapHeight();

		/**
		Devuelve el tama�o de las casillas del mapa.
		*/
		unsigned int getGridSize();

		/**
		Devuelve la posici�n modulada en el grid del mapa, de las
		coordenadas pasadas por argumento.
		*/
		const Vector2 getRelativeMapPos(const Vector2 pos);

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

		/**
		A�ade una entidad de tipo Waypoint encima de cada casilla
		del mapa l�gico.
		*/
		void ShowDebugTiles( CMap * _map );

		/**
		Fiils the tiles of the map with the info stored in tileMatrix.

		@param tileMatrix a talbe with the information to fill in each tile of the map.
		*/
		void FillTileData( Map::CMapParser::TTileMatrix tileMatrix );


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

		/// Declaraci�n de atributos �tiles a lo largo de la ejecuci�n del juego.

		/**
		Almacena las dimensiones actuales del mapa.
		*/
		int _mapWidth;
		int _mapHeight;

		/**
		Atributos r�pidos que almacena la mitad de la
		dimensi�n del mapa actual.
		*/
		int _halfMapWidth;
		int _halfMapHeight;

		/**
		Tama�o de las celdas en potencia de 2.
		*/
		int _gridSize;

		/**
		Almacena la mitad del tama�o de una celda.
		*/
		int _halfGrid;

		/**
		N�mero de columnas y filas que tiene el mapa actual.
		*/
		int _nMapCols;
		int _nMapRows;

	};

}

#endif // __Logic_GridMap_H