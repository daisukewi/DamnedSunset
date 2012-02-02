/**
@file EnemyController.cpp

Contiene la implementación del componente que controla el movimiento 
del enemigo.
 
@see Logic::CEnemyController
@see Logic::IComponent

@author Luis Mendoza
@date Enero, 2012
*/

#include "EnemyController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

// Includes para pruebas de paso de mensajes a componentes de IA
#include "AI/Server.h"
#include "AI/Movement.h"

#include "Logic/Entity/Messages/MoveSteering.h"


namespace Logic
{
	IMP_FACTORY(CEnemyController);
	
	//---------------------------------------------------------

	bool CEnemyController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if(entityInfo->hasAttribute("position"))
			_destino = entityInfo->getFloatAttribute("position");

		_moving = false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemyController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CEnemyController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemyController::accept(IMessage *message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CEnemyController::process(IMessage *message)
	{

	} // process
	
	//---------------------------------------------------------

	void CEnemyController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		// Si no se está moviendo calculamos un nuevo punto de destino y llevamos al enemigo para allá.
		// Cuando la distancia al objetivo es pequeña volvemos a hacer el mismo proceso.
		if (!_moving)
		{
			_destino.x = rand() % 200 - 100;
			_destino.y = 5.0f;
			_destino.z = rand() % 200 - 100;

			// Orientamos la entidad hacia el punto de destino
			_entity->setYaw(atan((_destino.x - _entity->getPosition().x) / (_destino.z - _entity->getPosition().z)));

			MMoveSteering *m = new MMoveSteering();

			m->setMovementType(AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
			m->setTarget(_destino);

			_entity->emitMessage(m, this);
		}

		_moving = (_entity->getPosition() - _destino).length() >= 15;

	} // tick

} // namespace Logic

