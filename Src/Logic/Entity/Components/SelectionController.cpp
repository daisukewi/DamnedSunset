#include "SelectionController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "AI/Movement.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Messages/ControlRaycast.h"
#include "Logic/Entity/Messages/EntitySelected.h"
#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Logic/Entity/Messages/MoveSteering.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/EmplaceBuilding.h"

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
		bool accepted = !message->getType().compare("MMouseEvent")
			|| !message->getType().compare("MControlRaycast")
			|| !message->getType().compare("MEntitySelected")
			|| !message->getType().compare("MEmplaceBuilding");

		if (accepted) message->addPtr();

		return accepted;
	} // accept
	
	//---------------------------------------------------------

	void CSelectionController::process(IMessage *message)
	{
		if (!message->getType().compare("MMouseEvent"))
		{
			if (_canSelect)
			{
				MMouseEvent *m_mouse = static_cast <MMouseEvent*> (message);

				switch(m_mouse->getAction())
				{
					case TMouseAction::LEFT_CLICK:
						startSelection();
						break;
					case TMouseAction::RIGHT_CLICK:
						startAction();
						break;
				}
			}

		} else if (!message->getType().compare("MEmplaceBuilding"))
		{
			// TODO: (Blackboard): Este pequeño hack evita realizar acciones cuando se ha mandado
			// la orden de construir. Se puede modificar si se implemente el blackboard.
			MEmplaceBuilding *m_building = static_cast <MEmplaceBuilding*> (message);
			switch (m_building->getAction())
			{
				case BuildingMessage::START_BUILDING:
					_canSelect = false;
					break;
				case BuildingMessage::EMPLACE_BUILDING:
				case BuildingMessage::CANCEL_BUILDING:
					_canSelect = true;
					break;
			}

		} else if (!message->getType().compare("MControlRaycast"))
		{
			MControlRaycast *m_raycast = static_cast <MControlRaycast*> (message);
			switch (m_raycast->getAction())
			{
				case RaycastMessage::HIT_RAYCAST:
					if (_isSelecting || _isWaitingForAction)
						processRayCast(m_raycast->getCollisionPoint(), m_raycast->getCollisionEntity());
					break;
			}

		} else if (!message->getType().compare("MEntitySelected"))
		{
			MEntitySelected *m_selection = static_cast <MEntitySelected*> (message);
			saveSelectedEntity(m_selection->getSelectedEntity());
		}

		message->removePtr();

	} // process

	//---------------------------------------------------------

	void CSelectionController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	//---------------------------------------------------------

	void CSelectionController::processRayCast( Vector3 colPoint, CEntity* colEntity )
	{
		// Hack para cancelar la orden mientras se está construyendo.
		if (!_canSelect)
		{
			_isSelecting = _isWaitingForAction = false;
			return;
		}

		// Procesar mensaje del raycast cuando se está seleccionando
		if (_isSelecting)
		{
			if (!colEntity->getType().compare("Player"))
			{
				saveSelectedEntity(colEntity);

			}

		// Procesar mensaje del raycast cuando se hace una accion y se tiene algo seleccionado
		} else if (_isWaitingForAction && _selectedEntity != NULL)
		{
			if (!colEntity->getType().compare("Player"))
			{
				// Realizar acciones sobre un jugador.

			// Realizar acciones sobre el suelo
			} else if (!colEntity->getType().compare("World"))
			{
				CMoveSteering *m_movement = new CMoveSteering();
				m_movement->setMovementType(AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);
				m_movement->setTarget(colPoint);
				_selectedEntity->emitMessage(m_movement, this);

			// Realizar acciones sobre un enemigo
			} else if (!colEntity->getType().compare("Enemy"))
			{
				if (!_selectedEntity->getType().compare("Player"))
				{
					CDamaged *m_damage = new CDamaged();
					m_damage->setHurt(10.0f);
					colEntity->emitMessage(m_damage, this);
				}
			}
		}
		
		_isSelecting = false;
		_isWaitingForAction = false;

		// Mandamos un mensaje para dejar de lanzar raycasts
		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::STOP_RAYCAST);
		_entity->emitMessage(rc_message, this);

	} // processRayCast

	//---------------------------------------------------------

	void CSelectionController::startSelection()
	{
		_isSelecting = true;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		_entity->emitMessage(rc_message, this);

	} // startSelection

	//---------------------------------------------------------

	void CSelectionController::startAction()
	{
		_isWaitingForAction = true;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		_entity->emitMessage(rc_message, this);

	} // startAction

	void CSelectionController::saveSelectedEntity( CEntity* selectedEntity )
	{
		_selectedEntity = selectedEntity;

		//Mandamos un mensaje a la camara para que se centre en el jugador
		CUbicarCamara *m_ubicar = new CUbicarCamara();
		m_ubicar->setPosition(_selectedEntity->getPosition());
		_entity->emitMessage(m_ubicar, this);

	} // saveSelectedEntity

} // namespace Logic
