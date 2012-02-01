/**
@file SetAnimation.cpp

Contiene la implementación del mensaje de poner una animación.

@author Alberto Plaza
@date Enero, 2012
*/

#include "SetAnimation.h"

namespace Logic
{

	MSetAnimation::MSetAnimation()
	{
		IMessage();

		_type = "MSetAnimation";

	} // MSetAnimation

	//---------------------------------------------------------

	void MSetAnimation::setAnimationName(std::string animationName)
	{
		_animationName = animationName;

	} // setAnimationName

	//---------------------------------------------------------

	std::string MSetAnimation::getAnimationName()
	{
		return _animationName;

	} // getAnimationName

	//---------------------------------------------------------

	void MSetAnimation::setLoop(bool loop)
	{
		_loop = loop;

	} // setLoop

	//---------------------------------------------------------

	bool MSetAnimation::getLoop()
	{
		return _loop;

	} // getLoop

	//---------------------------------------------------------

} // namespace Logic