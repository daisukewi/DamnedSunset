/**
@file SwitchTrigger.cpp

Contiene la implementación del componente que envia un mensaje MSwitch a una
entidad cuando su entidad es tocada o dejada de ser tocada.
 
@see Logic::CSwitchTrigger
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "SwitchTrigger.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Switch.h"

namespace Logic 
{
	IMP_FACTORY(CSwitchTrigger);
	
	//---------------------------------------------------------

	bool CSwitchTrigger::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		assert(entityInfo->hasAttribute("target") && "Hay que especificar el atributo target");

		_targetName = entityInfo->getStringAttribute("target");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSwitchTrigger::activate()
	{
		// Obtenemos la entidad objetivo a lanzar.
		if(_targetName.length())
			_target = _entity->getMap()->getEntityByName(_targetName);

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CSwitchTrigger::deactivate()
	{
		_target = 0;

	} // deactivate
	
	//---------------------------------------------------------

	bool CSwitchTrigger::accept(IMessage *message)
	{
		return !message->getType().compare("MIsTouched");

	} // accept
	
	//---------------------------------------------------------

	void CSwitchTrigger::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);

			if (_target)
			{
				Logic::MSwitch *m2 = new Logic::MSwitch();

				if (m->getTouched())
					m2->setState(1);
				else
					m2->setState(0);

				_target->emitMessage(m2);
			}
		}

	} // process


} // namespace Logic

