
/**
@file TerrainTile.h

Contiene la declaración de la clase CTerrainTile que contiene
la informacion de una celda del terreno.

@see Logic::TerrainTile

@author Daniel Flamenco
@date Abril, 2012
*/
#ifndef __Logic_TerrainTile_H
#define __Logic_TerrainTile_H

#include "Logic/Entity/Entity.h"

namespace Map
{
	class CEntity;
}

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
	class CTerrainTile
	{
	public:
		/**
		Constructor.
		*/
		CTerrainTile (std::string name) : _name(name) {}

		/**
		Destructor.
		*/
		~CTerrainTile() {}

		/**
		Devuelve el nombre del tipo de terreno.
		*/
		std::string getName();

		/**
		Recoge la información del terreno del mapa y lo guarda en el objeto.
		Tiene que tener los atributos:
		<li>Cost</li>
		<li>Difuse_texture</li>
		<li>Normal_texture</li>
		*/
		void FillData(Map::CEntity* terrain_info);

	private:

		/**
		Nombre del tipo de celda del terreno.
		*/
		std::string _name;

		int _aStarCost;

		std::string _difuseMap, _normalMap;



	};

}

#endif // __Logic_TerrainTile_H