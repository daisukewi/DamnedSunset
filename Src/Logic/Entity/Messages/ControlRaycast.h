/**
@file EmplaceBuilding.h

Contiene la declaraci�n del mensaje para controlar el lanzamiento de raycast.

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
	Tipo de acci�n a realizar cuando se env�a un mensaje del control de raycast.
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
	Clase mensaje que se encargar� de controlar el lanzamiento de raycasts desde
	la c�mara hacia el mapa.

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
		M�todo que establece la acci�n que se quiere realizar con este mensaje.

		@param action Tipo de la acci�n a realizar.
		*/
		void setAction(TRaycastAction action);

		/**
		M�todo que devuelve la acci�n que se quiere realizar con este mensaje.

		@return Tipo de la acci�n a realizar.
		*/
		TRaycastAction getAction();

		/**
		M�todo que establece el punto de colisi�n del rayo

		@param point Punto donde ha colisionado el rayo.
		*/
		void setCollisionPoint(Vector3 point);

		/**
		M�todo que devuelve el punto de colisi�n del rayo

		@return Punto de colisi�n del rayo.
		*/
		Vector3 getCollisionPoint();

		/**
		M�todo que establece la entidad con la que ha colisionado el rayo.

		@param entity Puntero a la entidad con la que ha colisionado el rayo.
		*/
		void setCollisionEntity(CEntity *entity);

		/**
		M�todo que devuelve la entidad con la que ha colisionado el rayo.

		@return Puntero a la entidad con la que ha colisionado el rayo.
		*/
		CEntity* getCollisionEntity();

	protected:

		/**
		Atributo que indica la acci�n que se va a realizar con este mensaje.
		*/
		TRaycastAction _action;

		/**
		Atributo que indica la posici�n de colisi�n del rayo con el escenario.
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