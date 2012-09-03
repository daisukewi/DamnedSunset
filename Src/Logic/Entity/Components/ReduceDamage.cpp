#include "ReduceDamage.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

namespace Logic 
{
	IMP_FACTORY(CReduceDamage);
	
	//---------------------------------------------------------

	CReduceDamage::CReduceDamage() : IComponent() {

	}

	CReduceDamage::~CReduceDamage() {
	}

	bool CReduceDamage::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("reduceDamageTime"))
			_reduceTime = entityInfo->getFloatAttribute("reduceDamageTime");
		if(entityInfo->hasAttribute("reduceDamageDistance"))
			_reduceDistance = entityInfo->getFloatAttribute("reduceDamageDistance");
		if(entityInfo->hasAttribute("reduceDamage"))
			_reduceDamage = entityInfo->getFloatAttribute("reduceDamage");

		return true;
	} // spawn


	bool CReduceDamage::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CReduceDamage::accept(IMessage *message)
	{
		return (!message->getType().compare("MActivateReduceDamage"));
	} // accept
	
	//---------------------------------------------------------

	void CReduceDamage::process(IMessage *message)
	{
		
		if (!message->getType().compare("MActivateReduceDamage")){

			_numEnt = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),_reduceDistance,_entidades);

			MDamaged *message = new MDamaged();
			message->setDamageModification(_reduceDamage);
			message->setDamageAction(DamageMessage::ADD_DAMAGE_MODIFICATION);

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

	void CReduceDamage::timeElapsed()
	{
		
		MDamaged *message = new MDamaged();
		message->setDamageModification(_reduceDamage*-1.0);
		message->setDamageAction(DamageMessage::ADD_DAMAGE_MODIFICATION);

		message->addPtr();
		for (int i =0; i < _numEnt; ++i)
		{
			if (!_entidades[i]->getTag().compare("Player") ){
				_entidades[i]->emitMessage(message);
			}

		}
		message->removePtr();

		if (_reduceTime > 0){

			_numEnt = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),_reduceDistance,_entidades);

			MDamaged *message2 = new MDamaged();
			message2->setDamageModification(_reduceDamage);
			message2->setDamageAction(DamageMessage::ADD_DAMAGE_MODIFICATION);

			message2->addPtr();
			for (int i =0; i < _numEnt; ++i)
			{
				if (!_entidades[i]->getTag().compare("Player") ){
					
					_entidades[i]->emitMessage(message2);
					
				}
			}
			message2->removePtr();
			
			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(1000, this);
			_reduceTime-=1000;

		}else{
			
		}
		
		

	} // timeElapsed

} // namespace Logic

