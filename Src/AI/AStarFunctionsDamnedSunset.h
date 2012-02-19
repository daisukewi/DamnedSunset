/**
@file AStarFunctionsDamnedSunset.h

En este fichero se definen las funciones
necesarias para calcular rutas usando A*.


@author Daniel Flamenco
@date Febrero, 2012
*/

#pragma once

#ifndef __AI_AStarFunctionsDamnedSunset_H
#define __AI_AStarFunctionsDamnedSunset_H

#include "micropather.h"

namespace AI 
{
	/**
	Clase que hereda de micropather::Graph y que contiene las funciones
	de A* espec�ficas de DamnedSunset.
	*/
	class CAStarFunctionsDamnedSunset : public micropather::Graph
	{
	public:
		/** 
		Constructor
		*/
		CAStarFunctionsDamnedSunset(void);
		/** 
		Destructor
		*/
		~CAStarFunctionsDamnedSunset(void);
		/**
		Devuelve el coste seg�n la heur�stica para llegar desde el estado stateStart hasta stateEnd.
		Para que el camino devuelto por A* sea �ptimo la heur�stica sea aceptable y no sobreestimar 
		la distancia.
		Para la b�squeda de caminos de Damned Sunset utilizaremos como heur�stica la distancia eucl�dea
		entre los puntos.
		*/
		virtual float LeastCostEstimate( void* stateStart, void* stateEnd );

		/** 
		Devuelve la lista de vecinos de un nodo junto con el coste de llegar desde el nodo actual
		hasta cada uno de ellos.
		En Galeon usaremos el grafo de waypoints para obtenerla.
		*/	
		virtual void AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent );

		/**
			This function is only used in DEBUG mode - it dumps output to stdout. Since void* 
			aren't really human readable, normally you print out some concise info (like "(1,2)") 
			without an ending newline.
		*/
		virtual void  PrintStateInfo( void* state );

	};

} // namespace AI 

#endif //__AI_AStarFunctionsDamnedSunset_H