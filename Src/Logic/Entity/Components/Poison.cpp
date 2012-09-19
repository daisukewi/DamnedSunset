#include "Poison.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "BaseSubsystems/Server.h"

#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/Venom.h"

#include "Logic/Entity/Messages/Damaged.h"

#include "Graphics/Billboard.h"

namespace Logic 
{
	IMP_FACTORY(CPoison);
	//---------------------------------------------------------

	CPoison::CPoison() : IComponent(), BaseSubsystems::IClockListener() {
		
		
	}

	CPoison::~CPoison() {
		if (_billboard)
			delete _billboard;
	}

	bool CPoison::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("poisonSound"))
			_poisonSound = entityInfo->getFloatAttribute("poisonSound");

		if(entityInfo->hasAttribute("poisonEffect"))
			_poisonEffect = entityInfo->getFloatAttribute("poisonEffect");


		//Billboard

		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardPoisonMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardPoisonMaterial"));
		if(entityInfo->hasAttribute("billboardPoisonWith") && entityInfo->hasAttribute("billboardPoisonHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardPoisonWith"),entityInfo->getFloatAttribute("billboardPoisonHeight"));
		if(entityInfo->hasAttribute("billboardPoisonPosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardPoisonPosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}	

		_billboard->setVisible(false);


		return true;
	} // spawn


	bool CPoison::activate()
	{

		_damage = 0;
		_time = 0;
		_count = 0;
		_poison = false;


		return true;
	} // activate
	//---------------------------------------------------------

	bool CPoison::accept(IMessage *message)
	{
		return !message->getType().compare("MVenom");
	} // accept
	
	//---------------------------------------------------------

	void CPoison::process(IMessage *message)
	{
		if (!message->getType().compare("MVenom"))
		{
			if (!_poison){


				MVenom *m = static_cast <MVenom*> (message);
				_damage = m->getVenomDamage();
				_time = m->getVenomTime();
				_count = m->getCount();
			
				_billboard->setVisible(true);

				BaseSubsystems::CServer::getSingletonPtr()->addClockListener(_time, this);
				
				_poison = true;
			
			
			}


		}
	} // process

	void CPoison::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	}

	void CPoison::timeElapsed()
	{
		if (_poison){

			MDamaged *m2 = new MDamaged();
			m2->setHurt(_damage);
			m2->setKiller(_entity);
			_entity->emitMessage(m2);


			_count--;
			if (_count == 0){
				_poison =  false;
				_billboard->setVisible(false);
			}	else{
			
				BaseSubsystems::CServer::getSingletonPtr()->addClockListener(_time, this);
				
			}
		}
	} // timeElapsed

} // namespace Logic

