/**
@file MouseEvent.cpp

Contiene la implementación del mensaje para controlar avisar de los eventos del raton.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "MouseEvent.h"

namespace Logic
{

	MMouseEvent::MMouseEvent()
	{
		IMessage();

		_type = "MMouseEvent";

	} // MMouseEvent

	//---------------------------------------------------------

	void MMouseEvent::setAction(TMouseAction action)
	{
		_action = action;

	} // setAction

	//---------------------------------------------------------

	TMouseAction MMouseEvent::getAction()
	{
		return _action;

	} // getAction

} // namespace Logic