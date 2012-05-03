/**
@file AttackDistance.cpp

Contiene la implementación del mensaje de ataque a una entidad.

@author Alberto Ortega
@date Mayo, 2012
*/

#include "AttackDistance.h"

namespace Logic
{

	MAttackDistance::MAttackDistance()
	{
		IMessage();

		_type = "MAttackDistance";

	} // MAttackDistance

	//---------------------------------------------------------

	void MAttackDistance::setEntity(CEntity* entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	CEntity* MAttackDistance::getEntity()
	{
		return _entity;

	} // getEntity

	//---------------------------------------------------------

} // namespace Logic