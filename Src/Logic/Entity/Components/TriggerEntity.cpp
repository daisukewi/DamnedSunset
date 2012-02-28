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

#include "Logic/Entity/Messages/IsTouched.h"

using namespace Physics;

namespace Logic
{
	IMP_FACTORY(CTriggerEntity);

	//---------------------------------------------------------

	CTriggerEntity::CTriggerEntity() : IComponent(), _physicObj(NULL)
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

		// Crear el objeto físico asociado al componente
		_physicObj = createTriggerEntity(entityInfo);

		return (_physicObj != NULL);
	} 

	//---------------------------------------------------------

	bool CTriggerEntity::accept(IMessage *message)
	{
		return (message->getType().compare("MSetTransform") == 0);
	}

	//---------------------------------------------------------

	void CTriggerEntity::process(IMessage *message)
	{
	
	}

	//---------------------------------------------------------

	void CTriggerEntity::tick(unsigned int msecs) 
	{
		// Invocar al método de la clase padre (IMPORTANTE)
		IComponent::tick(msecs);
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
		TPhysicMode mode = PM_STATIC;
		Vector3 position = _entity->getPosition();
		Matrix3 orientation = _entity->getOrientation();

		// Creamos la nueva entidad física
		return _physicServer->createTrigger(this, mode, position, orientation, model); 
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
				/*
				// Las entidades físicas dinámicas y kinemáticas deben tener al menos un
				// volumen de colisión que no sea un trigger. Intuitivamente este volumen
				// de colisión es el que contiene la masa de la entidad.
				// 
				// En este juego usaremos el grupo de colisión 0 para los triggers kinemáticos.
				// Para que todo funcione correctamente debemos configurar los character controller
				// para que no choquen contra el grupo 0 (método move). Además desactivamos las
				// colisiones de otros grupos contra el 0 al crear la escena.
				std::string type = entityInfo->getStringAttribute(STR_TRIGGER_TYPE);
				if ((type == STR_DYNAMIC) || (type == STR_KINEMATIC)) {
					createTriggerShape(entityInfo, model, 1.0f);
				}
				*/
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
		assert(((shape == STR_TRIGGER_CAPSULE) || (shape == STR_TRIGGER_PLANE) || (shape == STR_TRIGGER_BOX)) &&
				"Tipo de shape no permitida en un objeto físico simple");

		// Usar una capsula?
		if (shape == STR_TRIGGER_CAPSULE) {
			float radius = entityInfo->getFloatAttribute(STR_TRIGGER_RADIUS);
			float height = entityInfo->getFloatAttribute(STR_TRIGGER_HEIGHT);
			_physicServer->createCapsuleShape(model, radius * scale, height * scale, group);

		// Usar un plano?
		} else if (shape == STR_TRIGGER_PLANE) {
			Vector3 normal = entityInfo->getVector3Attribute(STR_TRIGGER_NORMAL);
			_physicServer->createPlaneShape(model, normal, group);
	
		// Usar una caja?
		} else if (shape == STR_TRIGGER_BOX) {
			Vector3 dimensions = entityInfo->getVector3Attribute(STR_TRIGGER_DIMENSIONS);
			_physicServer->createBoxShape(model, dimensions * scale, group);

		} 
	}

	//---------------------------------------------------------

} // namespace Logic