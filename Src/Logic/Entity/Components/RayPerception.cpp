/**
@file RayPerception.cpp

Contiene la implementación del componente que controla la percepción de la entidad usando rayos.
 
@see Logic::CLRayPerception
@see Logic::IComponent

@author Antonio A. Sánchez Ruiz-Granados
@date Noviembre, 2011
*/

#include "RayPerception.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"
#include "Physics/Server.h"
#include "BaseSubsystems/Math.h"

using namespace Logic;

IMP_FACTORY(CRayPerception);
	
//---------------------------------------------------------

bool CRayPerception::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
{
	if(!IComponent::spawn(entity,map,entityInfo))
		return false;

	// distancia a la que se perciben las entidades
	if(entityInfo->hasAttribute("perception_distance"))
		_distance = entityInfo->getFloatAttribute("perception_distance");

	return true;

} // spawn
	
//---------------------------------------------------------

void CRayPerception::tick(unsigned int msecs)
{
	// Obtener la posición y orientación de la entidad
	Vector3 dir = Math::getDirection(_entity->getTransform());
	Vector3 origin = _entity->getPosition();

	// Crear un rayo
	Ray ray(origin, dir);
	
	// Comprobar si el rayo colisiona con alguna entidad
	CEntity *entity = Physics::CServer::getSingletonPtr()->raycastClosest(ray, _distance);
	if (entity) {
		std::cout << entity->getName() << " percibida" << std::endl;
	}

	// Nota: si este componente se añade al jugador funciona correctamente porque
	// el jugador se representa como una capsula y el rayo se lanza a la altura del
	// suelo. Si el rayo se lanza desde más arriba comenzaría dentro de la cápsula
	// y por tanto siempre chocaría contra la propia capsula del jugador.
}

//---------------------------------------------------------



