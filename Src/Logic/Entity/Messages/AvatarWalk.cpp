/**
@file AvatarWalk.cpp

Contiene la implementación del mensaje de mandar andar a una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "AvatarWalk.h"

namespace Logic
{

	CAvatarWalk::CAvatarWalk()
	{
		IMessage();

		_type = "CAvatarWalk";

	} // CAvatarWalk

	//---------------------------------------------------------

	Vector3 CAvatarWalk::getMovement()
	{
		return _movement;

	} // getMovement

	//---------------------------------------------------------

	void CAvatarWalk::setMovement(Vector3 movement)
	{
		_movement = movement;

	} // setMovement

	//---------------------------------------------------------

} // namespace Logic