/**
@file SunController.cpp

Contiene la implementación del componente que controla el movimiento 
del sol y el control del la luz ambiental.
 
@see Logic::CSunController
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


namespace Logic 
{
	IMP_FACTORY(CBuilderController);

	const int GRID_SIZE = 5;
	const int MAP_SIZE = 100;
	
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

	bool CBuilderController::accept(const TMessage &message)
	{
		return message._type == Message::BUILD_START
			|| message._type == Message::BUILD_MOVE
			|| message._type == Message::BUILD_EMPLACE;

	} // accept
	
	//---------------------------------------------------------

	void CBuilderController::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::BUILD_START:
			if (_building) return;
			startBuilding(message._string);
			break;
		case Message::BUILD_MOVE:
			if (!_building) return;
			moveBuilding(message._vector2);
			break;
		case Message::BUILD_EMPLACE:
			if (!_building) return;
			emplaceBuilding();
			break;
		}
		
	} // process
	
	//---------------------------------------------------------

	void CBuilderController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
	} // tick

	void CBuilderController::startBuilding( std::string buildingType )
	{
		_building = true;

		Map::CEntity *buildInfo = new Map::CEntity("Base");
		buildInfo->setType("Entity");
		buildInfo->setAttribute("position", "{0,0,0}");
		buildInfo->setAttribute("orientation", "0");
		buildInfo->setAttribute("model", "torreta_pie.mesh");

		_buildingEntity = Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		if (!_buildingEntity)
		{
			_building = false;
		}

	}

	void CBuilderController::emplaceBuilding()
	{
		Vector3 pos = _buildingEntity->getPosition();
		std::stringstream vecPos;
		vecPos << "{" << pos.x << "," << pos.y << "," << pos.z << "}";

		// Borrar la entidad sin física
		Logic::CEntityFactory::getSingletonPtr()->deleteEntity(_buildingEntity);

		// Creamos una nueva entidad pero con física.
		/*Map::CEntity *buildInfo = new Map::CEntity("Base");
		buildInfo->setType("Entity");
		buildInfo->setAttribute("position", vecPos.str());
		buildInfo->setAttribute("orientation", "0");
		buildInfo->setAttribute("model", "torreta_pie.mesh");
			/*
			type = "Building",
			position = {10, 0, 0},
			orientation = 0,
			model = "torreta_pie.mesh",
			physic_entity = "simple",
			physic_type = "static",
			physic_shape = "box",
			physic_dimensions = { 2.3, 2.5, 2.3 },
			physic_height = 2,
			physic_radius = 10,
			physic_collision_group = 2,
			*/

		//Logic::CEntityFactory::getSingletonPtr()->createEntity(buildInfo, _entity->getMap());

		_building = false;
	}

	void CBuilderController::moveBuilding( Vector2 pos )
	{
		if (!_buildingEntity) return;

		Vector3 *point = new Vector3();

		//Lanzar un rayo desde la camara hasta el plano del escenario.
		Ray mouseRay = Graphics::CServer::getSingletonPtr()->getCameraToViewportRay(pos.x, pos.y	);
		if (Physics::CServer::getSingletonPtr()->raycastAdvanced(mouseRay, point) == NULL) return;

		_buildingEntity->setPosition(Vector3(point->x, 1.0f, point->z));

	}

} // namespace Logic

