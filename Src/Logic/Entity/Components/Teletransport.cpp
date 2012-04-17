/**
@file Teletransport.cpp

Contiene la implementación del componente que se encarga de teletransportar a una entidad a un punto.
 
@see Logic::CTeletransport
@see Logic::IComponent

@author Luis Mendoza
@date Abril, 2012
*/

#include "Teletransport.h"

#include "Logic/Entity/Entity.h"

#include "assert.h"

//Mensajes
#include "Logic/Entity/Messages/TeletransportTo.h"


namespace Logic 
{
	IMP_FACTORY(CTeletransport);
	
	//---------------------------------------------------------

	CTeletransport::CTeletransport(){
	}

	CTeletransport::~CTeletransport() {

	}

	bool CTeletransport::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
	} // spawn
	
	//---------------------------------------------------------

	bool CTeletransport::accept(IMessage *message)
	{
		return (message->getType().compare("MTeletransportTo") == 0);

	} // accept
	
	//---------------------------------------------------------

	void CTeletransport::process(IMessage *message)
	{
		MTeletransportTo *m_trans =  static_cast<MTeletransportTo*> (message);
		Vector3 point = m_trans->getPosition();
		//_entity->setPosition(point);
		//Physics::CServer::getSingletonPtr()->setPosition((CPhysicObjCharacter *)_entity, point);

		std::cout << "Teletransporte procesado" ;
	} // process
} // namespace Logic
