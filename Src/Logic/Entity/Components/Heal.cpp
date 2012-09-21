/**
@file Heal.cpp

Contiene la implementación del componente que controla la curación.
 
@see Logic::CHeal
@see Logic::IComponent

@author Luis Mendoza
@date Marzo, 2012
*/

#include "Heal.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/Healed.h"
#include "Logic/Entity/Messages/CureEntity.h"

namespace Logic 
{
	IMP_FACTORY(CHeal);
	
	//---------------------------------------------------------

	bool CHeal::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("healSound"))
			_healSound = entityInfo->getFloatAttribute("healSound");


		if(entityInfo->hasAttribute("healEffect"))
			_healEffect = entityInfo->getFloatAttribute("healEffect");

		if(entityInfo->hasAttribute("healLife"))
			_lifeToHeal = entityInfo->getFloatAttribute("healLife");


		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CHeal::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CHeal::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CHeal::accept(IMessage *message)
	{
		return (!message->getType().compare("MCureEntity"));

	} // accept
	
	//---------------------------------------------------------

	void CHeal::process(IMessage *message)
	{
		if (!message->getType().compare("MCureEntity"))
		{
			MCureEntity *m_cure = static_cast <MCureEntity*> (message);
			_cure = m_cure->getCure();
			if (_cure)
			{
				_targetEntity = m_cure->getEntity();
			}
		}

	} // process
	
	//---------------------------------------------------------

	void CHeal::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_cure)
		{
			// Llevamos al jugador hasta donde está la entidad objetivo
			if ((_targetEntity->getPosition() - _entity->getPosition()).length() >= 30)
			{
				MMoveSteering *m = new MMoveSteering();
				m->setMovementType(AI::IMovement::MOVEMENT_KINEMATIC_AVOID);
				m->setTarget(_targetEntity->getPosition());
				_entity->emitMessage(m, this);
			}
			else
			{	
				MHealed *m_heal = new MHealed();
				// Curamos _lifeToHeal puntos de vida al compañero
				m_heal->setHeal(_lifeToHeal);
				m_heal->setHealer(_entity);
				_targetEntity->emitMessage(m_heal, this);
				_cure = false;
			}
		}
	} // tick

} // namespace Logic