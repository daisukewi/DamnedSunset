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

	bool CBuilderController::accept(const TMessage &message)
	{
		return message._type == Message::BUILD_START
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

		if (!_building) return;


		
	} // tick

	void CBuilderController::startBuilding( std::string _string )
	{
		_building = true;

		Map::CEntity *newBuild = new Map::CEntity("Base");
		newBuild->setAttribute("type", "Entity");
		newBuild->setAttribute("position", "{0,0,0}");
		newBuild->setAttribute("orientation", "0");
		newBuild->setAttribute("model", "torreta_pie.mesh");
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

		_buildingEntity = Logic::CEntityFactory::getSingletonPtr()->createEntity(newBuild, _entity->getMap());

	}

	void CBuilderController::emplaceBuilding()
	{
		_building = false;
	}

} // namespace Logic

