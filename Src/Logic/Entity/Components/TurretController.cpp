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

#include "Physics\Server.h"
#include "Logic/Server.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/StopAnimation.h"

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

		if (entityInfo->hasAttribute("damage"))
			_damage = entityInfo->getIntAttribute("damage");

		if (entityInfo->hasAttribute("timeBetweenShoots"))
			_timeBetweenShoots = entityInfo->getFloatAttribute("timeBetweenShoots");

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
			CEntity *ent = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(m->getEntityID());
			if (ent)
			{
				if (m->getTouched() && !ent->getType().compare("Enemy"))
				{
					_enemiesID.push_back(m->getEntityID());
					if (!_attacking)
					{
						//Si no estaba atacando, ponemos para que dispare al siguiente tick y ponemos la animacion
						_attacking = true;
						MSetAnimation *m_anim = new MSetAnimation();
						m_anim->setAnimationName("torreta");
						m_anim->setLoop(true);
						_entity->emitMessage(m_anim);
					}
				}
				else if (!m->getTouched())
				{
					_enemiesID.remove(m->getEntityID());
					_attacking = !(_enemiesID.empty());

					if (!_attacking)
					{
						MStopAnimation *m_stop = new MStopAnimation();
						m_stop->setAnimationName("torreta");
						_entity->emitMessage(m_stop);
					}
				}
			}
			else
			{
				std::cout << "\n ENEMIGO HA MUERTO \n";
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
		
		_currentTime += msecs;

		if ((_attacking) && (_currentTime > _timeBetweenShoots))
		{
			_currentTime = 0;

			//Buscamos la entidad a la que disparar de la lista de entidades que han entrado en su rango
			Logic::CEntity * targetEntity;
			do {
				unsigned int id = _enemiesID.back();
				targetEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(id);
				if (targetEntity == NULL)
					_enemiesID.remove(id);
			} while (targetEntity == NULL && !_enemiesID.empty());

			if (targetEntity)
			{
				/*Vector3 origen = _entity->getPosition();
				Vector3 destino = targetEntity->getPosition();
				destino.y = 3.0f;
				Vector3 direction = destino - origen;
				direction.x *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
				direction.y *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
				direction.z *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);*/
				/*
				std::cout << _enemies->back()->getPosition() << '\n';
				std::cout << origen << '\n';
				std::cout << origen +  1 * direction << '\n';
				*/
				/*direction.normalise();
				Vector3 impact;
				Ray disparo = Ray(origen, direction);
				Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastGroup(disparo, &impact,
					(Physics::TPhysicGroup)(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER));

				if (entity == targetEntity)
				{
					MDamaged *m_dam = new MDamaged();
					m_dam->setHurt((40 * msecs * _precision / (100.0f * ((_entity->getPosition() - targetEntity->getPosition()).length() + 0.1))) * _damage);
					m_dam->setKiller(_entity);
					targetEntity->emitMessage(m_dam, this);
				}
				else
				{
					std::cout << "Fallo!!!\n";
				}*/

				MDamaged *m_dam = new MDamaged();
				m_dam->setHurt(_damage);
				m_dam->setKiller(_entity);
				targetEntity->emitMessage(m_dam, this);
			}
			else 
			{
				//Deja de disparar
				MStopAnimation *m_stop = new MStopAnimation();
				m_stop->setAnimationName("torreta");
				_entity->emitMessage(m_stop);
				_attacking = false;
			}	
		}
	} // tick

} // namespace Logic

