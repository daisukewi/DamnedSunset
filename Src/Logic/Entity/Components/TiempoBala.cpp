#include "TiempoBala.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Maps/Map.h"

#include "Logic/Entity/Messages/ActivarTiempoBala.h"
#include "Logic\Entity\Messages\SetRealTime.h"

namespace Logic 
{
	IMP_FACTORY(CTiempoBala);
	
	//---------------------------------------------------------

	CTiempoBala::CTiempoBala() : IComponent() {
		_entitiesID = NULL;
		_numEntities = 0;
	}

	CTiempoBala::~CTiempoBala() {
	}

	bool CTiempoBala::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		return true;
	} // spawn


	bool CTiempoBala::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CTiempoBala::accept(IMessage *message)
	{
		return  !message->getType().compare("MActivarTiempoBala");
	} // accept
	
	//---------------------------------------------------------

	void CTiempoBala::process(IMessage *message)
	{
		if (!message->getType().compare("MActivarTiempoBala"))
		{
			MActivarTiempoBala *m = static_cast <MActivarTiempoBala*> (message);
			_entitiesID = m->getEntitiesID();
			_numEntities = m->getNumEntities();
			m->invalidateIDs();

			//Enviamos un mensaje a las entidades para q no les afecte el tiempo bala
			Logic::MSetRealTime * msrt = new Logic::MSetRealTime();
			msrt->setRealTime(true);
			for (int i = 0; i < _numEntities; ++i)
			{
				unsigned int id = _entitiesID[i];
				Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(id)->emitMessage(msrt);
			}
			//Aplicamos el efecto bala
			BaseSubsystems::CServer::getSingletonPtr()->setFactorRalentizar(5);

			//Que nos avise, cuando haya pasado el tiempo para que se tenga q detener el tiempo bala
			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(m->getTime() *1000, this);
		}
	} // process



	void CTiempoBala::timeElapsed()
	{
		//Desactivamos el efecto bala
		BaseSubsystems::CServer::getSingletonPtr()->setFactorRalentizar(1);

		//Enviamos un mensaje a las entidades para q no les afecte el tiempo bala
		Logic::MSetRealTime * msrt = new Logic::MSetRealTime();
		msrt->setRealTime(true);
			
		for (int i = 0; i < _numEntities; ++i)
		{
			Logic::CServer::getSingletonPtr()->getMap()->getEntityByID(_entitiesID[i])->emitMessage(msrt);
		}
		delete _entitiesID;
		_entitiesID = NULL;
	} // timeElapsed

} // namespace Logic

