/**
@file BuilderController.cpp

Contiene la implementación del componente que controla el movimiento 
de los edificios sobre el escenario, cuando se van a construir.
 
@see Logic::CBuilderController
@see Logic::IComponent

@author Daniel Flamenco
@date Enero, 2012
*/

#include "BuilderController.h"

#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/EmplaceBuilding.h"
#include "Logic/Entity/Messages/ControlRaycast.h"
#include "Logic/Entity/Messages/MouseEvent.h"


namespace Logic 
{
	IMP_FACTORY(CBuilderController);

	//---------------------------------------------------------

	bool CBuilderController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CBuilderController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CBuilderController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CBuilderController::accept(IMessage *message)
	{
		bool accepted = !message->getType().compare("MEmplaceBuilding")
			|| !message->getType().compare("MControlRaycast")
			|| !message->getType().compare("MMouseEvent");

		if (accepted) message->addPtr();

		return accepted;

	} // accept
	
	//---------------------------------------------------------

	void CBuilderController::process(IMessage *message)
	{
		if (!message->getType().compare("MEmplaceBuilding"))
		{
			MEmplaceBuilding *m_building = static_cast <MEmplaceBuilding*> (message);
			switch (m_building->getAction())
			{
				case BuildingMessage::START_BUILDING:
					startBuilding(m_building->getBuildingType());
					break;
				case BuildingMessage::EMPLACE_BUILDING:
					if (!_building) return;
					emplaceBuilding();
					break;
				case BuildingMessage::CANCEL_BUILDING:
					cancelBuilding();
					break;
			}

		} else if (!message->getType().compare("MControlRaycast"))
		{
			MControlRaycast *m_raycast = static_cast <MControlRaycast*> (message);
			switch (m_raycast->getAction())
			{
				case RaycastMessage::HIT_RAYCAST:
					if (!_building) return;
					Vector3 collPoint = m_raycast->getCollisionPoint();
					moveBuilding(Vector2(collPoint.x, collPoint.z));
					break;
			}

		} else if (!message->getType().compare("MMouseEvent"))
		{
			MMouseEvent *m_mouse = static_cast <MMouseEvent*> (message);

			switch(m_mouse->getAction())
			{
				case TMouseAction::LEFT_CLICK:
					if (!_building) return;
					emplaceBuilding();
					break;
			}
		}

		message->removePtr();

	} // process
	
	//---------------------------------------------------------

	void CBuilderController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
	} // tick

	//---------------------------------------------------------

	void CBuilderController::startBuilding( std::string buildingType )
	{
		if (_building)
		{
			// Borrar la entidad que se estaba construyendo antes
			Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);
		}

		_building = true;

		// Creamos una nueva entidad sacada de los arquetipos
		Map::CEntity * buildInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Entity");
		buildInfo->setName("PhantomBuilding");
		buildInfo->setAttribute("position", "{0,0,0}");
		buildInfo->setAttribute("orientation", "0");
		buildInfo->setAttribute("model", "torreta_pie.mesh");

		_buildingEntity = Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		if (!_buildingEntity)
		{
			_building = false;
			return;
		}

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		_entity->emitMessage(rc_message);

	} //startBuilding

	//---------------------------------------------------------

	void CBuilderController::cancelBuilding()
	{
		if (!_building) return;

		// Borrar la entidad que se estaba construyendo antes
		Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);

		// Mandamos un mensaje para dejar de lanzar raycasts
		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::STOP_RAYCAST);
		_entity->emitMessage(rc_message);

		_building = false;

	} // cancelBuilding

	//---------------------------------------------------------

	void CBuilderController::emplaceBuilding()
	{
		if (!_building || _buildingEntity == NULL) return;

		Vector3 pos = _buildingEntity->getPosition();
		std::stringstream vecPos, buildingName;
		std::string	buildingType;

		vecPos << pos.x << " 0.0 " << pos.z;
		buildingName << _buildingEntity->getName() << ++_buildingNumber;
		buildingType = _buildingEntity->getType();

		// Borrar la entidad sin física
		Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);

		// Creamos una nueva entidad sacada de los arquetipos
		Map::CEntity * buildInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Turret");

		// Le ponemos un nuevo nombre para poder hacer spawn y la posición del edificio fantasma
		buildInfo->setName(buildingName.str());
		buildInfo->setAttribute("position", vecPos.str());
		
		Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		// Mandamos un mensaje para dejar de lanzar raycasts.
		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::STOP_RAYCAST);
		_entity->emitMessage(rc_message);

		MEmplaceBuilding *b_message = new MEmplaceBuilding();
		b_message->setAction(BuildingAction::FINISH_BUILDING);
		_entity->emitMessage(b_message, this);

		_building = false;

	} // emplaceBuilding

	//---------------------------------------------------------

	void CBuilderController::moveBuilding( Vector2 pos )
	{
		if (_buildingEntity == NULL) return;

		// Ponemos la nueva posición del edificio en el centro de la casilla que le corresponda.
		Vector2 newPos = _entity->getMap()->getAbsoluteGridPos(pos);
		_buildingEntity->setPosition(Vector3(newPos.x, 1.0f, newPos.y));

	} // moveBuilding

} // namespace Logic

