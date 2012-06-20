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
#include "Logic/Entity/Messages/SoundEffect.h"

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
			_attackTime = 1000;
		}
		if (entityInfo->hasAttribute("trigger_radius")){
			_maxDistance = entityInfo->getFloatAttribute("trigger_radius");
		}else{
			_maxDistance = 80;
		}
		if (entityInfo->hasAttribute("attackSoundEffect")){
			_attackSoundEffect = entityInfo->getStringAttribute("attackSoundEffect");
		}else{
			_attackSoundEffect = "RifleShot1.ogg";
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
				
					if (Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(m->getEntity()->getEntityID())){
						if (m->getEntity()->getTag().compare("enemy"))
							{
								//Posicionarse mirando al enemigo
								float yaw = atan((_attackEntity->getPosition().x - _entity->getPosition().x) / (_attackEntity->getPosition().z - _entity->getPosition().z));
								if ((_attackEntity->getPosition().z - _entity->getPosition().z) >= 0)
									yaw += Math::PI;
								_entity->setYaw(yaw);


								MDamaged *m_dam = new MDamaged();
								m_dam->setHurt((_damage)); ///Descomentar para reducir el daño en base a la distancia de los personajes (100.0f * ((_entity->getPosition() - m->getEntity()->getPosition()).length() + 0.1))) * _damage);
								m_dam->setKiller(_entity);
								m->getEntity()->emitMessage(m_dam, this);
							
								MSoundEffect *m_sound = new MSoundEffect();
								m_sound->setSoundEffect(_attackSoundEffect);
								_entity->emitMessage(m_sound);

								MSetAnimation *m_anim2  =new MSetAnimation();
								m_anim2->setAnimationName("AttackRifle");
								m_anim2->setNextAnimationName("HoldRifle");
								
								_entity->emitMessage(m_anim2);
						
							}
					}
				}else{
					_continue = true;
					_attackStart = true;
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
		bool finalizar = false;
		_attackCountTime += msecs;

		if (_continue){
			if (_attackCountTime >= _attackTime){
			
				_attackCountTime = 0;

				if (Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_IDAttackEntity)){	
					if (!_attackEntity->getType().compare("Enemy"))
						{
							//Si esta a menos de la distancia máxima
							float difX = _attackEntity->getPosition().x - _entity->getPosition().x;
							float difZ = _attackEntity->getPosition().z - _entity->getPosition().z;

							if ((_maxDistance*_maxDistance) >= (difX*difX + difZ*difZ)){

								//Posicionarse mirando al enemigo
								float yaw = atan((_attackEntity->getPosition().x - _entity->getPosition().x) / (_attackEntity->getPosition().z - _entity->getPosition().z));
								if ((_attackEntity->getPosition().z - _entity->getPosition().z) >= 0)
									yaw += Math::PI;
								_entity->setYaw(yaw);


								//Empezar la animación si es acaba de comenzar el ataque
								if (_attackStart){
									_attackStart = false;

									MSetAnimation *m_anim2  =new MSetAnimation();
									m_anim2->setAnimationName("AttackRifle");
									m_anim2->setLoop(true);
									_entity->emitMessage(m_anim2);


								}


								MDamaged *m_dam = new MDamaged();
								m_dam->setHurt((_damage)); ///Descomentar para reducir el daño en base a la distancia de los personajes (100.0f * ((_entity->getPosition() - m->getEntity()->getPosition()).length() + 0.1))) * _damage);
								m_dam->setKiller(_entity);
								_attackEntity->emitMessage(m_dam, this);



								MSoundEffect *m_sound = new MSoundEffect();
								m_sound->setSoundEffect(_attackSoundEffect);
								_entity->emitMessage(m_sound);
							}else{
								finalizar = true;
							}
		
						}else{
							finalizar = true;
					
						}
				}else{
					finalizar = true;
				}

			}
		}else{
			_attackCountTime = 0;
		}

		if (finalizar){
			_continue = false;
			_attackCountTime = 0;
			MSetAnimation *m_anim  =new MSetAnimation();
			m_anim->setAnimationName("HoldRifle");
			_entity->emitMessage(m_anim);
		}
	} // tick

	//---------------------------------------------------------

} // namespace Logic

