/**
@file CameraControl.cpp

Contiene la implementación del mensaje de control de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/

#include "CameraControl.h"

namespace Logic
{

	MCameraControl::MCameraControl()
	{
		IMessage();

		_type = "MCameraControl";

	} // MCameraControl

	//---------------------------------------------------------

	bool MCameraControl::getMouse()
	{
		return _mouse;

	} // getMouse

	//---------------------------------------------------------

	void MCameraControl::setMouse(bool mouse)
	{
		_mouse = mouse;

	} // setMouse

	//---------------------------------------------------------

	std::string MCameraControl::getMovement()
	{
		return _movement;

	} // getMovement

	//---------------------------------------------------------

	void MCameraControl::setMovement(std::string movement)
	{
		_movement = movement;

	} // setMovement

	//---------------------------------------------------------

	int MCameraControl::getScroll()
	{
		return _scroll;

	} // getScroll

	//---------------------------------------------------------

	void MCameraControl::setScroll(int scroll)
	{
		_scroll = scroll;

	} // setScroll

	//---------------------------------------------------------

} // namespace Logic