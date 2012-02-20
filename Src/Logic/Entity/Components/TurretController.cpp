/**
@file TurretController.cpp

Contiene la implementación del componente que controla lo que debe hacer una torreta.
 
@see Logic::CTurretController
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/

#include "TurretController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackEntity.h"


namespace Logic
{
	IMP_FACTORY(CTurretController);
	
	//---------------------------------------------------------

	bool CTurretController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("precision"))
			_precision = entityInfo->getFloatAttribute("precision");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CTurretController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CTurretController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CTurretController::accept(IMessage *message)
	{
		return !message->getType().compare("MIsTouched") || !message->getType().compare("MAttackEntity");

	} // accept
	
	//---------------------------------------------------------

	void CTurretController::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);

			if (m->getTouched() && !m->getEntity()->getType().compare("Enemy"))
			{
				_enemy = m->getEntity();
				_attacking = true;
				/*
				// Orientamos la torreta hacia el enemigo al que dispara
				float yaw = atan((_enemy->getPosition().x - _entity->getPosition().x) / (_enemy->getPosition().z - _entity->getPosition().z));
				if ((_enemy->getPosition().z - _entity->getPosition().z) >= 0)
					yaw += Math::PI;
				_entity->setYaw(yaw);
				*/
			}
			else if (!m->getTouched())
				_attacking = false;
		}
		else if (!message->getType().compare("MAttackEntity"))
		{
			MAttackEntity *m_attack = static_cast <MAttackEntity*> (message);
			if (!m_attack->getAttack())
				_attacking =false;
		}

	} // process
	
	//---------------------------------------------------------

	void CTurretController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (_attacking && _enemy != NULL)
		{
			MDamaged *m_dam = new MDamaged();
			assert(_enemy);

			m_dam->setHurt(40 * _precision / ((_entity->getPosition() - _enemy->getPosition()).length() + 0.1));
			m_dam->setKiller(_entity);

			_enemy->emitMessage(m_dam, this);
		}


	} // tick

} // namespace Logic

