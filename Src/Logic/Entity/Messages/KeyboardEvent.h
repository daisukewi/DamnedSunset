/**
@file KeyboardEvent.h

Contiene la declaraci�n del mensaje para avisar de los eventos del teclado.

@see Logic::IMessage

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_KeyboardEvent_H
#define __Logic_KeyboardEvent_H

#include "GUI/InputManager.h"

#include "Logic/Entity/Message.h"

namespace Logic
{



	/**
	Clase mensaje que se encargar� de avisar de los eventos del teclado.

	@author Alberto Ortega
	@date Mayo, 2012
	*/
	class MKeyboardEvent : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MKeyboardEvent();

		/**
		M�todo que establece la acci�n que se quiere realizar con este mensaje.

		@param key Tipo de la acci�n a realizar.
		*/
		void setKey(GUI::Key::TKeyID key);

		/**
		M�todo que devuelve la acci�n que se quiere realizar con este mensaje.

		@return Tipo de la acci�n a realizar.
		*/
		GUI::Key::TKeyID getKey();

	protected:

		/**
		Atributo que indica la acci�n que se va a realizar con este mensaje.
		*/
		GUI::Key::TKeyID _key;

	}; // class MKeyboardEvent

} // namespace Logic

#endif // __Logic_KeyboardEvent_H