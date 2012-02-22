#include "Selectable.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic/Maps/Map.h"
#include "Logic/Entity/Messages/EntitySelected.h"
#include "Logic/Entity/Messages/IsSelectable.h"

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

	bool CSelectable::accept(IMessage *message)
	{
		return !message->getType().compare("MIsSelectable");

	} // accept

	//---------------------------------------------------------

	void CSelectable::process(IMessage *message)
	{
		if (!message->getType().compare("MIsSelectable")){

			MIsSelectable *m_selectable = static_cast <MIsSelectable*> (message);

			//Obtener la entidad encargadad de controllar el gameplay
			CEntity *entity = _entity->getMap()->getEntityByName("PlayerGod");
			
			//Crear y enviar el mensaje de entity selected
			MEntitySelected* m_selected = new MEntitySelected();
			m_selected->setSelectedEntity(_entity);
			m_selected->setPoint(m_selectable->getPoint());
			entity->emitMessage(m_selected);
		}
	} // process

	//---------------------------------------------------------

	void CSelectable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		

	} // tick

} // namespace Logic
