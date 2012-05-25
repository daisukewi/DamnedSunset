/**
@file KeyboardEvent.h

Contiene la declaración del mensaje para avisar de los eventos del teclado.

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
	Clase mensaje que se encargará de avisar de los eventos del teclado.

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
		Método que establece la acción que se quiere realizar con este mensaje.

		@param key Tipo de la acción a realizar.
		*/
		void setKey(GUI::Key::TKeyID key);

		/**
		Método que devuelve la acción que se quiere realizar con este mensaje.

		@return Tipo de la acción a realizar.
		*/
		GUI::Key::TKeyID getKey();

	protected:

		/**
		Atributo que indica la acción que se va a realizar con este mensaje.
		*/
		GUI::Key::TKeyID _key;

	}; // class MKeyboardEvent

} // namespace Logic

#endif // __Logic_KeyboardEvent_H