/**
@file MoveTo.cpp

Contiene la implementación del mensaje que indica a una entidad donde tiene que moverse

@author Alberto Ortega
@date Febrero, 2012
*/

#include "MoveTo.h"

namespace Logic
{

	MMoveTo::MMoveTo()
	{
		IMessage();

		_type = "MMoveTo";

	} // MAvatarWalk

	//---------------------------------------------------------

	Vector3 MMoveTo::getPosition()
	{
		return _point;

	} // getMovement

	//---------------------------------------------------------

	void MMoveTo::setPosition(Vector3 point)
	{
		_point = point;

	} // setMovement

	//---------------------------------------------------------

} // namespace Logic
