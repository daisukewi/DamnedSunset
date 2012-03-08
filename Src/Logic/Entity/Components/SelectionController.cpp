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
#include "Logic/Entity/Messages/AStarRoute.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/EmplaceBuilding.h"
#include "Logic/Entity/Messages/IsSelectable.h"
#include "Logic/Entity/Messages/ActivateSkill.h"
#include "Logic/Entity/Messages/LanzarGranada.h"
#include "Logic/Entity/Messages/CureEntity.h"

#include "Logic/Entity/GodStates/Free.h"
#include "Logic/Entity/GodStates/BuildSelected.h"
#include "Logic/Entity/GodStates/PlayerSelected.h"
#include "Logic/Entity/GodStates/GodState.h"
#include "Logic/Entity/GodStates/Healing.h"
#include "Logic/Entity/GodStates/Building.h"
#include "Logic/Entity/GodStates/LanzandoGranada.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"

#include <assert.h>
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

		//Inicializar los estados
		
		_godStates = new IGodState*[_numStates];
		_activeState = _godStates[State::FREE] = new CFree(this);
		_godStates[State::PLAYER_SELECTED] = new CPlayerSelected(this);
		_godStates[State::BUILD_SELECTED] = new CBuildSelected(this);
		_godStates[State::BUILDING] = new CBuilding(this);
		_godStates[State::HEALING] = new CHealing(this);
		_godStates[State::LANZANDO_GRANADA] = new CLanzandoGranada(this);
		_selectedEntity = NULL;
		
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSelectionController::deactivate()
	{
		for(int i = 0; i < _numStates ; i++){
			delete _godStates[i];
		}

	} // deactivate
	
	//---------------------------------------------------------

	bool CSelectionController::accept(IMessage *message)
	{
		bool accepted = !message->getType().compare("MMouseEvent")
			|| !message->getType().compare("MControlRaycast")
			|| !message->getType().compare("MEntitySelected")
			|| !message->getType().compare("MEmplaceBuilding")
			|| !message->getType().compare("MActivateSkill")
			|| !message->getType().compare("MLanzarGranada");

		if (accepted) message->addPtr();

		return accepted;
	} // accept
	
	//---------------------------------------------------------

	void CSelectionController::process(IMessage *message)
	{
		
		/*if (!message->getType().compare("MMouseEvent"))
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
					if (_isSelecting || _isWaitingForAction){
						//Comprobar si la entidad es seleccionable
						CEntity *col_entity = m_raycast->getCollisionEntity();
						
						MIsSelectable* message = new MIsSelectable();
						message->setPoint(m_raycast->getCollisionPoint());
						col_entity->emitMessage(message);

					}
					break;
			}

		} else if (!message->getType().compare("MEntitySelected"))
		{
			MEntitySelected *m_selection = static_cast <MEntitySelected*> (message);
			processEntity(m_selection->getPoint(),m_selection->getSelectedEntity());
		} else if (!message->getType().compare("MActivateSkill"))
		{
			MActivateSkill *m_skill = static_cast <MActivateSkill*> (message);
			_skill = m_skill->getSkill();

		}
		
		message->removePtr();
		
		*/
		

		if (!message->getType().compare("MMouseEvent"))
		{
			MMouseEvent *m_mouse = static_cast <MMouseEvent*> (message);

			//Almacenar el botón que ha sido pulsado del ratón
			_button = m_mouse->getAction();

			//Pedir al componente de lanzar rayos que empiece a hacerlo
			MControlRaycast *rc_message = new MControlRaycast();
			rc_message->setAction(RaycastMessage::START_RAYCAST);
			rc_message->setCollisionGroups(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER);
			_entity->emitMessage(rc_message, this);
			_raycastStart = true;
			//std::cout << "MOUSE_EVENT" << "\n";
			
		}else if (!message->getType().compare("MEmplaceBuilding"))
		{
			MEmplaceBuilding *m_building = static_cast <MEmplaceBuilding*> (message);
			switch (m_building->getAction())
			{
				case BuildingMessage::START_BUILDING:
					changeState(State::BUILDING);
					//std::cout << "MEmplaceBuilding \n";
					break;
				case BuildingMessage::FINISH_BUILDING:
				case BuildingMessage::CANCEL_BUILDING:
					changeState(State::PLAYER_SELECTED);
					break;
			}

		}
		else if (!message->getType().compare("MControlRaycast"))
		{
			MControlRaycast *m_raycast = static_cast <MControlRaycast*> (message);
			if (_raycastStart){
				_raycastStart = false;
				switch (m_raycast->getAction())
				{
				case RaycastMessage::HIT_RAYCAST:
					{	
						
						//Parar el raycast
						MControlRaycast *rc_message = new MControlRaycast();
						rc_message->setAction(RaycastMessage::STOP_RAYCAST);
						_entity->emitMessage(rc_message, this);

						//Comprobar si la entidad es seleccionable
						CEntity *col_entity = m_raycast->getCollisionEntity();
						
						MIsSelectable* message = new MIsSelectable();
						message->setPoint(m_raycast->getCollisionPoint());
						col_entity->emitMessage(message);

						//std::cout << "CONTROL_RAYCAST" << "\n";

						break;
					}
				}
			}

		} else if (!message->getType().compare("MEntitySelected"))
		{
				MEntitySelected *m_selection = static_cast <MEntitySelected*> (message);
				//Enviar un mensaje al estado correspondiente

				//std::cout << "click al estado: " << _activeState;
				//Si el mensaje ha sido enviado desde la interfaz, asignamos
				//a la variable _button el valor TMouseAction::LEFT_CLICK, para que el estado
				//sepa que hacer
				if (m_selection->getInterface())
					_button = TMouseAction::LEFT_CLICK;

				_activeState->click(m_selection->getSelectedEntity(), m_selection->getPoint(),_button);
				//std::cout << "ENTITY_SELECTED" << "\n";


		} else if (!message->getType().compare("MActivateSkill"))
		{
			MActivateSkill *m_skill = static_cast <MActivateSkill*> (message);
			_skill = m_skill->getSkill();
			switch (_skill)
			{
				case TSkill::CURE:
					changeState(State::HEALING);
					break;
			}

		} else if (!message->getType().compare("MLanzarGranada"))
		{
			MLanzarGranada *m_lanzarGranada = static_cast <MLanzarGranada*> (message);
			changeState(State::LANZANDO_GRANADA);
		}
		
		message->removePtr();
	} // process


	//---------------------------------------------------------

	void CSelectionController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

	//---------------------------------------------------------

	void CSelectionController::changeState(int state){
		if ((state > -1 ) && ( state < this->_numStates ))
			_activeState = _godStates[state];
	}

	//---------------------------------------------------------

	void CSelectionController::sendAttackMsg(CEntity* entity, bool attack){

		MAttackEntity *m = new MAttackEntity();
		if (attack)
		{
			m->setEntity(entity);
			m->setAttack(true);
		}
		else
			m->setAttack(false);
		_selectedEntity->emitMessage(m);

	}

	//---------------------------------------------------------

	void CSelectionController::sendHealerMsg(CEntity* entity, bool heal){

		MCureEntity *m = new MCureEntity();
		if (heal)
		{
			m->setEntity(entity);
			m->setCure(true);
		}
		else
			m->setCure(false);
		_selectedEntity->emitMessage(m);

	}

	//---------------------------------------------------------

	void CSelectionController::moveAStar(CEntity* entity, Vector3 point){

		MAStarRoute *m_movement = new MAStarRoute();
		m_movement->setAction(RouteAction::START_ROUTE);
		m_movement->setRouteDestination(point);
		_selectedEntity->emitMessage(m_movement, NULL);

	}

	void CSelectionController::processEntity( Vector3 colPoint, CEntity* colEntity )
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
				if (!_selectedEntity->getName().compare("Amor") && _skill)
				{
					// Enviamos una orden de curación al jugador.
					MAttackEntity *m = new MAttackEntity();
					m->setEntity(colEntity);
					m->setAttack(true);
					_selectedEntity->emitMessage(m, this);
				}
			
			// Realizar acciones sobre el suelo
			} else if (!colEntity->getType().compare("World"))
			{
				_skill = false;

				// Dejamos de atacar o curar y nos movemos.
				MAttackEntity *m = new MAttackEntity();
				m->setAttack(false);
				_selectedEntity->emitMessage(m, this);

				MAStarRoute *m_movement = new MAStarRoute();
				m_movement->setAction(RouteAction::START_ROUTE);
				m_movement->setRouteDestination(colPoint);
				_selectedEntity->emitMessage(m_movement, this);
				/*MMoveSteering *m_steering = new MMoveSteering();
				m_steering->setMovementType(AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);
				m_steering->setTarget(colPoint);
				_selectedEntity->emitMessage(m_steering, this);*/

			// Realizar acciones sobre un enemigo
			} else if (!colEntity->getType().compare("Enemy"))
			{
				_skill = false;
				if (!_selectedEntity->getType().compare("Player"))
				{
					// Enviamos una orden de ataque al enemigo
					MAttackEntity *m = new MAttackEntity();
					m->setEntity(colEntity);
					m->setAttack(true);
					_selectedEntity->emitMessage(m, this);
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
		_skill = false;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		rc_message->setCollisionGroups(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER);
		_entity->emitMessage(rc_message, this);

	} // startSelection

	//---------------------------------------------------------

	void CSelectionController::startAction()
	{
		_isWaitingForAction = true;

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		rc_message->setCollisionGroups(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER);
		_entity->emitMessage(rc_message, this);

	} // startAction

	void CSelectionController::saveSelectedEntity( CEntity* selectedEntity )
	{
		//Enviar mensaje a la entidad para que se deseleccione
		if (_selectedEntity != NULL){
			MEntitySelected *m_selected = new MEntitySelected();
			_selectedEntity->emitMessage(m_selected);
		}

		_selectedEntity = selectedEntity;

		//Mandamos un mensaje a la camara para que se centre en el jugador
		MUbicarCamara *m_ubicar = new MUbicarCamara();
		m_ubicar->setEntity(_selectedEntity);
		_entity->emitMessage(m_ubicar, this);

	} // saveSelectedEntity

	CEntity* CSelectionController::getSelectedEntity()
	{
		return _selectedEntity;

	} // SelectedEntity

	void CSelectionController::changeSelectedEntity(CEntity* entity){
		//Enviar mensaje a la entidad para que se deseleccione
		if (_selectedEntity != NULL)
		{
			MEntitySelected *m_selected = new MEntitySelected();
			_selectedEntity->emitMessage(m_selected);
		}

		_selectedEntity = entity;

		//Enviamos mensaje a la entidad para que se seleccione
		MEntitySelected *m_selected = new MEntitySelected();
		m_selected->setSelectedEntity(entity);
		_selectedEntity->emitMessage(m_selected);


		//Cargamos la interfaz correspondiente a la interfaz seleccionada
		if (!_selectedEntity->getName().compare("Jack"))
			GUI::CServer::getSingletonPtr()->getInterfazController()->menuJugador1();
		else if (!_selectedEntity->getName().compare("Erick"))
			GUI::CServer::getSingletonPtr()->getInterfazController()->menuJugador2();
		else if (!_selectedEntity->getName().compare("Amor"))
			GUI::CServer::getSingletonPtr()->getInterfazController()->menuJugador3();
		else
			assert(!"De momento solo se puede seleccionar una de esas 3 entidades");

		//Mandamos un mensaje a la camara para que se centre en el jugador
		MUbicarCamara *m_ubicar = new MUbicarCamara();
		m_ubicar->setEntity(_selectedEntity);
		_entity->emitMessage(m_ubicar, this);

	}
	
	

} // namespace Logic
