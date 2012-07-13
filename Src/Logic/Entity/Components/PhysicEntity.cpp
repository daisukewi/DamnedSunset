/**
@file PhysicEntity.cpp

Contiene la implementación del componente encargado de la representación física de las
entidades que no son character controllers.
 
@see Logic::CPhysicEntity
@see Logic::IComponent
@see Logic::CPhysicCharacter

@author Antonio Sánchez Ruiz-Granados
@date Octubre, 2010
*/

#include "PhysicEntity.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Physics/Server.h"
#include "Physics/PhysicModelSimple.h"
#include "Physics/PhysicModelGeneric.h"
#include "Physics/IPhysicObj.h"

#include "Logic/Entity/Messages/SetTransform.h"
#include "Logic/Entity/Messages/AplicarVelocidad.h"

using namespace Logic;
using namespace Physics;

IMP_FACTORY(CPhysicEntity);

//---------------------------------------------------------

CPhysicEntity::CPhysicEntity() : IComponent(), _physicObj(NULL) , _forceApplyTransform(false)
{
	_physicServer = CServer::getSingletonPtr();
}

//---------------------------------------------------------

CPhysicEntity::~CPhysicEntity() 
{
	if(_physicObj) {
		// Eliminar el objeto físico de la escena
		_physicServer->destroyObject(_physicObj);
		_physicObj = NULL;
	}
	
	_physicServer = NULL;
} 

//---------------------------------------------------------

bool CPhysicEntity::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
{
	// Invocar al método de la clase padre
	if(!IComponent::spawn(entity,map,entityInfo))
		return false;

	// Crear el objeto físico asociado al componente
	_physicObj = createPhysicEntity(entityInfo);

	// Anotar su posición y rotación actual
	_transform = _entity->getTransform();

	return (_physicObj != NULL);
} 

//---------------------------------------------------------

bool CPhysicEntity::accept(IMessage *message)
{
	return (message->getType().compare("MSetTransform") == 0) || !message->getType().compare("MAplicarVelocidad");
}

//---------------------------------------------------------

void CPhysicEntity::process(IMessage *message)
{
	if (!message->getType().compare("MSetTransform"))
	{
		MSetTransform *m = static_cast <MSetTransform*> (message);

		// Anotamos la transformación para usarla posteriormente en el método 
		// tick. De esa forma, si recibimos varios mensajes en el mismo ciclo 
		// sólo tendremos en cuenta el último
		_transform = m->getTransform();
		_forceApplyTransform = m->getForce();
	} else if (!message->getType().compare("MAplicarVelocidad")) {
		MAplicarVelocidad *m = static_cast <MAplicarVelocidad*> (message);
		_physicObj->SetLinearVelocity(m->getVelocity(), 0);
	}
}

//---------------------------------------------------------

void CPhysicEntity::tick(unsigned int msecs) 
{
	// Invocar al método de la clase padre (IMPORTANTE)
	IComponent::tick(msecs);

	// Si el objeto físico es kinemático intentamos moverlo a la posición
	// recibida en el último mensaje de tipo MSetTransform
	if (_physicObj->IsKinematic()) {
		_physicServer->move(_physicObj, _transform);
	} else {
		if (_forceApplyTransform)
		{
			_forceApplyTransform = false;
			_physicServer->setStaticObjectPosition(_physicObj, _transform.getTrans());
		}
		// Actualizar la posición y la orientación de la entidad lógica usando la 
		// información proporcionada por el motor de física
		_entity->setPosition(_physicServer->getPosition(_physicObj));
		_entity->setOrientation(_physicServer->getOrientation(_physicObj, 0));
	}
}

//---------------------------------------------------------

void CPhysicEntity::onEntityHit(const CEntity *otherEntity) 
{

}

//---------------------------------------------------------

IPhysicObj* CPhysicEntity::createPhysicEntity(const Map::CEntity *entityInfo)
{
	// Obtenemos el modelo físico que describe el tipo de entidad física
	// que debemos crear
	IPhysicModel *model = createPhysicModel(entityInfo);

	// Obtenemos el tipo de entidad física (estática, dinámica, kinemática)
	// particular que queremos crear y su posición en el mundo
	TPhysicMode mode = getPhysicMode(entityInfo);
	Vector3 position = _entity->getPosition();
	Matrix3 orientation = _entity->getOrientation();

	// Creamos la nueva entidad física
	return _physicServer->createObject(this, mode, position, orientation, model); 
}

//---------------------------------------------------------

IPhysicModel* CPhysicEntity::createPhysicModel(const Map::CEntity *entityInfo)
{
	// Obtenemos el tipo de entidad física que debemos crear
	const std::string entity = entityInfo->getStringAttribute(STR_PHYSIC_ENTITY);
	assert((entity == STR_SIMPLE || entity == STR_GENERIC) &&
			"Tipo de entidad no permitida en el componente físico");

	// Creamos el modelo correspondiente
	IPhysicModel *model = NULL;
	if (entity == STR_SIMPLE) {
		model = createPhysicModelSimple(entityInfo);
	} else if (entity == STR_GENERIC) {
		model = createPhysicModelGeneric(entityInfo);
	}

	return model;
}

