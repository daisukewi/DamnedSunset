/**
@file CameraControl.cpp

Contiene la implementación del mensaje de control de la cámara.

@author Alberto Plaza
@date Enero, 2012
*/

#include "CameraControl.h"

namespace Logic
{

	CCameraControl::CCameraControl()
	{
		IMessage();

		_type = "CCameraControl";

	} // CCameraControl

	//---------------------------------------------------------

	bool CCameraControl::getMouse()
	{
		return _mouse;

	} // getMouse

	//---------------------------------------------------------

	void CCameraControl::setMouse(bool mouse)
	{
		_mouse = mouse;

	} // setMouse

	//---------------------------------------------------------

	std::string CCameraControl::getMovement()
	{
		return _movement;

	} // getMovement

	//---------------------------------------------------------

	void CCameraControl::setMovement(std::string movement)
	{
		_movement = movement;

	} // setMovement

	//---------------------------------------------------------

} // namespace Logic