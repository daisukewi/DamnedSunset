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

	} // spawna
	
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
		Map::CEntity * buildInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("PhantomTurret");
		buildInfo->setName("PhantomBuilding");

		Vector2 size = buildInfo->getVector2Attribute("building_size");
		_buildingWidth = size.x;
		_buildingHeight = size.y;

		_buildingEntity = Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		if (!_buildingEntity)
		{
			_building = false;
			return;
		}

		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::START_RAYCAST);
		rc_message->setCollisionGroups(Physics::TPhysicGroup::PG_WORLD);
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
		if (!CheckBuildingCanEmplace()) return;

		Vector3 pos = _buildingEntity->getPosition();
		std::stringstream vecPos, buildingName;
		std::string	buildingType;

		vecPos << pos.x << " 0.0 " << pos.z;
		buildingName << _buildingEntity->getName() << ++_buildingNumber;
		buildingType = _buildingEntity->getType();

		// Borrar la entidad sin física
		Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);

		// Creamos una nueva entidad con su entidad trigger sacada de los arquetipos
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
		Vector2 newPos = _entity->getMap()->getGridMap()->getAbsoluteGridPos(pos);
		_buildingEntity->setPosition(Vector3(newPos.x, 1.0f, newPos.y));

	} // moveBuilding

	//---------------------------------------------------------

	bool CBuilderController::CheckBuildingCanEmplace()
	{
		Vector3 pos = _buildingEntity->getPosition();

		TGridTile current_tile = _entity->getMap()->getGridMap()->getTileFromPosition(pos.x, pos.z);
		int _startRow = current_tile->GetRow() - _buildingHeight / 2;
		int _startCol = current_tile->GetCol() - _buildingWidth / 2;

		int _endRow = _startRow + _buildingHeight;
		int _endCol = _startCol + _buildingWidth;

		bool canEmplace = true;

		for (int row = _startRow; row < _endRow; row ++)
			for (int col = _startCol; col < _endCol; col++)
			{
				//TODO: Comprobar cada casilla y mandar al pixel shader un color para mostrar
				// el edificio en rojo, amarillo o verde.
				canEmplace &= !_entity->getMap()->getGridMap()->getTileFromCoord(row, col)->IsPopulated();
			}

		return canEmplace;

	} // CheckBuildingCanEmplace

} // namespace Logic

