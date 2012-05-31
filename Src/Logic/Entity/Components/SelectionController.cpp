/**
@file SelectionController.cpp

Contiene la implementacion del componente que se encarga de decidir
que cosas se seleccionan cuando se hace click izquierdo, y que sobre que
entidades se actua cuando se hace click derecho.

@see Logic::CSelectionController
@see Logic::IComponent

@author Daniel Flamenco
@date Mayo, 2012
*/

#include "SelectionController.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Messages/EntitySelected.h"
#include "Logic/Entity/Messages/IsSelectable.h"
#include "Logic/Entity/Messages/IsActuable.h"

#include "BaseSubsystems/Server.h"

#include "ScriptManager/Server.h"

#include "Physics/Server.h"

#include <assert.h>
#include <sstream>

namespace Logic 
{
	IMP_FACTORY(CSelectionController);
	
	//---------------------------------------------------------

	bool CSelectionController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSelectionController::activate()
	{
		return true;

	} // activate
	
	//---------------------------------------------------------

	void CSelectionController::deactivate()
	{
		

	} // deactivate
	
	//---------------------------------------------------------

	bool CSelectionController::accept(IMessage *message)
	{
		return !message->getType().compare("MKeyboardEvent") 
			|| !message->getType().compare("MMouseEvent")
			|| !message->getType().compare("MEntitySelected")
			|| !message->getType().compare("MIsSelectable")
			|| !message->getType().compare("MIsActuable");

	} // accept
	
	//---------------------------------------------------------

	void CSelectionController::process(IMessage *message)
	{
		if (!message->getType().compare("MKeyboardEvent")){
			//IMPORTANTE Habrá que pensar donde se van a detectar las teclas
			/*if (_selectedEntity){
				message->addPtr();
				_selectedEntity->emitMessage(message);
				message->removePtr();
			}*/

		}
		else if (!message->getType().compare("MMouseEvent"))
		{
			MMouseEvent *m_mouse = static_cast <MMouseEvent*> (message);

			switch (m_mouse->getAction())
			{
			case TMouseAction::LEFT_CLICK:
				prepareSelectionClick();
				break;
			case TMouseAction::MIDDLE_CLICK:
				//No action
				break;
			case TMouseAction::RIGHT_CLICK:
				prepareActionClick();
				break;
			}

		}
		else if (!message->getType().compare("MIsSelectable"))
		{
			MIsSelectable *m_selectable = static_cast <MIsSelectable*> (message);

			if (_waitingForSelectable && m_selectable->getMessageType() == SelectablePetition::SELECTION_RESPONSE)
			{
				_targetEntityID = m_selectable->getSenderEntity()->getEntityID();
				processSelectionClick();
				return;
			}

		}
		else if (!message->getType().compare("MIsActuable"))
		{
			MIsActuable *m_actuable = static_cast <MIsActuable*> (message);

			if (_waitingForActuable && m_actuable->getMessageType() == ActuablePetition::ACTION_RESPONSE)
			{
				_targetEntityID = m_actuable->getSenderEntity()->getEntityID();
				processActionClick();
				return;
			}
		}
		
	} // process


	//---------------------------------------------------------

	void CSelectionController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	//---------------------------------------------------------

	void CSelectionController::prepareSelectionClick()
	{
		_targetEntityID = -1;
		_waitingForSelectable = false;
		_worldCollisionPoint = Vector3(0, -1, 0);

		// Send raycast to obtain the mouse hit point with the world
		if (Logic::CServer::getSingletonPtr()->raycastFromViewport(&_worldCollisionPoint, Physics::PG_WORLD) == NULL)
			return;

		Vector3 point;

		CEntity* targetedEntity = Logic::CServer::getSingletonPtr()->raycastFromViewport(&point, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		if (targetedEntity == NULL)
		{
			processSelectionClick();
			return;
		}

		_targetEntityID = targetedEntity->getEntityID();
		_waitingForSelectable = true;

		// Send a message to the entity hit to ensure its selectability
		MIsSelectable* m_selectable = new MIsSelectable();
		m_selectable->setMessageType(SELECTION_REQUEST);
		m_selectable->setSenderEntity(_entity);
		// Send the message as instant. The response must be send instantly as well.
		targetedEntity->emitInstantMessage(m_selectable, this);

		_waitingForSelectable = false;

	} // prepareSelectionClick

	//---------------------------------------------------------

	void CSelectionController::prepareActionClick()
	{
		_targetEntityID = -1;
		_waitingForActuable = false;
		_worldCollisionPoint = Vector3(0, -1, 0);

		// Send raycast to obtain the mouse hit point with the world
		if (Logic::CServer::getSingletonPtr()->raycastFromViewport(&_worldCollisionPoint, Physics::PG_WORLD) == NULL)
			return;

		Vector3 point;

		CEntity* targetedEntity = Logic::CServer::getSingletonPtr()->raycastFromViewport(&point, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		if (targetedEntity == NULL)
		{
			processActionClick();
			return;
		}

		_targetEntityID = targetedEntity->getEntityID();
		_waitingForActuable = true;

		// Send message to the entitiy hit to ensure its actuability
		//MIsActuable* m_actuable = new MIsActuable();
		//m_actuable->setMessageType(ACTION_REQUEST);
		//m_actuable->setSenderEntity(_entity);
		//targetedEntity->emitMessage(m_actuable);
		
		// @TODO: Create a component to decide if the plalyer can actuate over that entity or not.
		processActionClick();

		_waitingForActuable = false;

	} // prepareActionClick

	//---------------------------------------------------------

	void CSelectionController::processSelectionClick()
	{
		_waitingForSelectable = false;

		//Send a message with the Selection petition, the world mouse click point, and the entity.
		std::stringstream procSelec;
		procSelec << "processSelection(" << _targetEntityID << ", " << _worldCollisionPoint.x << ", " << _worldCollisionPoint.y << ", " << _worldCollisionPoint.z << ")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(procSelec.str().c_str());

	} // processSelectionClick done <-- by Pedro

	//---------------------------------------------------------

	void CSelectionController::processActionClick()
	{
		_waitingForActuable = false;

		// Send a message with the Action petition, the world mouse richt-click point, and the entity.
		std::stringstream procSelec;
		procSelec << "processAction(" << _targetEntityID << ", " << _worldCollisionPoint.x << ", " << _worldCollisionPoint.y << ", " << _worldCollisionPoint.z << ")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(procSelec.str().c_str());

	} // processActionClick


} // namespace Logic
