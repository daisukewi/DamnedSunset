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
#include "Logic/Entity/Messages/SetAnimation.h"


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

		_enemies = new TEntityList();

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
		return !message->getType().compare("MIsTouched") /*|| !message->getType().compare("MAttackEntity")*/;

	} // accept
	
	//---------------------------------------------------------

	void CTurretController::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);

			if (m->getTouched() && !m->getEntity()->getType().compare("Enemy"))
			{
				_enemies->push_back(m->getEntity());
				_attacking = true;
				/*
				Apunto a la torreta a la muerte del enemigo que acaba de llegar.
				*/
				_enemies->back()->addDeathListener(this);
				/*
				// Orientamos la torreta hacia el enemigo al que dispara
				float yaw = atan((_enemy->getPosition().x - _entity->getPosition().x) / (_enemy->getPosition().z - _entity->getPosition().z));
				if ((_enemy->getPosition().z - _entity->getPosition().z) >= 0)
					yaw += Math::PI;
				_entity->setYaw(yaw);
				*/
				MSetAnimation *m_anim = new MSetAnimation();
				m_anim->setAnimationName("torreta");
				m_anim->setLoop(true);
				_entity->emitMessage(m_anim);
			}
			else if (!m->getTouched())
			{
				if (_enemies != NULL)
				{
					_enemies->remove(m->getEntity());
					_attacking = !(_enemies->empty());
				}
			}
		}
		/*
		else if (!message->getType().compare("MAttackEntity"))
		{
			MAttackEntity *m_attack = static_cast <MAttackEntity*> (message);
			if (!m_attack->getAttack())
			{
				_attacking =false;
				assert(m_attack->getEntity());
				_enemies->remove(m_attack->getEntity());
			}
		}
		*/

	} // process
	
	//---------------------------------------------------------

	void CTurretController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (_attacking)
		{
			MDamaged *m_dam = new MDamaged();
			assert(_enemies->back());

			m_dam->setHurt(40 * _precision / ((_entity->getPosition() - _enemies->back()->getPosition()).length() + 0.1));
			m_dam->setKiller(_entity);

			assert(_enemies->back());
			_enemies->back()->emitMessage(m_dam, this);
		}


	} // tick

	//---------------------------------------------------------

	void CTurretController::entityDeath(CEntity* entity)
	{
		/* 
		Implementación del método que va a ser llamado cuando muera la entidad.
		*/
		_enemies->remove(entity);
		_attacking = !(_enemies->empty());
		entity->removeDeathListener(this);

	} // entityDeath

	//---------------------------------------------------------

} // namespace Logic

