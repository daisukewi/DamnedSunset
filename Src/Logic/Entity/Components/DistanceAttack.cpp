/**
@file TurretController.cpp

Contiene la implementación del componente que controla lo que debe hacer una torreta.
 
@see Logic::CTurretController
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/

#include "DistanceAttack.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Logic/Server.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Physics\Server.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackDistance.h"
#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/StopAnimation.h"

namespace Logic
{
	IMP_FACTORY(CDistanceAttack);
	
	//---------------------------------------------------------

	bool CDistanceAttack::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("precision")){
			_precision = entityInfo->getFloatAttribute("precision");
			
		}else{
			_precision = 1.0;
		}
		if (entityInfo->hasAttribute("damage")){
			_damage = entityInfo->getIntAttribute("damage");
		}else{
			_damage = 40.0;
		}
		if (entityInfo->hasAttribute("attackTime")){
			_attackTime = entityInfo->getIntAttribute("attackTime");
		}else{
			_attackTime = 500;
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CDistanceAttack::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CDistanceAttack::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CDistanceAttack::accept(IMessage *message)
	{
		return !message->getType().compare("MAttackDistance") /*|| !message->getType().compare("MAttackEntity")*/;

	} // accept
	
	//---------------------------------------------------------

	void CDistanceAttack::process(IMessage *message)
	{
		if (!message->getType().compare("MAttackDistance")){
		
		
			MAttackDistance *m = static_cast <MAttackDistance*> (message);

			//Cuando se está atacando continuamente es necesario indicar enviar un mensaje con la variable attack a false para indicar que se deje de atacar
			if (!m->getAttack()){
				_continue = false;
			}else{
				if (!m->getContinue()) {
					_continue = false;
					Vector3 origen = _entity->getPosition();
					Vector3 destino = m->getEntity()->getPosition();
					destino.y = 3.0f;
					Vector3 direction = destino - origen;
					//Descomentar para deviar el disparo a distancia de los personajes
					//direction.x *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
					//direction.y *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
					//direction.z *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
		
					direction.normalise();
					Vector3 impact;
					Ray disparo = Ray(origen, direction);
					Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastGroup(disparo, &impact,
						(Physics::TPhysicGroup)(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER));
					if (!entity->getTag().compare("enemy"))
					{
						MDamaged *m_dam = new MDamaged();
						m_dam->setHurt((_damage)); ///Descomentar para reducir el daño en base a la distancia de los personajes (100.0f * ((_entity->getPosition() - m->getEntity()->getPosition()).length() + 0.1))) * _damage);
						m_dam->setKiller(_entity);
						entity->emitMessage(m_dam, this);
					}
				}else{
					_continue = true;
					_attackEntity = m->getEntity(); 
					_IDAttackEntity = m->getEntityID();

				}
			}
			
		}
		

	} // process
	
	//---------------------------------------------------------

	void CDistanceAttack::tick(unsigned int msecs)
	{

		IComponent::tick(msecs);

		_attackCountTime += msecs;

		if (_continue){
			if (_attackCountTime >= _attackTime){
			
				_attackCountTime = 0;

			
				/*Vector3 origen = _entity->getPosition();
				Vector3 destino =	_attackEntity->getPosition();
				destino.y = 2.0f;
				Vector3 direction = destino - origen;
				//Descomentar para deviar el disparo a distancia de los personajes
				//direction.x *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
				//direction.y *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
				//direction.z *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
		
				direction.normalise();
				Vector3 impact;
				Ray disparo = Ray(origen, direction);
				Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastGroup(disparo, &impact,
					(Physics::TPhysicGroup)(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER));*/
				if (Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_IDAttackEntity)){	
					if (!_attackEntity->getType().compare("Enemy"))
						{
							MDamaged *m_dam = new MDamaged();
							m_dam->setHurt((_damage)); ///Descomentar para reducir el daño en base a la distancia de los personajes (100.0f * ((_entity->getPosition() - m->getEntity()->getPosition()).length() + 0.1))) * _damage);
							m_dam->setKiller(_entity);
							_attackEntity->emitMessage(m_dam, this);
						}
				}else{
					_continue = false;
					_attackCountTime = 0;
				}

			}
		}else{
			_attackCountTime = 0;
		}
	} // tick

	//---------------------------------------------------------

} // namespace Logic

