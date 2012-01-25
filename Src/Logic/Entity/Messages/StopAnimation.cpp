/**
@file StopAnimation.cpp

Contiene la implementaci�n del mensaje de parar una animaci�n.

@author Alberto Plaza
@date Enero, 2012
*/

#include "StopAnimation.h"

namespace Logic
{

	CStopAnimation::CStopAnimation()
	{
		IMessage();

		_type = "CStopAnimation";

	} // CStopAnimation

	//---------------------------------------------------------

	void CStopAnimation::setAnimationName(std::string animationName)
	{
		_animationName = animationName;

	} // setAnimationName

	//---------------------------------------------------------

	std::string CStopAnimation::getAnimationName()
	{
		return _animationName;

	} // getAnimationName

	//---------------------------------------------------------

} // namespace Logic