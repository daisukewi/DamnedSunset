/**
@file DamageTrigger.cpp

Contiene la implementación del componente que envia un mensaje MDamaged cuando su 
entidad es tocada. El mensaje se envía a la entidad que se ha tocado.
 
@see Logic::CDamageTrigger
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "DamageTrigger.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/IsTouched.h"

namespace Logic 
{
	IMP_FACTORY(CDamageTrigger);
	
	//---------------------------------------------------------

	bool CDamageTrigger::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("damage"))
			_damage = entityInfo->getFloatAttribute("damage");

		return true;

	} // spawn

	//---------------------------------------------------------

	bool CDamageTrigger::accept(IMessage *message)
	{
		return !message->getType().compare("MIsTouched");

	} // accept
	
	//---------------------------------------------------------

	void CDamageTrigger::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);

			if (m->getTouched())
			{
				MDamaged *m2 = new MDamaged();
				m2->setHurt(_damage);
				m2->setKiller(_entity);
				m->getEntity()->emitMessage(m2);
			}
		}

	} // process


} // namespace Logic

