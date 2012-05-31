/**
@file TriggerEntity.cpp

Contiene la implementación del componente encargado de la representación de los triggers.
 
@see Logic::CPhysicEntity
@see Logic::IComponent
@see Logic::CTriggerEntity

@author Luis Mendoza
@date Febrero, 2012
*/

#include "TriggerEntity.h"

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
	IMP_FACTORY(CTriggerEntity);

	//---------------------------------------------------------

	CTriggerEntity::CTriggerEntity() : IComponent(), _physicObj(NULL),  _offsetY(0), _setPosition(false)
	{
		_physicServer = CServer::getSingletonPtr();
	}

	//---------------------------------------------------------

	CTriggerEntity::~CTriggerEntity() 
	{
		if(_physicObj) {
			// Eliminar el objeto físico de la escena
			_physicServer->destroyObject(_physicObj);
			_physicObj = NULL;
		}
	
		_physicServer = NULL;
	} 

	//---------------------------------------------------------

	bool CTriggerEntity::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		// Invocar al método de la clase padre
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("triggerFunction"))
		{
			_triggerFunction = true;
			_luaTriggerFunction = entityInfo->getStringAttribute("triggerFunction").c_str();
		}
		else
			_triggerFunction = false;

		// Crear el objeto físico asociado al componente
		_physicObj = createTriggerEntity(entityInfo);

		_setPosition = false;
		return (_physicObj != NULL);
	} 

	//---------------------------------------------------------

	bool CTriggerEntity::accept(IMessage *message)
	{
		return (!message->getType().compare("MSetTransform"));
	}

	//---------------------------------------------------------

	void CTriggerEntity::process(IMessage *message)
	{
		if (!message->getType().compare("MSetTransform")){
			_setPosition = true;
			MSetTransform *m = static_cast <MSetTransform*> (message);
			Vector3 aux = m->getTransform().getTrans();
			aux.y -= _offsetY;
			_newPosition = aux;
		}
	}

	//---------------------------------------------------------

	void CTriggerEntity::tick(unsigned int msecs) 
	{
		// Invocar al método de la clase padre
		IComponent::tick(msecs);

		if (_physicObj->IsKinematic())
		{
			if (_setPosition) {
				if (_physicObj){
					_physicServer->move(_physicObj, _newPosition);
				}
				_setPosition = false;
			}
		}
	}

	//---------------------------------------------------------

	void CTriggerEntity::onEntityTrigger(const CEntity *otherEntity, bool enter, bool leave, bool stay)
	{
		// Sólo tenemos en cuenta los eventos de entrada y salida del trigger
		if (stay)
			return;

		// Construimos un mensaje de tipo TOUCHED o UNTOUCHED y lo enviamos a todos los
		// componentes de la entidad. 
		MIsTouched *m = new MIsTouched();
		if (enter)
		{
			m->setTouched(true);
			if (_triggerFunction)
			{
				std::stringstream script;
				script << _luaTriggerFunction << "(" << otherEntity->getEntityID() << ")";
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
			}
		}
		else
		{
			m->setTouched(false);
		}

		m->setEntity(const_cast<CEntity *> (otherEntity));

		_entity->emitMessage(m);
	}

	//---------------------------------------------------------

	IPhysicObj* CTriggerEntity::createTriggerEntity(const Map::CEntity *entityInfo)
	{
		// Obtenemos el modelo físico que describe el tipo de entidad física
		// que debemos crear
		IPhysicModel *model = createTriggerModel(entityInfo);

		// Obtenemos el tipo de entidad física (estática, dinámica, kinemática)
		// particular que queremos crear y su posición en el mundo
		TPhysicMode mode = getTriggerMode(entityInfo);
		Vector3 position = _entity->getPosition();
		Matrix3 orientation = _entity->getOrientation();
		
		// Crear el modelo físico
		float height = entityInfo->getFloatAttribute(STR_PHYSIC_HEIGHT);
		
		// Calculamos el desplazamiento necesario para transformar entre el sistema de 
		// coordenadas local de PhysX, que tiene su origen en el centro de la entidad, 
		// y el de la lógica, que tiene su origen en los pies de la entidad.
		_offsetY = height / 2.0f;
		position.y-= _offsetY;
		// Creamos la nueva entidad física
		return _physicServer->createTrigger(this, mode, position, orientation, model); 
	}

	//---------------------------------------------------------

	TPhysicMode CTriggerEntity::getTriggerMode(const Map::CEntity *entityInfo) 
	{
		std::string type = entityInfo->getStringAttribute(STR_TRIGGER_TYPE);
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

	CPhysicModelSimple* CTriggerEntity::createTriggerModel(const Map::CEntity *entityInfo)
	{
		// Creamos el modelo físico correspondiente
		CPhysicModelSimple *model = _physicServer->createModelSimple();

		// Creamos el volumen de colisión adecuado
		createTriggerShape(entityInfo, model, 1.0f);

		// Comprobamos si estamos definiendo un trigger
		if (entityInfo->hasAttribute(STR_TRIGGER) && 
			entityInfo->getBoolAttribute(STR_TRIGGER)) {
			
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
				std::string type = entityInfo->getStringAttribute(STR_TRIGGER_TYPE);
				if ((type == STR_TRIGGER_DYNAMIC) || (type == STR_TRIGGER_KINEMATIC)) {
					createTriggerShape(entityInfo, model, 1.0f);
				}
				
		}

		// Devolvemos el modelo resultante
		return model;
	}

	//---------------------------------------------------------

	void CTriggerEntity::createTriggerShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale)
	{
		// Leemos el grupo de colisión al que debe pertenecer la shape
		int group = 0;
		if (entityInfo->hasAttribute(STR_TRIGGER_COLLISION_GROUP)) {
			group = entityInfo->getIntAttribute(STR_TRIGGER_COLLISION_GROUP);
		}
	
		// Crear el volumen de colisión adecuado
		const std::string shape = entityInfo->getStringAttribute(STR_TRIGGER_SHAPE);
		assert(((shape == STR_TRIGGER_CAPSULE) || (shape == STR_TRIGGER_PLANE) || (shape == STR_TRIGGER_BOX) 
			|| (shape == STR_TRIGGER_SPHERE)) && "Tipo de shape no permitida en un objeto físico simple");

		// Usar una capsula?
		if (shape == STR_TRIGGER_CAPSULE) {
			float radius = entityInfo->getFloatAttribute(STR_TRIGGER_RADIUS);
			float height = entityInfo->getFloatAttribute(STR_TRIGGER_HEIGHT);
			_physicServer->createCapsuleShape(model, radius * scale, height * scale, group);

		// Usar un plano?
		} else if (shape == STR_TRIGGER_PLANE) {
			Vector3 normal = entityInfo->getVector3Attribute(STR_TRIGGER_NORMAL);
			_physicServer->createPlaneShape(model, normal, group);

		// Usar una esfera?
		} else if (shape == STR_TRIGGER_SPHERE) {
			float radius = entityInfo->getFloatAttribute(STR_TRIGGER_RADIUS);
			_physicServer->createSphereShape(model, radius * scale, group);
	
		// Usar una caja?
		} else if (shape == STR_TRIGGER_BOX) {
			Vector2 dimensions2D = entityInfo->getVector2Attribute("dimension");
			int gridSize = _entity->getMap()->getGridMap()->getGridSize();
			Ogre::Vector3 dimensions3D = Ogre::Vector3(dimensions2D.y * (gridSize / 2), 50, dimensions2D.x * (gridSize / 2));

			_physicServer->createBoxShape(model, dimensions3D * scale, group);

		} 
	}

	//---------------------------------------------------------

} // namespace Logic