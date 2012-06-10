/**
@file MouseEvent.cpp

Contiene la implementación del mensaje para controlar avisar de los eventos del raton.

@author Daniel Flamenco
@date Enero, 2012
*/

#include "MouseEvent.h"

#include "BaseSubsystems/Math.h"

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
	
	//---------------------------------------------------------
	void MMouseEvent::setRelPosition(Vector2 relPosition){
		_relPosition = relPosition;
	} // setRelPosition
	
	//---------------------------------------------------------
	Vector2 MMouseEvent::getRelPosition(){
		return _relPosition;
	}


} // namespace Logic