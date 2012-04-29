/**
@file LUA_AStarRoute.h

LUA

Contiene la declaraci�n del mensaje para calcular una ruta con A*
entre dos puntos del mapa y luego seguirlos con Steering Behaviours.


@author Alberto Ortega
@date Abril, 2012
*/

#ifndef __Logic_LUA_MAStarRoute_H
#define __Logic_LUA_MAStarRoute_H

#include "LUA_Message.h"


namespace ScriptManager
{

	/**
	Tipo de acci�n a realizar cuando se env�a un mensaje de construir.
	*/
	namespace RouteToMessage
	{
		enum RouteAction
		{
			START_ROUTE,
			STOP_ROUTE,
			FINISHED_MOVE,
			FINISHED_ROUTE
		};
	}

	typedef RouteToMessage::RouteAction RouteAction;

	/**
	Clase mensaje que se encargar� de avisar al agente que tiene que calcular
	una ruta con A* entre dos puntos, y luego seguir sus puntos para moverse.

	@author Alberto Ortega
	@date Abril, 2012
	*/
	class LUA_MAStarRoute: public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MAStarRoute();

		/**
		M�todo que establece la acci�n que se quiere realizar con este mensaje.

		@param action Tipo de la acci�n a realizar.
		*/
		void setAction(RouteAction action);

		/**
		M�todo que devuelve la acci�n que se quiere realizar con este mensaje.

		@return Tipo de la acci�n a realizar.
		*/
		RouteAction getAction();
		

		/*
		M�todo que establece la coordenada X del punto de destino al que se quiere ir.

		@param destPointX float que contiene la coordenada X del destino.
		*/
		void setDestPointX(float destPointX);


		/*
		M�todo que establece la coordenada Y del punto de destino al que se quiere ir.

		@param destPointY float que contiene la coordenada Y del destino.
		*/
		void setDestPointY(float destPointY);


		/*
		M�todo que establece la coordenada Z del punto de destino al que se quiere ir.

		@param destPointZ float que contiene la coordenada Z del destino.
		*/
		void setDestPointZ(float destPointZ);

		/*
		M�todo que devuelve la coordenada X del punto de destino al que se quiere ir

		@return coordenada X del punto de destino
		*/
		float getDestPointX();

		/*
		M�todo que devuelve la coordenada Y del punto de destino al que se quiere ir

		@return coordenada Y del punto de destino
		*/
		float getDestPointY();

		/*
		M�todo que devuelve la coordenada Z del punto de destino al que se quiere ir

		@return coordenada Z del punto de destino
		*/
		float getDestPointZ();

		/*
		M�todo que devuelve true si la ruta ha fallado.
		En caso contrario, es que ha llegado correctamente a su destino.
		*/
		bool hasRouteFailed();

		/*
		Establece si la ruta ha fallado o ha llegado correctamente a su destino.

		@param failed True si la ruta ha fallado.
		False si ha llegado correctamente a su destino.
		*/
		void setRouteFailed(bool failed);

		/*
		Implementaci�n del m�todo send heredado de la clase LUA_IMessage
		*/
		virtual void send();

	protected:

		/**
		Atributo que indica la acci�n que se va a realizar con este mensaje.
		*/
		RouteAction _action;

		/**
		Atributos que indican la posici�n con el destino de la ruta.
		*/
		float _destPointX;
		float _destPointY;
		float _destPointZ;
		/*
		Atributo que indica si la ruta ha fallado o no.
		*/
		bool _failed;

	}; // class LUA_MAStarRoute

} // namespace Logic

#endif // __Logic_MAStarRoute_H