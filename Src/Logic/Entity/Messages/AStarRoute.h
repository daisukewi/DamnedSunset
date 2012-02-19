/**
@file AStarRoute.h

Contiene la declaración del mensaje para calcular una ruta con A*
entre dos puntos del mapa y luego seguirlos con Steering Behaviours.

@see Logic::IMessage

@author Daniel Flamenco
@date Febrero, 2012
*/

#ifndef __Logic_MAStarRoute_H
#define __Logic_MAStarRoute_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic
{

	/**
	Tipo de acción a realizar cuando se envía un mensaje de construir.
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
	Clase mensaje que se encargará de avisar al agente que tiene que calcular
	una ruta con A* entre dos puntos, y luego seguir sus puntos para moverse.

	@author Daniel Flamenco
	@date Febrero, 2012
	*/
	class MAStarRoute : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAStarRoute();

		/**
		Método que establece la acción que se quiere realizar con este mensaje.

		@param action Tipo de la acción a realizar.
		*/
		void setAction(RouteAction action);

		/**
		Método que devuelve la acción que se quiere realizar con este mensaje.

		@return Tipo de la acción a realizar.
		*/
		RouteAction getAction();

		/*
		Método que establece el punto de destino al que se quiere ir.

		@param dest Vector3 que contiene las coordenadas del destino.
		*/
		void setRouteDestination(Vector3 dest);

		/**
		Método que devuelve el punto de destino al que se quiere ir.

		@return Vector3 que contiene las coordenadas del destino.
		*/
		Vector3 getRouteDestination();

		/*
		Método que devuelve true si la ruta ha fallado.
		En caso contrario, es que ha llegado correctamente a su destino.
		*/
		bool hasRouteFailed();

		/*
		Establece si la ruta ha fallado o ha llegado correctamente a su destino.

		@param failed True si la ruta ha fallado.
		False si ha llegado correctamente a su destino.
		*/
		void setRouteFailed(bool failed);

	protected:

		/**
		Atributo que indica la acción que se va a realizar con este mensaje.
		*/
		RouteAction _action;

		/**
		Atributo que indica la posición con el destino de la ruta.
		*/
		Vector3 _destPoint;

		/*
		Atributo que indica si la ruta ha fallado o no.
		*/
		bool _failed;

	}; // class MAStarRoute

} // namespace Logic

#endif // __Logic_MAStarRoute_H