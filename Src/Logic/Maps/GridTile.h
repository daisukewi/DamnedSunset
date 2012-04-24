
/**
@file GridTile.h

Contiene la declaración de la clase CGridTile, Las celdas del mapa lógico.

@see Logic::GridTile

@author Daniel Flamenco
@date Febrero, 2012
*/
#ifndef __Logic_GridTile_H
#define __Logic_GridTile_H

#include "Logic/Entity/Entity.h"

// Declaración de la clase
namespace Logic
{

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
		unsigned int GetRow();

		/**
		Devuelve la columna en la que se encuentra la casilla dentro de la tabla.
		*/
		unsigned int GetCol();

		/**
		Pone el tipo de terreno de la casilla.
		*/
		void SetTerrain(int terrainType);

		/**
		Obtiene el tipo de terreno de la casilla.
		*/
		int GetTerrain() { return _terrain; }

		/**
		Establece el edificio que se encuentra en la casilla.
		*/
		void SetBuilding(CEntity* building);

		/**
		Elimina el edificio que tiene la casilla.
		*/
		void DeleteBuilding();

		/**
		Obtiene el edificio que se encuentra en la casilla.

		Devuelve NULL si no hay edificio.
		*/
		CEntity* GetBuilding();

		/**
		Indica si la casilla está ocupada por un edificio o tiene
		alguna unidad en ella.

		@return true Si hay un edificio construido, o cuando hay una unidad
		en la casilla.
		*/
		bool IsPopulated();

		/**
		Añade una nueva entidad a la casilla.
		NOT IMPLEMENTED
		*/
		void AddUnit(CEntity* entity);

		/**
		Elimina una entidad de la casilla.
		NOT IMPLEMENTED
		*/
		void DeleteUnit(CEntity* entity);

		void FillData();

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

}

#endif // __Logic_GridTile_H