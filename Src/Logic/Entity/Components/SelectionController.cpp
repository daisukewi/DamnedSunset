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

#include "Logic/Entity/Messages/MouseMove.h"
#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Messages/EntitySelected.h"
#include "Logic/Entity/Messages/IsSelectable.h"
#include "Logic/Entity/Messages/IsActuable.h"
#include "Logic/Entity/Messages/KeyboardEvent.h"

#include "BaseSubsystems/Server.h"

#include "ScriptManager/Server.h"

#include "Physics/Server.h"
#include "GUI/Server.h"
#include "Graphics/Server.h"

//#include "Graphics/f.h"


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

		std::stringstream script;
		script << "god = {} ";
		script << "god.playersSelected = {}";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

		if (entityInfo->hasAttribute("initState"))
		{
			std::stringstream godScript;
			godScript << "god.state = " << entityInfo->getIntAttribute("initState");
			ScriptManager::CServer::getSingletonPtr()->executeScript(godScript.str().c_str());
		}
		else
		{
			std::stringstream godScript;
			godScript << "god.state = 1";
			ScriptManager::CServer::getSingletonPtr()->executeScript(godScript.str().c_str());
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSelectionController::activate()
	{
		//Obtener los IDs de los personajes
		_player1 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack");
		_player2 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick");
		_player3 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Norah");
		_multiSelection = false;
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
			MKeyboardEvent* m = static_cast <MKeyboardEvent*> (message);	
			processKeyboardEvent(m->getKey());
		}
		else if (!message->getType().compare("MMouseEvent"))
		{
			MMouseEvent *m_mouse = static_cast <MMouseEvent*> (message);

			switch (m_mouse->getAction())
			{
			case TMouseAction::LEFT_CLICK:
				_mousePositionReleased = m_mouse->getRelPosition();
				prepareMultipleSelectionClick();
				_multiSelection = false;
				//prepareSelectionClick();
				break;
			case TMouseAction::MIDDLE_CLICK:
				//No action
				break;
			case TMouseAction::RIGHT_CLICK:
				prepareActionClick();
				break;

			case TMouseAction::LEFT_PRESSED:
				//Controlar la selección múltiple
				
				_mousePositionPressed = m_mouse->getRelPosition();
				_multiSelection = true;
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

		_currentExeFrames++;

		// Ejecuto el selection controller de LUA si toca.
		if (_currentExeFrames >= _exeFrames)
		{
			// Reinicio el contador de frames.
			_currentExeFrames = 0;

			// LLamo al tick del selection controller en LUA.
			std::stringstream script;
			script << "godActionParameters = { deltaTime = " << _godDeltaTime << " } ";
			script	<< "godAction()";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			_godDeltaTime = 0;
		}
		else
		{
			_godDeltaTime += msecs;
		}


		////Si se está haciendo multiselección mandar dibujar a LUA el cuadrado de selección
		//if (_multiSelection){
		//	//Obtener las posición actual del ratón
		//	Vector2 mousePosition = GUI::CServer::getSingletonPtr()->getMouseRelPos();

		//	//Cambiar de posición relativa a absoluta de las posiciones del ratón y el cuadrado de selección

		//	//Punto 1 del cuadrado de selección
		//	Vector2 aux1 //GUI::CServer::getSingletonPtr()->positionRelToAbs(_mousePositionPressed);
		//	
		//	//Punto 2 del cuadrado de selección
		//	Vector2 point2;
		//	point2.x = _mousePositionPressed.x;
		//	point2.y = mousePosition.y;
		//	Vector2 aux2 = GUI::CServer::getSingletonPtr()->positionRelToAbs(point2);

		//	//Punto 3 del cuadrado de selección
		//	Vector2 aux3 = GUI::CServer::getSingletonPtr()->positionRelToAbs(mousePosition);
		//	
		//	//Punto 4 del cuadrado de selección
		//	Vector2 point4;
		//	point4.x = mousePosition.x;
		//	point4.y = _mousePositionPressed.y;
		//	Vector2 aux4 = GUI::CServer::getSingletonPtr()->positionRelToAbs(point4);

		//	
		//
		//	
		//	
		//	std::stringstream procSelec;

		//	procSelec << "drawSquare("<< aux1.x  << "," << aux1.y << ","<<   
		//								 aux2.x  << "," << aux2.y << ","<< 
		//								 aux3.x  << "," << aux3.y << ","<<
		//								 aux4.x  << "," << aux4.y << ","<<")";

		//	ScriptManager::CServer::getSingletonPtr()->executeScript(procSelec.str().c_str());

		//}
		float aux = 1.0;
		if (_multiSelection){
			Graphics::CServer::getSingletonPtr()->createSquare(aux,aux,aux,aux);
		}

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

		//Para tener más precisión en la selección se van a lanzar 5 raycast por cada click. El primero de ellos se lanza desde la posición del ratón.
		//Los demás tendrán un desplazamiento hacia la izquierda, derecha, arriba y abajo.
		/*
		6 4 7
		2 1 3
		8 5 9
		*/
		//Los raycast de las diagonales solo se lanzan sy los demás no han acertado.
		//De esta forma no hace falta hacer click exactamente donde se encuentra la entidad a seleccionar
		/*Vector3 point1;
		Vector3 point2;
		Vector3 point3;
		Vector3 point4;
		Vector3 point5;

		CEntity* targetedEntity1 = Logic::CServer::getSingletonPtr()->raycastFromViewport(_mousePositionReleased,&point1, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
	
		CEntity* targetedEntity2 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x-0.015,_mousePositionReleased.y),&point2, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
		CEntity* targetedEntity3 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x+0.015,_mousePositionReleased.y),&point3, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
		CEntity* targetedEntity4 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x,_mousePositionReleased.y-0.015),&point4, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
		CEntity* targetedEntity5 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x,_mousePositionReleased.y+0.015),&point5, Physics::PG_CHARACTERS | Physics::PG_BUILDING);

		CEntity* auxEntity = checkClick(targetedEntity1,targetedEntity2,targetedEntity3,targetedEntity4,targetedEntity5);
		
		if (auxEntity == NULL)
		{
			//Lanzar raycast de las diagonales
			CEntity* targetedEntity6 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x-0.015,_mousePositionReleased.y-0.015),&point1, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
	
			CEntity* targetedEntity7 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x+0.015,_mousePositionReleased.y-0.015),&point2, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
			CEntity* targetedEntity8 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x-0.015,_mousePositionReleased.y+0.015),&point3, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
			CEntity* targetedEntity9 = Logic::CServer::getSingletonPtr()->raycastFromViewport(Vector2(_mousePositionReleased.x+0.015,_mousePositionReleased.y+0.015),&point4, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
		
			auxEntity = checkClick(targetedEntity6,targetedEntity7,targetedEntity8,targetedEntity9,NULL);
			
			if (auxEntity == NULL){
				processSelectionClick();
				return;
			}
		}

		_targetEntityID = auxEntity->getEntityID();
		_waitingForSelectable = true;

		// Send a message to the entity hit to ensure its selectability
		MIsSelectable* m_selectable = new MIsSelectable();
		m_selectable->setMessageType(SELECTION_REQUEST);
		m_selectable->setSenderEntity(_entity);
		// Send the message as instant. The response must be send instantly as well.
		auxEntity->emitInstantMessage(m_selectable, this);

		_waitingForSelectable = false;*/

		Vector3 point1;

		CEntity *auxEntity = Logic::CServer::getSingletonPtr()->raycastFromViewport(_mousePositionReleased,&point1, Physics::PG_CHARACTERS | Physics::PG_BUILDING);
			
		if (auxEntity == NULL){
			processSelectionClick();
			return;
		}
		

		_targetEntityID = auxEntity->getEntityID();
		_waitingForSelectable = true;

		// Send a message to the entity hit to ensure its selectability
		MIsSelectable* m_selectable = new MIsSelectable();
		m_selectable->setMessageType(SELECTION_REQUEST);
		m_selectable->setSenderEntity(_entity);
		// Send the message as instant. The response must be send instantly as well.
		auxEntity->emitInstantMessage(m_selectable, this);

		_waitingForSelectable = false;


	} // prepareSelectionClick

	//---------------------------------------------------------
	
	CEntity* CSelectionController::checkClick(CEntity *entity1, CEntity* entity2, CEntity* entity3, CEntity* entity4, CEntity* entity5)
	{
		if (entity1 == NULL)
		{
			if (entity2 == NULL)
			{
				if (entity3 == NULL)
				{
					if (entity4 == NULL)
					{
						if(entity5 == NULL){
							return NULL;
						}
						else{
							return entity5;
						}
					}else{
						return entity4;
					}
				}else{
					return entity3;
				}

			}else{
				return entity2;
			}
		}else{
			return entity1;
		}
		
		return NULL;
	}

	//---------------------------------------------------------

	void CSelectionController::prepareMultipleSelectionClick(){
		
		//Obtener los 4 puntos en pantalla del cuadrado de selección
		//Los puntos 1 y 3 son _mousePositionPressed y mousePositionReleased


		//Si la posición del ratón ha variado poco, realizar una selección simple
		float difX = _mousePositionReleased.x - _mousePositionPressed.x;
		float difY = _mousePositionReleased.y - _mousePositionPressed.y;
		if ((std::abs(difY) + std::abs(difX)) < 0.025) {
			prepareSelectionClick();
		}else{
			Vector2 point2;
			point2.x = _mousePositionPressed.x;
			point2.y = _mousePositionReleased.y;
		
			Vector2 point4;
			point4.x = _mousePositionReleased.x;
			point4.y = _mousePositionPressed.y;
		
			_targetEntityID = -1;
			_waitingForSelectable = false;
			_worldCollisionPoint = Vector3(0, -1, 0);

			//Pasar las coordenadas en pantalla a las coordenadas de mundo
			Vector3 worldCollisionPoint1 = Vector3(0,-1,0);
			Vector3 worldCollisionPoint2 = Vector3(0,-1,0);
			Vector3 worldCollisionPoint3 = Vector3(0,-1,0);
			Vector3 worldCollisionPoint4 = Vector3(0,-1,0);

			Logic::CServer::getSingletonPtr()->raycastFromViewport(_mousePositionPressed,&worldCollisionPoint1, Physics::PG_WORLD);
			Logic::CServer::getSingletonPtr()->raycastFromViewport(point2,&worldCollisionPoint2, Physics::PG_WORLD);
			Logic::CServer::getSingletonPtr()->raycastFromViewport(_mousePositionReleased,&worldCollisionPoint3, Physics::PG_WORLD);
			Logic::CServer::getSingletonPtr()->raycastFromViewport(point4,&worldCollisionPoint4, Physics::PG_WORLD);

			//Obtener las posiciones de los personajes y del mapa en 2D, x y z
			Vector2 player1Pos = Vector2(_player1->getPosition().x,_player1->getPosition().z);
			Vector2 player2Pos = Vector2(_player2->getPosition().x,_player2->getPosition().z);
			Vector2 player3Pos = Vector2(_player3->getPosition().x,_player3->getPosition().z);

			Vector2 worldPoint1 = Vector2(worldCollisionPoint1.x, worldCollisionPoint1.z);
			Vector2 worldPoint2 = Vector2(worldCollisionPoint2.x, worldCollisionPoint2.z);
			Vector2 worldPoint3 = Vector2(worldCollisionPoint3.x, worldCollisionPoint3.z);
			Vector2 worldPoint4 = Vector2(worldCollisionPoint4.x, worldCollisionPoint4.z);

			//Comprobar si los personajes están dentro del área seleccionada
			processMultipleSelection(Math::isInsideRectangle(worldPoint1,worldPoint2,worldPoint3,worldPoint4,player1Pos),
									Math::isInsideRectangle(worldPoint1,worldPoint2,worldPoint3,worldPoint4,player2Pos),
									Math::isInsideRectangle(worldPoint1,worldPoint2,worldPoint3,worldPoint4,player3Pos));

			
			std::string aux = "GodSelected";
			int ID = ScriptManager::CServer::getSingletonPtr()->getGlobal(aux.c_str(),-2);
			if (ID >= 0){
				_targetEntityID = ID;
				_waitingForSelectable = true;

				// No hace falta enviar mensaje, ya se sabe que es selectable porque es un personaje
				// Send a message to the entity hit to ensure its selectability
				//MIsSelectable* m_selectable = new MIsSelectable();
				//m_selectable->setMessageType(SELECTION_REQUEST);
				//m_selectable->setSenderEntity(_entity);
				// Send the message as instant. The response must be send instantly as well.
				//Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_targetEntityID)->emitInstantMessage(m_selectable, this);

				_waitingForSelectable = false;
			}
		}

		
	
	}

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
		procSelec << "selectionParameters = { target = " << _targetEntityID << ", point_x = " << _worldCollisionPoint.x << ", point_y = " << _worldCollisionPoint.y << ", point_z = " << _worldCollisionPoint.z << " } ";
		procSelec << "godEvent(\"OnSelectionClick\")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(procSelec.str().c_str());

	} // processSelectionClick

	//---------------------------------------------------------

	void CSelectionController::processActionClick()
	{
		_waitingForActuable = false;

		// Send a message with the Action petition, the world mouse richt-click point, and the entity.
		std::stringstream procAction;
		procAction << "actionParameters = { target = " << _targetEntityID << ", point_x = " << _worldCollisionPoint.x << ", point_y = " << _worldCollisionPoint.y << ", point_z = " << _worldCollisionPoint.z << " } ";
		procAction << "godEvent(\"OnActionClick\")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(procAction.str().c_str());

	} // processActionClick

	//---------------------------------------------------------

	void CSelectionController::processMultipleSelection(bool player1inside, bool player2inside, bool player3inside)
	{
		_waitingForSelectable = false;

		int id1 = player1inside?_player1->getEntityID():-1; 
		int id2 = player2inside?_player2->getEntityID():-1; 
		int id3 = player3inside?_player3->getEntityID():-1;

		std::stringstream procSelec;
		procSelec << "multiSelectionParameters = { player1 = " << id1 << ", player2 = " << id2 << ", player3 = " << id3 << " } ";
		procSelec << "godEvent(\"OnMultiSelectionClick\")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(procSelec.str().c_str());

	} // processMultipleSelecion

	//---------------------------------------------------------

	void CSelectionController::processKeyboardEvent(GUI::Key::TKeyID key){
		std::string aux;
		std::stringstream procKey;
		if (GUI::Key::TKeyID::TAB){
			aux = "TAB";
		}
		procKey << "processKeyboardEvent(\"" << aux <<"\")" ;
		ScriptManager::CServer::getSingletonPtr()->executeScript(procKey.str().c_str());
	} //processKeyboardEvent

	//---------------------------------------------------------

} // namespace Logic
