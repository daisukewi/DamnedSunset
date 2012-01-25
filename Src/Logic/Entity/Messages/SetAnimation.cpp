/**
@file SetAnimation.cpp

Contiene la implementación del mensaje de poner una animación.

@author Alberto Plaza
@date Enero, 2012
*/

#include "SetAnimation.h"

namespace Logic
{

	CSetAnimation::CSetAnimation()
	{
		IMessage();

		_type = "CSetAnimation";

	} // CSetAnimation

	//---------------------------------------------------------

	void CSetAnimation::setAnimationName(std::string animationName)
	{
		_animationName = animationName;

	} // setAnimationName

	//---------------------------------------------------------

	std::string CSetAnimation::getAnimationName()
	{
		return _animationName;

	} // getAnimationName

	//---------------------------------------------------------

	void CSetAnimation::setLoop(bool loop)
	{
		_loop = loop;

	} // setLoop

	//---------------------------------------------------------

	bool CSetAnimation::getLoop()
	{
		return _loop;

	} // getLoop

	//---------------------------------------------------------

} // namespace Logic