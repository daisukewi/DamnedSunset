/**
@file TeletransportTo.cpp

Contiene la implementación del mensaje de teletransporte.

@author Luis Mendoza
@date Abril, 2012
*/

#include "TeletransportTo.h"

namespace Logic
{

	MTeletransportTo::MTeletransportTo()
	{
		IMessage();

		_type = "MTeletransportTo";

	} // MTeletransportTo

	//---------------------------------------------------------

	void MTeletransportTo::setPosition(Vector3 position)
	{
		_position = position;

	} // setPosition

	//---------------------------------------------------------

	Vector3 MTeletransportTo::getPosition()
	{
		return _position;

	} // getPosition

	//---------------------------------------------------------

} // namespace Logic