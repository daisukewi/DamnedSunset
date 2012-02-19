/**
@file EmplaceBuilding.h

Contiene la declaración del mensaje para controlar el lanzamiento de raycast.

@see Logic::IMessage

@author Daniel Flamenco
@date Enero, 2012
*/

#ifndef __Logic_ControlRaycast_H
#define __Logic_ControlRaycast_H

#include "Logic/Entity/Message.h"

#include "Logic/Entity/Entity.h"

#include "BaseSubsystems/Math.h"

namespace Logic
{

	/**
	Tipo de acción a realizar cuando se envía un mensaje del control de raycast.
	*/
	namespace RaycastMessage
	{
		enum TRaycastAction
		{
			START_RAYCAST,
			STOP_RAYCAST,
			HIT_RAYCAST

		};
	}

	typedef RaycastMessage::TRaycastAction TRaycastAction;

	/**
	Clase mensaje que se encargará de controlar el lanzamiento de raycasts desde
	la cámara hacia el mapa.

	@author Daniel Flamenco
	@date Enero, 2012
	*/
	class MControlRaycast : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MControlRaycast();

		/**
		Método que establece la acción que se quiere realizar con este mensaje.

		@param action Tipo de la acción a realizar.
		*/
		void setAction(TRaycastAction action);

		/**
		Método que devuelve la acción que se quiere realizar con este mensaje.

		@return Tipo de la acción a realizar.
		*/
		TRaycastAction getAction();

		/**
		Método que establece el punto de colisión del rayo

		@param point Punto donde ha colisionado el rayo.
		*/
		void setCollisionPoint(Vector3 point);

		/**
		Método que devuelve el punto de colisión del rayo

		@return Punto de colisión del rayo.
		*/
		Vector3 getCollisionPoint();

		/**
		Método que establece la entidad con la que ha colisionado el rayo.

		@param entity Puntero a la entidad con la que ha colisionado el rayo.
		*/
		void setCollisionEntity(CEntity *entity);

		/**
		Método que devuelve la entidad con la que ha colisionado el rayo.

		@return Puntero a la entidad con la que ha colisionado el rayo.
		*/
		CEntity* getCollisionEntity();

	protected:

		/**
		Atributo que indica la acción que se va a realizar con este mensaje.
		*/
		TRaycastAction _action;

		/**
		Atributo que indica la posición de colisión del rayo con el escenario.
		*/
		Vector3 _collisionPoint;

		/**
		Atributo que contiene un puntero a la entidad con la que ha colisionado
		el rayo.
		*/
		CEntity *_collisionEntity;

	}; // class MControlRaycast

} // namespace Logic

#endif // __Logic_ControlRaycast_H