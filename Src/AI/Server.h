/**
@file Server.h

Servidor de IA.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#pragma once

#ifndef __AI_Server_H
#define __AI_Server_H

#include "GridmapGraph.h"
#include "AStarFunctionsDamnedSunset.h"
#include "micropather.h"

namespace AI {


/**
Servidor de IA. De momento s�lo se encarga de mantener el
grafo con los waypoints y de centralizar las llamadas a A*.

La idea es que en un futuro tambi�n se ocupe de gestionar la 
percepci�n.
*/
class CServer
{
	public:

		/**
		Devuelve la �nica instancia de la clase.

		@return Puntero al servidor de IA.
		*/
		static CServer *getSingletonPtr() { return _instance; }
		
		/**
		Inicializa el servidor de IA. Esta operaci�n s�lo es necesario realizarla
		una vez durante la inicializaci�n de la aplicaci�n. 

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera el servidor de IA. Debe llamarse al finalizar la aplicaci�n.
		*/
		static void Release();

		/**
		Funci�n invocada en cada vuelta para actualizaci�n.

		@param secs Segundos desde que se reenderiz� el �ltimo frame.
		@return Valor booleano indicando si todo fue bien.
		*/
		bool tick(float secs);

		/**
		Devuelve el grafo de navegaci�n.
		*/
		CGridmapGraph* getNavigationMap() { return _navMap; };
		/**
		Calcula una ruta usando A*.
		*/
		std::vector<Vector3> *getAStarRoute(Vector3 from, Vector3 to);
		/**
		Dado un �ngulo en radianes lo lleva al intervalo [-PI, PI]
		*/
		static double correctAngle(double angle);

	private:
		/**
		Constructor de la clase.
		*/
		CServer();

		/**
		Destructor de la clase.
		*/
		virtual ~CServer();
		/**
		Instancia �nica de la clase.
		*/
		static CServer *_instance;

		/*
		Referencia al mapa de navegaci�n utilizado para calcular
		la ruta con A*.
		*/
		CGridmapGraph* _navMap;
		/**
		Clase que se encarga de calcular la mejor ruta con A*
		*/
		// CAStar* _aStar;
		micropather::MicroPather* _aStar;
		/** 
		Funciones de distancia para calcular A*
		*/
		CAStarFunctionsDamnedSunset* _f;

}; // class CServer

} // namespace AI
#endif