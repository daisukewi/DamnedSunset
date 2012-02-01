/**
@file Damaged.cpp

Contiene la implementaci�n del mensaje de da�o.

@author Luis Mendoza
@date Enero, 2012
*/

#include "Damaged.h"

namespace Logic
{

	MDamaged::MDamaged()
	{
		IMessage();

		_type = "MDamaged";

	} // MDamaged

	//---------------------------------------------------------

	void MDamaged::setHurt(float hurt)
	{
		_hurt = hurt;

	} // setHurt

	//---------------------------------------------------------

	float MDamaged::getHurt()
	{
		return _hurt;

	} // getHurt

	//---------------------------------------------------------

} // namespace Logic