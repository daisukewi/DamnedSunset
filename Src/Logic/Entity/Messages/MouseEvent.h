/**
@file EmplaceBuilding.h

Contiene la declaraci�n del mensaje para avisar de los eventos del raton.

@see Logic::IMessage

@author Daniel Flamenco
@date Enero, 2012
*/

#ifndef __Logic_MouseEvent_H
#define __Logic_MouseEvent_H

#include "Logic/Entity/Message.h"

namespace Logic
{

	/**
	Tipo de acci�n a realizar cuando se env�a un mensaje del control de raycast.
	*/
	namespace MouseEventMessage
	{
		enum TMouseAction
		{
			LEFT_CLICK,
			MIDDLE_CLICK,
			RIGHT_CLICK
		};
	}

	typedef MouseEventMessage::TMouseAction TMouseAction;

	/**
	Clase mensaje que se encargar� de avisar de los eventos del rat�n.

	@author Daniel Flamenco
	@date Enero, 2012
	*/
	class MMouseEvent : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMouseEvent() : IMessage("MMouseEvent") {};

		/**
		M�todo que establece la acci�n que se quiere realizar con este mensaje.

		@param action Tipo de la acci�n a realizar.
		*/
		void setAction(TMouseAction action);

		/**
		M�todo que devuelve la acci�n que se quiere realizar con este mensaje.

		@return Tipo de la acci�n a realizar.
		*/
		TMouseAction getAction();

	protected:

		/**
		Atributo que indica la acci�n que se va a realizar con este mensaje.
		*/
		TMouseAction _action;

	}; // class MMouseEvent

} // namespace Logic

#endif // __Logic_MouseEvent_H