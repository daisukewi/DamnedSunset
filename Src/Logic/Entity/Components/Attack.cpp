/**
@file Attack.cpp

Contiene la implementación del componente que controla el ataque de una entidad.
 
@see Logic::CAttack
@see Logic::IComponent

@author Luis Mendoza
@date Marzo, 2012
*/

#include "Attack.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackEntity.h"

#include "ScriptManager/Server.h"

namespace Logic 
{
	IMP_FACTORY(CAttack);
	
	//---------------------------------------------------------

	bool CAttack::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("damage"))
			_damage = entityInfo->getFloatAttribute("damage");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CAttack::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CAttack::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CAttack::accept(IMessage *message)
	{
		return (!message->getType().compare("MAttackEntity"));

	} // accept
	
	//---------------------------------------------------------

	void CAttack::process(IMessage *message)
	{
		if (!message->getType().compare("MAttackEntity"))
		{
			MAttackEntity *m = static_cast <MAttackEntity*> (message);
			_attack = m->getAttack();

			MSetAnimation *m_anim = new MSetAnimation();
			m_anim->setLoop(true);
			if (_attack)
			{
				_targetEntity = m->getEntity();
				_targetEntity->addDeathListener(this);
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

	void CAttack::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_attack)
		{
			// Llevamos al jugador hasta donde está la entidad objetivo
			if ((_targetEntity->getPosition() - _entity->getPosition()).length() >= 20)
			{
				MMoveSteering *m = new MMoveSteering();
				m->setMovementType(AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
				m->setTarget(_targetEntity->getPosition());
				_entity->emitMessage(m, this);
			}
			else
			{
				MDamaged *m_damage = new MDamaged();
				// Quitamos 1 punto de vida al enemigo
				//m_damage->setHurt(msecs / 100.0f);
				m_damage->setHurt(_damage / msecs);
				m_damage->setKiller(_entity);
				_targetEntity->emitMessage(m_damage, this);	
			}
		}

	} // tick

	//---------------------------------------------------------

	void CAttack::entityDeath(CEntity* entity)
	{
		/* 
		Implementación del método que va a ser llamado cuando muera la entidad.
		*/
		_attack = false;

		// Si la entidad que se ha muerto es un jugador, también aviso a lua de la muerte del mismo.
		if (!entity->getType().compare("Player"))
		{
			std::stringstream script;
			script << "enemyEventParam = { playerDeath = " << entity->getEntityID() <<  " } ";
			script << "enemyEvent(\"OnPlayerDeath\", " << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Si la entidad que se ha muerto es un edificio, también aviso a lua de la muerte del mismo.
		if (!entity->getTag().compare("playerBuilding"))
		{
			std::stringstream script;
			script << "enemyEventParam = { buildingDestroy = " << entity->getEntityID() <<  " } ";
			script << "enemyEvent(\"OnBuildingDestroy\", " << _entity->getEntityID() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		//entity->removeDeathListener(this);

	} // entityDeath

} // namespace Logic

