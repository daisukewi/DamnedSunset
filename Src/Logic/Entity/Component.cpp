/**
@file Components/Component.cpp

Contiene la implementación de la clase base de los componentes.
 
@see Logic::IComponent
@see Logic::CCommunicationPort

@author David Llansó
@date Julio, 2010
*/

#include "Component.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Map/MapEntity.h"
#include "Messages/ActivarComponente.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	bool IComponent::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		_active = true;
		_entity = entity;
		return true;

	} // spawn
	
	//---------------------------------------------------------

	void IComponent::tick(unsigned int msecs)
	{
		processMessages();
	} // tick

	bool IComponent::acceptPadre(IMessage *message)
	{
		bool acepted = !message->getType().compare("MActivarComponente") || accept(message);
		return acepted;
	}

	void IComponent::processPadre(IMessage *message)
	{
		if (!message->getType().compare("MActivarComponente"))
		{
			MActivarComponente *m = static_cast <MActivarComponente*> (message);
			if (m->getNombreComponent() == this->getType())
			{
				if ( m->getActivar() && !_active)
				{
					this->activate();
					_active = true;
				}
				else if ( !m->getActivar() && _active)
				{
					this->deactivate();
					_active = false;
				}
			}
		}
		process(message);
	}

} // namespace Logic
