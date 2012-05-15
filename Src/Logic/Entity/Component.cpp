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
#include "Messages/SetRealTime.h"
#include "Logic/Entity/Entity.h"

namespace Logic 
{
	bool IComponent::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
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
		bool acepted = !message->getType().compare("MActivarComponente") || (_active && ( !message->getType().compare("MSetRealTime") || accept(message) ) );
		return acepted;
	}

	void IComponent::processPadre(IMessage *message)
	{
		if (!message->getType().compare("MActivarComponente"))
		{
			MActivarComponente *m = static_cast <MActivarComponente*> (message);

			std::string s = m->getNombreComponent();
			std::string buf; // Have a buffer string
			std::stringstream ss(s); // Insert the string into a stream
			while (ss >> buf) {
				if (this->getType() == buf)
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
		}
		else if (!message->getType().compare("MSetRealTime"))
		{
			MSetRealTime *m = static_cast <MSetRealTime*> (message);
			_entity->setRealTime(m->getRealTime());
		}
		process(message);
	}

} // namespace Logic
