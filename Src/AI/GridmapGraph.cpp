/**
@file GridmapGraph.cpp

Clase para comunicarse con el mapa lógico y funcione con A*.

@see GridmapGraph

@author Daniel Flamenco
@date Febrero 2012

*/
#include "GridmapGraph.h"
#include "DisjointSets.h"

#include "Logic\Server.h"
#include "Logic\Entity\Entity.h"
#include "Logic\Maps\Map.h"
#include "Logic\Maps\GridMap.h"

namespace AI {

	/**
	Constructor
	*/
	CGridmapGraph::CGridmapGraph(void)
	{
	}
	
	//--------------------------------------------------------

	/**
	Destructor
	*/
	CGridmapGraph::~CGridmapGraph(void)
	{
	}

	//--------------------------------------------------------

	/**
	Devuelve el coste asociado a la arista entre dos nodos (la distancia).
	*/
	float CGridmapGraph::getCost(int node1, int node2)
	{
		if (!_gm->getTileFromIndex(node2)->IsPopulated()
			|| (_gm->getTileFromIndex(node2)->GetBuilding() == _gm->getTileFromIndex(node1)->GetBuilding()))
				return 1.0f;

		return 50.0f;
		
	} // getCost

	//--------------------------------------------------------

	/**
	Devuelve la lista de vecinos de un nodo.
	*/
	std::list<unsigned int> CGridmapGraph::getNeighbours(int idNode)
	{
		return _gm->getAdjacencyGrids(idNode);
	}

	//--------------------------------------------------------

	/**
	Devuelve el número de nodos que contiene el mapa.
	*/
	int CGridmapGraph::getNodeCount()
	{
		return _gm->getNumGrids();
	}

	//--------------------------------------------------------

	/**
	Devuelve la posición de un nodo, dado su identificador.
	*/
	Vector3 CGridmapGraph::getNodePosition(int idNode)
	{
		return _gm->getTilePositionFromIndex(idNode);
	}
	
	//--------------------------------------------------------

	int CGridmapGraph::getClosestNode(Vector3 position)
	{
		return _gm->getIndexTileFromPosition(position);
	}

	//--------------------------------------------------------

	void CGridmapGraph::PrintMapWithRoute( std::vector<void*>* path )
	{
		_gm->PrintMapWithRoute(path);
	}

}