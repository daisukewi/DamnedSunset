/**
@file EntitySelected.cpp

Contiene la implementación del mensaje ue se encargará de avisar
que se ha creado un enemigo

@author Alberto Ortega
@date Mayo, 2012
*/

#include "EnemyCreated.h"

namespace Logic
{

	MEnemyCreated::MEnemyCreated()
	{
		IMessage();

		_type = "MEnemyCreated";

	} // MEntitySelected

	//---------------------------------------------------------

	void MEnemyCreated::setCreatedEnemy(CEntity *enemy)
	{
		_createdEnemy = enemy;

	} // setCreatedEnemy

	//---------------------------------------------------------

	CEntity* MEnemyCreated::getCreatedEnemy()
	{
		return _createdEnemy;

	} // getCreatedEnemy



} // namespace Logic