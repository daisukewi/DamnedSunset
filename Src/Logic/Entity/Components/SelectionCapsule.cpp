/**
@file SelectionCapsule.cpp

Contiene la implementación del componente encargado de la representación de la capsula de selección
 
@see Logic::CPhysicEntity
@see Logic::IComponent
@see Logic::CSelectionCapsule

@author Luis Mendoza
@date Febrero, 2012
*/

#include "SelectionCapsule.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Physics/Server.h"
#include "Physics/PhysicModelSimple.h"
#include "Physics/IPhysicObj.h"
#include "PhysicCharacter.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/SetTransform.h"

#include "ScriptManager/Server.h"

#include "BaseSubsystems/Math.h"

#include <sstream>

using namespace Physics;

namespace Logic
{
	IMP_FACTORY(CSelectionCapsule);

	
	CSelectionCapsule::CSelectionCapsule() : CTriggerEntity()
	{

	}

		

	//---------------------------------------------------------

	bool CSelectionCapsule::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		// Invocar al método de la clase padre
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_triggerFunction = false;

		// Crear el objeto físico asociado al componente
		_physicObj = createTriggerEntity(entityInfo);

		_setPosition = false;
		return (_physicObj != NULL);
	} 

	//---------------------------------------------------------

	TPhysicMode CSelectionCapsule::getTriggerMode(const Map::CEntity *entityInfo) 
	{
		std::string type = entityInfo->getStringAttribute("selection_type");
		assert(((type == STR_TRIGGER_STATIC) || (type == STR_TRIGGER_DYNAMIC) || (type == STR_TRIGGER_KINEMATIC)) &&
				"Trigger type no permitido");

		if (type == STR_TRIGGER_STATIC) {
			return PM_STATIC;
		} else if (type == STR_TRIGGER_DYNAMIC) {
			return PM_DYNAMIC;
		} else {
			return PM_KINEMATIC;
		} 
	}

	//---------------------------------------------------------

	CPhysicModelSimple* CSelectionCapsule::createTriggerModel(const Map::CEntity *entityInfo)
	{
		// Creamos el modelo físico correspondiente
		CPhysicModelSimple *model = _physicServer->createModelSimple();

		// Creamos el volumen de colisión adecuado
		createTriggerShape(entityInfo, model, 1.0f);

		// Comprobamos si estamos definiendo un trigger
		if (entityInfo->hasAttribute("selection_trigger") && 
			entityInfo->getBoolAttribute("selection_trigger")) {
			
				// Marcamos el volumen de colisión como trigger
				_physicServer->setTrigger(model, 0, true);
				
				// Las entidades físicas dinámicas y kinemáticas deben tener al menos un
				// volumen de colisión que no sea un trigger. Intuitivamente este volumen
				// de colisión es el que contiene la masa de la entidad.
				// 
				// En este juego usaremos el grupo de colisión 0 para los triggers kinemáticos.
				// Para que todo funcione correctamente debemos configurar los character controller
				// para que no choquen contra el grupo 0 (método move). Además desactivamos las
				// colisiones de otros grupos contra el 0 al crear la escena.
				std::string type = entityInfo->getStringAttribute("selection_type");
				if ((type == STR_TRIGGER_DYNAMIC) || (type == STR_TRIGGER_KINEMATIC)) {
					createTriggerShape(entityInfo, model, 1.0f);
				}
				
		}

		// Devolvemos el modelo resultante
		return model;
	}

	//---------------------------------------------------------

	void CSelectionCapsule::createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale)
	{
		// Leemos el grupo de colisión al que debe pertenecer la shape
		int group = 0;
		if (entityInfo->hasAttribute("selection_collision_group")) {
			group = entityInfo->getIntAttribute("selection_collision_group");
		}
	
		// Crear el volumen de colisión adecuado
		const std::string shape = entityInfo->getStringAttribute("selection_shape");
		assert(((shape == STR_TRIGGER_CAPSULE) || (shape == STR_TRIGGER_PLANE) || (shape == STR_TRIGGER_BOX) 
			|| (shape == STR_TRIGGER_SPHERE)) && "Tipo de shape no permitida en un objeto físico simple");

		// Usar una capsula?
		if (shape == STR_TRIGGER_CAPSULE) {
			float radius = entityInfo->getFloatAttribute("selection_radius");
			float height = entityInfo->getFloatAttribute("selection_height");
			_physicServer->createCapsuleShape(model, radius * scale, height * scale, group);

		// Usar un plano?
		} else if (shape == STR_TRIGGER_PLANE) {
			Vector3 normal = entityInfo->getVector3Attribute("selection_normal");
			_physicServer->createPlaneShape(model, normal, group);

		// Usar una esfera?
		} else if (shape == STR_TRIGGER_SPHERE) {
			float radius = entityInfo->getFloatAttribute("selection_radius");
			_physicServer->createSphereShape(model, radius * scale, group);
	
		// Usar una caja?
		} else if (shape == STR_TRIGGER_BOX) {
			Vector2 dimensions2D = entityInfo->getVector2Attribute("selection_dimension");
			int gridSize = _entity->getMap()->getGridMap()->getGridSize();
			// HACK: pongo la altrua a mano porque no nos interesa que sea configurable.
			// Vamos a querer que todas las entidades tengan la misma altura (muy alta) para que no haya problemas con el A*.
			Ogre::Vector3 dimensions3D = Ogre::Vector3(dimensions2D.y * (gridSize / 2), 15, dimensions2D.x * (gridSize / 2));

			_physicServer->createBoxShape(model, dimensions3D * scale, group);

		} 
	}

	//---------------------------------------------------------

} // namespace Logic