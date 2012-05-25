/**
@file KeyboardEvent.cpp

Contiene la implementación del mensaje para controlar avisar de los eventos del teclado.

@author Alberto Ortega
@date Mayo, 2012
*/

#include "GUI/InputManager.h"
#include "Logic/Entity/Messages/KeyboardEvent.h"

namespace Logic
{

	MKeyboardEvent::MKeyboardEvent()
	{
		IMessage();

		_type = "MKeyboardEvent";

	} // MKeyboardEvent

	//---------------------------------------------------------

	void MKeyboardEvent::setKey(GUI::Key::TKeyID key)
	{
		_key = key;

	} // setKey

	//---------------------------------------------------------

	GUI::Key::TKeyID MKeyboardEvent::getKey()
	{
		return _key;

	} // geKey

} // namespace Logic