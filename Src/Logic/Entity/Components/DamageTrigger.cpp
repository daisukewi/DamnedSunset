/**
@file DamageTrigger.cpp

Contiene la implementación del componente que envia un mensaje CDamaged cuando su 
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
		return !message->getType().compare("CIsTouched");

	} // accept
	
	//---------------------------------------------------------

	void CDamageTrigger::process(IMessage *message)
	{
		if (!message->getType().compare("CIsTouched"))
		{
			CIsTouched *m = static_cast <CIsTouched*> (message);

			if (m->getTouched())
			{
				CDamaged *m2 = new CDamaged();
				m2->setHurt(_damage);
				m->getEntity()->emitMessage(m2);
			}
		}

	} // process


} // namespace Logic

