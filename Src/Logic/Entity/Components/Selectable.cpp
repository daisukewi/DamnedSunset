#include "Selectable.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic/Maps/Map.h"


namespace Logic 
{
	IMP_FACTORY(CSelectable);
	
	//---------------------------------------------------------

	bool CSelectable::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSelectable::activate()
	{	
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSelectable::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSelectable::accept(const TMessage &message)
	{
		return message._type == Message::SELECTABLE;

	} // accept
	
	//---------------------------------------------------------

	void CSelectable::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SELECTABLE:
			//Obtener la entidad encargadad de controllar el gameplay
			CEntity *entity = _entity->getMap()->getEntityByName("TargetCamera");
			TMessage m;
			m._type = Message::ENTITY_SELECTED;
			m._entity = _entity;
			m._pointvector3 = message._pointvector3;
			entity->emitMessage(m);
			
			break;
		}

	} // process

	//---------------------------------------------------------

	void CSelectable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		

	} // tick

} // namespace Logic
