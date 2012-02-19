/**
@file CureEntity.cpp

Contiene la implementación del mensaje de curación a una entidad.

@author ALberto Ortega
@date Febrero, 2012
*/

#include "CureEntity.h"

namespace Logic
{

	MCureEntity::MCureEntity()
	{
		IMessage();

		_type = "MCureEntity";

	} // MAttackEntity

	//---------------------------------------------------------

	void MCureEntity::setEntity(CEntity* entity)
	{
		_entity = entity;

	} // setEntity

	//---------------------------------------------------------

	CEntity* MCureEntity::getEntity()
	{
		return _entity;

	} // getEntity

	//---------------------------------------------------------

} // namespace Logic