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
			|| !message->getType().compare("MEntitySelected");

		if (accepted) message->addPtr();

		return accepted;
	} // accept
	
	//---------------------------------------------------------

	void CSelectionController::process(IMessage *message)
	{
		if (!message->getType().compare("MMouseEvent"))
		{
			if (!_canSelect) return;
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

		} else if (!message->getType().compare("MControlRaycast"))
		{
			MControlRaycast *m_raycast = static_cast <MControlRaycast*> (message);
			switch (m_raycast->getAction())
			{
				case RaycastMessage::START_RAYCAST:
					_canSelect = false;
					break;
				case RaycastMessage::STOP_RAYCAST:
					_canSelect = true;
					break;
				case RaycastMessage::HIT_RAYCAST:
					if (!_isSelecting && !_isWaitingForAction) return;
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

		if (colEntity->getType().compare("Player") == 0)
		{
			if (_isSelecting)
				saveSelectedEntity(colEntity);

		} else if (colEntity->getType().compare("World") == 0)
		{
			if (_selectedEntity != NULL && _isWaitingForAction)
			{
				TMessage m;
				m._type = Message::MOVE_TO;
				m._vector3 = colPoint;
				m._int = AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE;
				_entity->emitMessage(m);
			}
		}

		_isSelecting = false;
		_isWaitingForAction = false;

		// Mandamos un mensaje para dejar de lanzar raycasts
		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::STOP_RAYCAST);
		_entity->emitMessage(rc_message);

	} // processRayCast

	//---------------------------------------------------------

	void CSelectionController::startSelection()
	{
		/*_isSelecting = true;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		_entity->emitMessage(rc_message, this);*/

	} // startSelection

	//---------------------------------------------------------

	void CSelectionController::startAction()
	{
		/*_isWaitingForAction = true;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		_entity->emitMessage(rc_message, this);*/

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
