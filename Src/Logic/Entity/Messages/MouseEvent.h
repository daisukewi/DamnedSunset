/**
@file EmplaceBuilding.h

Contiene la declaración del mensaje para avisar de los eventos del raton.

@see Logic::IMessage

@author Daniel Flamenco
@date Enero, 2012
*/

#ifndef __Logic_MouseEvent_H
#define __Logic_MouseEvent_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic
{

	/**
	Tipo de acción a realizar cuando se envía un mensaje del control de raycast.
	*/
	namespace MouseEventMessage
	{
		enum TMouseAction
		{
			LEFT_CLICK,
			MIDDLE_CLICK,
			RIGHT_CLICK,
			LEFT_PRESSED
		};
	}

	typedef MouseEventMessage::TMouseAction TMouseAction;

	/**
	Clase mensaje que se encargará de avisar de los eventos del ratón.

	@author Daniel Flamenco
	@date Enero, 2012
	*/
	class MMouseEvent : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMouseEvent();

		/**
		Método que establece la acción que se quiere realizar con este mensaje.

		@param action Tipo de la acción a realizar.
		*/
		void setAction(TMouseAction action);

		/**
		Método que devuelve la acción que se quiere realizar con este mensaje.

		@return Tipo de la acción a realizar.
		*/
		TMouseAction getAction();

		/**
		Método que establece la posicón relativa del ratón

		@param relPosition
		*/
		void setRelPosition(Vector2 relPosition);

		/**
		Método que devuelve la posición relativa del ratón
		*/
		Ogre::Vector2 getRelPosition();
		

	protected:

		/**
		Atributo que indica la acción que se va a realizar con este mensaje.
		*/
		TMouseAction _action;

		/**
		Atributo que indica la posición relativa en pantalla del ratón
		*/
		Vector2 _relPosition;

	}; // class MMouseEvent

} // namespace Logic

#endif // __Logic_MouseEvent_H