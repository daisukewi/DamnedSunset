/**
@file AvatarController.cpp

Contiene la implementación del componente que controla el movimiento 
de la entidad.
 
@see Logic::CAvatarController
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "AvatarController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/AvatarWalk.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackEntity.h"

namespace Logic 
{
	IMP_FACTORY(CAvatarController);
	
	//---------------------------------------------------------

	bool CAvatarController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CAvatarController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CAvatarController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CAvatarController::accept(IMessage *message)
	{
		return (!message->getType().compare("MAttackEntity"));

	} // accept
	
	//---------------------------------------------------------

	void CAvatarController::process(IMessage *message)
	{
		if (!message->getType().compare("MAttackEntity"))
		{
			MAttackEntity *m = static_cast <MAttackEntity*> (message);
			_attack = m->getAttack();

			MSetAnimation *m_anim = new MSetAnimation();
			m_anim->setLoop(true);
			if (_attack)
			{
				_enemy = m->getEntity();
				m_anim->setAnimationName("Walk");
			}
			else
			{
				m_anim->setAnimationName("Idle");
			}
			_entity->emitMessage(m_anim, this);
		}

	} // process
	
	//---------------------------------------------------------

	void CAvatarController::turn(float amount) 
	{
		_entity->yaw(amount);

	} // turn
	
	//---------------------------------------------------------

	void CAvatarController::walk() 
	{
		_walking = true;

		// Cambiamos la animación
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName("Walk");
		m->setLoop(true);

		_entity->emitMessage(m, this);

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkBack() 
	{
		_walkingBack = true;

		// Cambiamos la animación
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName("WalkBack");
		m->setLoop(true);

		_entity->emitMessage(m, this);

	} // walkBack
	
	//---------------------------------------------------------

	void CAvatarController::stopWalk() 
	{
		_walking = _walkingBack = false;

		// Cambiamos la animación si no seguimos desplazándonos
		// lateralmente
		if(!(_strafingLeft || _strafingRight))
		{
			MSetAnimation *m = new MSetAnimation();

			m->setAnimationName("Idle");
			m->setLoop(true);

			_entity->emitMessage(m, this);
		}

	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::strafeLeft() 
	{
		_strafingLeft = true;

		// Cambiamos la animación
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName("StrafeLeft");
		m->setLoop(true);

		_entity->emitMessage(m, this);

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::strafeRight() 
	{
		_strafingRight = true;

		// Cambiamos la animación
		MSetAnimation *m = new MSetAnimation();

		m->setAnimationName("StrafeRight");
		m->setLoop(true);

		_entity->emitMessage(m, this);

	} // walkBack
	
	//---------------------------------------------------------
	void CAvatarController::specialAction() 
	{
		/*// TODO PRÁCTICA IA
		// Este método es llamado cuando se activa la acción especial del jugador (por defecto con la tecla E).
		// Aquí se pueden enviar mensajes para testear el funcionamiento de otros componentes.
		AI::CWaypointGraph *wg = AI::CServer::getSingletonPtr()->getNavigationGraph();
		int waypoints = wg->getWaypointCount();
		int targetId = rand() % waypoints;
		Vector3 target = wg->getWaypoint(targetId);
		std::cout << "Navigating to: " << target << std::endl;

		Logic::MWayTo *message2 = new Logic::MWayTo();
		message2->setPoint(target);
		_entity->emitMessage(message2, this);*/
	} // specialAction
	
	//---------------------------------------------------------

	void CAvatarController::stopStrafe() 
	{
		_strafingLeft = _strafingRight = false;

		// Cambiamos la animación si no seguimos andando
		if(!(_walking || _walkingBack))
		{
			MSetAnimation *m = new MSetAnimation();

			m->setAnimationName("Idle");
			m->setLoop(true);

			_entity->emitMessage(m, this);
		}

	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Si nos estamos desplazando calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		if(_walking || _walkingBack || _strafingLeft || _strafingRight)
		{
			Vector3 direction(Vector3::ZERO);
			Vector3 directionStrafe(Vector3::ZERO);

			if(_walking || _walkingBack)
			{
				direction = Math::getDirection(_entity->getYaw());
				if(_walkingBack)
					direction *= -1;
			}

			if(_strafingLeft || _strafingRight)
			{
				directionStrafe = 
						Math::getDirection(_entity->getYaw() + Math::PI/2);
				if(_strafingRight)
					directionStrafe *= -1;
			}

			direction += directionStrafe;
			direction.normalise();
			direction *= msecs * _speed;

			// Enviar un mensaje para que el componente físico mueva el personaje
			Logic::MAvatarWalk *m = new Logic::MAvatarWalk();
			m->setMovement(direction);
			_entity->emitMessage(m);

			//Vector3 newPosition = _entity->getPosition() + direction;
			//_entity->setPosition(newPosition);
		}

		if (_attack)
		{
			// Llevamos al jugador hasta donde está el enemigo
			if ((_enemy->getPosition() - _entity->getPosition()).length() >= 10)
			{
				MMoveSteering *m = new MMoveSteering();
				m->setMovementType(AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
				m->setTarget(_enemy->getPosition());
				_entity->emitMessage(m, this);
			}
			
			else
			{
				MDamaged *m_damage = new MDamaged();

				if (!_enemy->getType().compare("Enemy"))
					// Quitamos 1 punto de vida al enemigo
					m_damage->setHurt(1.0f);
				else
					// Curamos 1 punto de vida al compañero
					m_damage->setHurt(-1.0f);

				m_damage->setKiller(_entity);
				_enemy->emitMessage(m_damage, this);
			}
		}

	} // tick

} // namespace Logic

