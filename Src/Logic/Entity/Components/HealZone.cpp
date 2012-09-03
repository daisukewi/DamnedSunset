#include "HealZone.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"
#include "Logic/Entity/Messages/Healed.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"
#include "Logic/Entity/Messages/ActivateHealZone.h"

namespace Logic 
{
	IMP_FACTORY(CHealZone);
	
	//---------------------------------------------------------

	CHealZone::CHealZone() : IComponent() {

	}

	CHealZone::~CHealZone() {
	}

	bool CHealZone::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("healZoneTime"))
			_healTime = entityInfo->getFloatAttribute("healZoneTime");
		if(entityInfo->hasAttribute("healZoneDistance"))
			_healDistance = entityInfo->getFloatAttribute("healZoneDistance");
		if(entityInfo->hasAttribute("healZoneValue"))
			_healValue = entityInfo->getFloatAttribute("healZoneValue");

		return true;
	} // spawn


	bool CHealZone::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CHealZone::accept(IMessage *message)
	{
		return (!message->getType().compare("MActivateHealZone"));
	} // accept
	
	//---------------------------------------------------------

	void CHealZone::process(IMessage *message)
	{
		
		if (!message->getType().compare("MActivateHealZone")){

			_numEnt = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),_healDistance,_entidades);

			MHealed *message = new MHealed();
			message->setHeal(_healValue);
			message->setHealer(_entity);

			message->addPtr();
			for (int i =0; i < _numEnt; ++i)
			{
				if (!_entidades[i]->getTag().compare("Player") ){
					
					_entidades[i]->emitMessage(message);
					
				}
			}
			message->removePtr();

			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);
		}
		;
	} // process

	void CHealZone::timeElapsed()
	{

		_healTime-=1000;

		if (_healTime > 0){

			_numEnt = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),_healDistance,_entidades);

			MHealed *message = new MHealed();
			message->setHeal(_healValue);
			message->setHealer(_entity);

			message->addPtr();
			for (int i =0; i < _numEnt; ++i)
			{
				if (!_entidades[i]->getTag().compare("Player") ){
					
					_entidades[i]->emitMessage(message);
					
				}
			}
			message->removePtr();
			
			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);
			

		}else{
			
		}
		
		

	} // timeElapsed

} // namespace Logic