//---------------------------------------------------------

TPhysicMode CPhysicEntity::getPhysicMode(const Map::CEntity *entityInfo) {
	
	// Los controladores son entidades kinemáticas
	if (entityInfo->getStringAttribute(STR_PHYSIC_ENTITY) == STR_CONTROLLER) {
		return PM_KINEMATIC;
	}
	
	// El resto de entidades definen su tipo explícitamente
	std::string type = entityInfo->getStringAttribute(STR_PHYSIC_TYPE);
	assert(((type == STR_STATIC) || (type == STR_DYNAMIC) || (type == STR_KINEMATIC)) &&
			"Physic type no permitido");

	if (type == STR_STATIC) {
		return PM_STATIC;
	} else if (type == STR_DYNAMIC) {
		return PM_DYNAMIC;
	} else {
		return PM_KINEMATIC;
	} 
}

//---------------------------------------------------------

CPhysicModelSimple* CPhysicEntity::createPhysicModelSimple(const Map::CEntity *entityInfo)
{
	// Comprobamos que estamos creando una entidad física simple
	const std::string entity = entityInfo->getStringAttribute(STR_PHYSIC_ENTITY);
	assert(entity == STR_SIMPLE);

	// Creamos el modelo físico correspondiente
	CPhysicModelSimple *model = _physicServer->createModelSimple();

	// Creamos el volumen de colisión adecuado
	createPhysicShape(entityInfo, model, 1.0f);

	// Si estamos definiendo un objeto dinámico anotamos su masa.
	if (entityInfo->hasAttribute(STR_PHYSIC_MASS)) {
		float mass = entityInfo->getFloatAttribute(STR_PHYSIC_MASS);
		_physicServer->setMass(model, mass);
	}

	// Devolvemos el modelo resultante
	return model;
}

//---------------------------------------------------------

void CPhysicEntity::createPhysicShape(const Map::CEntity *entityInfo, CPhysicModelSimple *model, float scale)
{
	// Leemos el grupo de colisión al que debe pertenecer la shape
	int group = 0;
	if (entityInfo->hasAttribute(STR_PHYSIC_COLLISION_GROUP)) {
		group = entityInfo->getIntAttribute(STR_PHYSIC_COLLISION_GROUP);
	}
	
	// Crear el volumen de colisión adecuado
	const std::string shape = entityInfo->getStringAttribute(STR_PHYSIC_SHAPE);
	assert(((shape == STR_CAPSULE) || (shape == STR_PLANE) || (shape == STR_BOX)) &&
			"Tipo de shape no permitida en un objeto físico simple");

	// Usar una capsula?
	if (shape == STR_CAPSULE) {
		float radius = entityInfo->getFloatAttribute(STR_PHYSIC_RADIUS);
		float height = entityInfo->getFloatAttribute(STR_PHYSIC_HEIGHT);
		_physicServer->createCapsuleShape(model, radius * scale, height * scale, group);

	// Usar un plano?
	} else if (shape == STR_PLANE) {
		Vector3 normal = entityInfo->getVector3Attribute(STR_PHYSIC_NORMAL);
		_physicServer->createPlaneShape(model, normal, group);
	
	// Usar una caja?
	} else if (shape == STR_BOX) {

		// @TODO @HACK Hago esto porque tengo prisa pero en un futuro habría que que hacer algo con el "World".
		if (!_entity->getType().compare("World"))
		{
			Vector3 dimensions = entityInfo->getVector3Attribute(STR_PHYSIC_DIMENSIONS);
			_physicServer->createBoxShape(model, dimensions * scale, group);
		}
		else
		{
			Vector2 dimensions2D = entityInfo->getVector2Attribute("dimension");
			int gridSize = _entity->getMap()->getGridMap()->getGridSize();
			// HACK: pongo la altrua a mano porque no nos interesa que sea configurable.
			// Vamos a querer que todas las entidades tengan la misma altura (muy alta) para que no haya problemas con el A*.
			Ogre::Vector3 dimensions3D = Ogre::Vector3(dimensions2D.y * (gridSize / 2), 50, dimensions2D.x * (gridSize / 2));

			_physicServer->createBoxShape(model, dimensions3D * scale, group);
		}

	} 
}

//---------------------------------------------------------

CPhysicModelGeneric* CPhysicEntity::createPhysicModelGeneric(const Map::CEntity *entityInfo)
{
	// Comprobar que estamos creando una entidad física genérica
	const std::string entity = entityInfo->getStringAttribute(STR_PHYSIC_ENTITY);
	assert(entity == STR_GENERIC);

	// Crear el modelo físico a partir de un fichero
	std::string file = entityInfo->getStringAttribute(STR_PHYSIC_FILE);
	return _physicServer->createModelGeneric(file);
}

//---------------------------------------------------------