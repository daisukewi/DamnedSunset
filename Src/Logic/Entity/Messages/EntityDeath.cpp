/**
@file EntityDeath.cpp

Contiene la implementación del mensaje de muerte de una entidad.

@author Luis Mendoza
@date Febrero, 2012
*/

#include "EntityDeath.h"

namespace Logic
{

	MEntityDeath::MEntityDeath()
	{
		IMessage();

		_type = "MEntityDeath";

	} // MEntityDeath

	//---------------------------------------------------------

	void MEntityDeath::setEntityDeath(CEntity* entity)
	{
		_entityDeath = entity;

	} // setEntityDeath

	//---------------------------------------------------------

	CEntity* MEntityDeath::getEntityDeath()
	{
		return _entityDeath;

	} // getEntityDeath

	//---------------------------------------------------------

} // namespace Logic