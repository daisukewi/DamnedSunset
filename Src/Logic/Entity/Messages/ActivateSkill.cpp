/**
@file ActivateSkill.cpp

Contiene la implementación del mensaje para activar una habilidad.

@author Luis Mendoza
@date Febrero, 2012
*/

#include "ActivateSkill.h"

namespace Logic
{

	MActivateSkill::MActivateSkill()
	{
		IMessage();

		_type = "MActivateSkill";

	} // MActivateSkill

	//---------------------------------------------------------

	void MActivateSkill::setSkill(int skill)
	{
		_skill = skill;

	} // setSkill

	//---------------------------------------------------------

	int MActivateSkill::getSkill()
	{
		return _skill;

	} // getSkill

	//---------------------------------------------------------

} // namespace Logic