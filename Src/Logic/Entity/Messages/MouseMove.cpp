/**
@file MouseMove.cpp

Contiene la implementación del mensaje que avisa del movimiento del ratón.

@author Alberto Plaza
@date Enero, 2012
*/

#include "MouseMove.h"

namespace Logic
{

	MMouseMove::MMouseMove()
	{
		IMessage();

		_type = "MMouseMove";

	} // MMouseMove

	//---------------------------------------------------------

	void MMouseMove::setPoint(Vector2 point)
	{
		_point = point;

	} // setPoint

	//---------------------------------------------------------

	Vector2 MMouseMove::getPoint()
	{
		return _point;
	
	} // getPoint

	//---------------------------------------------------------

} // namespace Logic