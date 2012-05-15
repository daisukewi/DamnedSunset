/**
@file DayNight.cpp

Contiene la declaración del mensaje que indica en que fase del día se está

@author Alberto Ortega
@date Mayo, 2012
*/

#include "DayNight.h"

namespace Logic
{

	MDayNight::MDayNight()
	{
		IMessage();

		_type = "MDayNight";

	} // MAvatarWalk

	//---------------------------------------------------------

	TIME_TYPE MDayNight::getTime()
	{
		return _timeType;

	} // getMovement

	//---------------------------------------------------------

	void MDayNight::setTime(TIME_TYPE timeType)
	{
		_timeType = timeType;

	} // setMovement

	//---------------------------------------------------------

} // namespace Logic
