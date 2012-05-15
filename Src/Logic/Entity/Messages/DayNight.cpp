/**
@file DayNight.cpp

Contiene la declaraci�n del mensaje que indica en que fase del d�a se est�

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
