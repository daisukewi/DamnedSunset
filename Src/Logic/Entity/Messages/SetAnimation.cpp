/**
@file SetAnimation.cpp

Contiene la implementaci�n del mensaje de poner una animaci�n.

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