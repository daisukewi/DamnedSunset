/**
@file WaypointGraph.cpp

Clase para mantener grafos de puntos de ruta (waypoints).

@see WaypointGraph

@author Gonzalo Fl�rez
@date Diciembre 2010

*/
#include "WaypointGraph.h"
#include "DisjointSets.h"
#include "Physics\Server.h"

#include "Logic\Entity\Entity.h"

namespace AI {

	/**
	Constructor
	*/
	CWaypointGraph::CWaypointGraph(void) : _generated(false) , _connected(false), _clean(false)
	{
	}
	/////////////////////////////////////////
	/**
	Destructor
	*/
	CWaypointGraph::~CWaypointGraph(void)
	{
	}
	/////////////////////////////////////////
	/**
	A�ade un nuevo waypoint al grafo.
	*/
	void CWaypointGraph::addWaypoint(Vector3 waypoint) 
	{
		_g.addNode(new CNode(waypoint));
		_clean = false;
	}
	/////////////////////////////////////////
	/**
	Calcula las aristas entre los waypoints. Para ello, entre cada par 
	de waypoints hace una comprobaci�n de visibilidad. Si un waypoint es
	visible desde otro, se a�ade una arista entre ellos.
	*/
	void CWaypointGraph::computeNavigationGraph()
	{
		// Generar las aristas para el grafo de navegaci�n
		// Para cada par de nodos del grafo tenemos que comprobar si se puede llegar en l�nea recta
		// El grafo subyacente en el que se basa esta clase se encuentra en la variable _g, y es un 
		// grafo no dirigido implementado en la clase CUndirectedGraph. En el fichero de cabecera de 
		// esta clase se pueden encontrar los m�todos para acceder a los nodos, a�adir aristas, etc.
		// Los m�todos que vais a necesitar ser�n getNode(i) para obtener las posiciones de cada nodo
		// y addEdge(i, j, dist) para a�adir las aristas.
		// Como el grafo es no dirigido, s�lo necesitamos hacer comparaciones en 1 sentido (si B es 
		// visible desde A sabemos que A es visible desde B). Al a�adir la arista de A a B se a�ade 
		// autom�ticamente la arista de B a A.
		// Para comprobar la visibilidad usamos el m�todo raycastClosest que nos proporciona el 
		// servidor de f�sica. Este m�todo recibe un rayo y la distancia m�xima y devuelve la entidad 
		// con la que ha colisionado o NULL. S�lo nos interesa a�adir una arista si el rayo no ha
		// colisionado con el mundo. Podemos saber si es el mundo usando la propiedad getType de
		// la entidad que devuelve raycastClosest, compar�ndola con la cadena "World".
		int numNodes = _g.getNodeCount();
		DisjointSets sets(numNodes);
		for (int i = 0; i < numNodes - 1; i++) {
			const CNode* node1 = _g.getNode(i);
			Vector3 pos1 = node1->position;
			for (int j = i + 1; j < numNodes; j++) {
				const CNode* node2 = _g.getNode(j);
				Vector3 pos2 = node2->position;
				// Sacamos la direcci�n (en pos2) y la distancia
				pos2 -= pos1;
				float dist = pos2.length();
				// El rayo necesita la direcci�n normalizada
				pos2 /= dist;
				// Si el rayo no choca con ninguna entidad ==> devuelve NULL ==> hay una recta entre los waypoints
				Logic::CEntity *entCol = 
					Physics::CServer::getSingletonPtr()->raycastClosest(Ray(pos1, pos2), dist);
				if (entCol == NULL || entCol->getType() != "World") {
					_g.addEdge(i, j, dist);
					int idI = sets.FindSet(i);
					int idJ = sets.FindSet(j);
					sets.Union(idI, idJ);
				}
			}
		}
		_connected = sets.NumSets() == 1;
		_clean = true;
		_generated = true;

	}
	/////////////////////////////////////////
	/**
	Obtiene el waypoint m�s cercano a una posici�n dada.
	<p>
	Hace una b�squeda lineal en la lista de nodos y devuelve el m�s cercano.
	*/
	int CWaypointGraph::getClosestWaypoint(Vector3 position)
	{
		// Recorremos la lista de waypoints y devolvemos el m�s cercano a la posici�n dada.
		// En lugar de calcular la distancia podemos calcular la distancia al cuadrado 
		// (squaredDistance). De esta manera nos ahorramos una ra�z cuadrada.
		// En algunos casos, el resultado de este m�todo no es v�lido para calcular una ruta, pues
		// no existe un camino en l�nea recta desde la posici�n de entrada hasta el waypoint.
		// Para evitar este problema, podemos comprobar que el nodo es visible desde la posici�n 
		// indicada. Esto puede aumentar el coste de esta operaci�n.

		int numNodes = _g.getNodeCount();
		if (numNodes == 0) return -1;

		int closestNode = 0;
		Vector3 node = _g.getNode(0)->position;
		double minDist = node.squaredDistance(position);
		for (int i = 1; i < numNodes; i++) {
			Vector3 node = _g.getNode(i)->position;
			double dist = node.squaredDistance(position);
			if (dist <= minDist) {
				minDist = dist;
				closestNode = i;
			}
		}
		return closestNode;
	}

	/** 
 	Cambia la altura de todos los waypoints del grafo

	@param height Nueva altura
	*/	
	void CWaypointGraph::setWaypointHeight(float height) 
	{
		for (int i = 0; i < _g.getNodeCount(); i++) {
			_g.getNode(i)->position.y = height;
		}
	}

}