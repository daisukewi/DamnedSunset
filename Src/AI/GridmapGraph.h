/**
@file GridmapGraph.h

Clase para comunicarse con el mapa lógico y funcione con A*.

@see GridmapGraph

@author Daniel Flamenco
@date Febrero 2012

*/

#pragma once

#ifndef __AI_GridmapGraph_H
#define __AI_GridmapGraph_H

#include "BaseSubsystems/Math.h"

#include "Logic/Maps/GridMap.h"

namespace AI {

/**
Esta clase se encarga de hacer de interfaz entre el mapa lógico
y el proyecto de IA para calcular una ruta entre dos puntos
utilizando el algoritmo de A*.
<p>
Tiene un wrapper del GridMap y traduce las llamadas a métodos
de CGridMap para calcular el A* sobre un mapa de celdas en vez
de un grafo de waypoints.
*/
class CGridmapGraph
{
public:

	/**
	Constructor
	*/
	CGridmapGraph(void);

	/**
	Destructor
	*/
	~CGridmapGraph(void);

	/*
	Establece el mapa de celdas que usará la IA para calcular
	la ruta con A*.
	*/
	void setGridMap(Logic::CGridMap* map) { _gm = map; };
	
	/**
	Devuelve el coste asociado a la arista entre dos nodos (la distancia).
	*/
	float getCost(int node1, int node2);

	/**
	Devuelve la lista de vecinos de un nodo.
	*/
	std::list<unsigned int> getNeighbours(int idNode);

	/**
	Obtiene el nodo más cercano a una posición dada.
	<p>
	Mediante una operación matemática se obtiene en O(1).
	*/
	int getClosestNode(Vector3 position);

	/**
	Devuelve el número de nodos que contiene el mapa.
	*/
	int getNodeCount();

	/**
	Devuelve la posición de un nodo, dado su identificador.
	*/
	Vector3 getNodePosition(int numWaypoint);


private:
	
	/*
	Almacena una referencia al mapa lógico que contiene
	la información del escenario y con los caminos por
	donde se puede caminar.
	*/
	Logic::CGridMap* _gm;

}; // class CGridmapGraph

} // namespace AI

#endif // __AI_GridmapGraph_H
