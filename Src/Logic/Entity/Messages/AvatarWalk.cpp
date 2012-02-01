/**
@file AvatarWalk.cpp

Contiene la implementación del mensaje de mandar andar a una entidad.

@author Alberto Plaza
@date Enero, 2012
*/

#include "AvatarWalk.h"

namespace Logic
{

	MAvatarWalk::MAvatarWalk()
	{
		IMessage();

		_type = "MAvatarWalk";

	} // MAvatarWalk

	//---------------------------------------------------------

	Vector3 MAvatarWalk::getMovement()
	{
		return _movement;

	} // getMovement

	//---------------------------------------------------------

	void MAvatarWalk::setMovement(Vector3 movement)
	{
		_movement = movement;

	} // setMovement

	//---------------------------------------------------------

} // namespace Logic