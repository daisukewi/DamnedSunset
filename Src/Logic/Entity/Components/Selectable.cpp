#include "Selectable.h"

#include "Logic/Entity/Entity.h"

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
			if (m_selectable->getMessageType() == SelectablePetition::SELECTION_REQUEST)
			{
				//Obtener la entidad encargadad de controllar el gameplay
				CEntity *senderEntity = m_selectable->getSenderEntity();
				if (senderEntity == NULL)
					return;
			
				//Crear y enviar el mensaje de entity selected
				MIsSelectable* m_selected = new MIsSelectable();
				m_selected->setMessageType(SELECTION_RESPONSE);
				m_selected->setSenderEntity(_entity);
				senderEntity->emitInstantMessage(m_selected);
				//senderEntity->emitMessage(m_selected);
			}
		}

	} // process

	//---------------------------------------------------------

	void CSelectable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	} // tick

} // namespace Logic
