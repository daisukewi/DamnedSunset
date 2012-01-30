/**
@file Damaged.cpp

Contiene la implementación del mensaje de daño.

@author Luis Mendoza
@date Enero, 2012
*/

#include "Damaged.h"

namespace Logic
{

	CDamaged::CDamaged()
	{
		IMessage();

		_type = "CDamaged";

	} // CDamaged

	//---------------------------------------------------------

	void CDamaged::setHurt(float hurt)
	{
		_hurt = hurt;

	} // setHurt

	//---------------------------------------------------------

	float CDamaged::getHurt()
	{
		return _hurt;

	} // getHurt

	//---------------------------------------------------------

} // namespace Logic