/**
@file AttackEntity.cpp

Contiene la implementación del mensaje de ataque a una entidad.

@author Luis Mendoza
@date Febrero, 2012
*/

#include "AttackEntity.h"

namespace Logic
{

	MAttackEntity::MAttackEntity()
	{
		IMessage();

		_type = "MAttackEntity";

	} // MAttackEntity

	//---------------------------------------------------------

	void MAttackEntity::setEntity(CEntity* entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	CEntity* MAttackEntity::getEntity()
	{
		return _entity;

	} // getEntity

	//---------------------------------------------------------

} // namespace Logic