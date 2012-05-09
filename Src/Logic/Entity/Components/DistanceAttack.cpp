/**
@file TurretController.cpp

Contiene la implementaci�n del componente que controla lo que debe hacer una torreta.
 
@see Logic::CTurretController
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/

#include "DistanceAttack.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Physics\Server.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/AttackDistance.h"
#include "Logic/Entity/Messages/SetAnimation.h"
#include "Logic/Entity/Messages/StopAnimation.h"

namespace Logic
{
	IMP_FACTORY(CDistanceAttack);
	
	//---------------------------------------------------------

	bool CDistanceAttack::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("precision")){
			_precision = entityInfo->getFloatAttribute("precision");
			
		}else{
			_precision = 1.0;
		}
		if (entityInfo->hasAttribute("damage")){
			_damage = entityInfo->getIntAttribute("damage");
		}else{
			_damage = 40.0;
		}
		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CDistanceAttack::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CDistanceAttack::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CDistanceAttack::accept(IMessage *message)
	{
		return !message->getType().compare("MAttackDistance") /*|| !message->getType().compare("MAttackEntity")*/;

	} // accept
	
	//---------------------------------------------------------

	void CDistanceAttack::process(IMessage *message)
	{
		if (!message->getType().compare("MAttackDistance")){
		
			MAttackDistance *m = static_cast <MAttackDistance*> (message);
			
			Vector3 origen = _entity->getPosition();
			Vector3 destino = m->getEntity()->getPosition();
			destino.y = 3.0f;
			Vector3 direction = destino - origen;
			//Descomentar para deviar el disparo a distancia de los personajes
			//direction.x *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
			//direction.y *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
			//direction.z *= (_precision + 1) * (1 / ((rand() % 100) + 1) + 1);
		
			direction.normalise();
			Vector3 impact;
			Ray disparo = Ray(origen, direction);
			Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastGroup(disparo, &impact,
				(Physics::TPhysicGroup)(Physics::TPhysicGroup::PG_ALL & ~Physics::TPhysicGroup::PG_TRIGGER));
			if (!entity->getType().compare("Enemy"))
			{
				MDamaged *m_dam = new MDamaged();
				m_dam->setHurt((_damage)); ///Descomentar para reducir el da�o en base a la distancia de los personajes (100.0f * ((_entity->getPosition() - m->getEntity()->getPosition()).length() + 0.1))) * _damage);
				m_dam->setKiller(_entity);
				entity->emitMessage(m_dam, this);
			}
			
		}
		

	} // process
	
	//---------------------------------------------------------

	void CDistanceAttack::tick(unsigned int msecs)
	{

		IComponent::tick(msecs);
	} // tick

	//---------------------------------------------------------

} // namespace Logic
