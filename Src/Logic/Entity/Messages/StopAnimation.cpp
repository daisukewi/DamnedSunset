/**
@file StopAnimation.cpp

Contiene la implementación del mensaje de parar una animación.

@author Alberto Plaza
@date Enero, 2012
*/

#include "StopAnimation.h"

namespace Logic
{

	MStopAnimation::MStopAnimation()
	{
		IMessage();

		_type = "MStopAnimation";

	} // MStopAnimation

	//---------------------------------------------------------

	void MStopAnimation::setAnimationName(std::string animationName)
	{
		_animationName = animationName;

	} // setAnimationName

	//---------------------------------------------------------

	std::string MStopAnimation::getAnimationName()
	{
		return _animationName;

	} // getAnimationName

	//---------------------------------------------------------

} // namespace Logic