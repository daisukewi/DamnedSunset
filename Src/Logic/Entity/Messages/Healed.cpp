/**
@file Healed.cpp

Contiene la implementaci�n del mensaje de curaci�n.

@author Luis Mendoza
@date Febrero, 2012
*/

#include "Healed.h"

namespace Logic
{

	MHealed::MHealed()
	{
		IMessage();

		_type = "MHealed";

	} // MHealed

	//---------------------------------------------------------

	void MHealed::setHeal(float heal)
	{
		_heal = heal;

	} // setHeal

	//---------------------------------------------------------

	void MHealed::setHealer(CEntity* healer)
	{
		_healer = healer;

	} // setHealer

	//---------------------------------------------------------

	float MHealed::getHeal()
	{
		return _heal;

	} // getHeal

	//---------------------------------------------------------

	CEntity* MHealed::getHealer()
	{
		return _healer;

	} // getHealer

	//---------------------------------------------------------

} // namespace Logic