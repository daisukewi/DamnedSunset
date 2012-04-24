#include "DetonadorBolaTeltr.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"
#include "Logic/Entity/Messages/TeletransportTo.h"

#include "Physics/Server.h"

namespace Logic 
{
	IMP_FACTORY(CDetonadorBolaTeltr);
	
	//---------------------------------------------------------

	CDetonadorBolaTeltr::CDetonadorBolaTeltr() : IComponent() {

	}

	CDetonadorBolaTeltr::~CDetonadorBolaTeltr() {
	}

	bool CDetonadorBolaTeltr::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(2000, this);
		return true;
	} // spawn


	bool CDetonadorBolaTeltr::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorBolaTeltr::accept(IMessage *message)
	{
		return  !message->getType().compare("MIsTouched");
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorBolaTeltr::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);
			if (m->getTouched() && !m->getEntity()->getType().compare("Enemy"))
			{
				_entidades.push_back(m->getEntity());
			} else if (!m->getTouched())
			{
				_entidades.remove(m->getEntity());
			}
		}
	} // process

	void CDetonadorBolaTeltr::timeElapsed()
	{

		Logic::CEntity* * entidadesColision;
		int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),20,entidadesColision);

		for (int i =0; i < numColisiones; ++i)
		{
			std::string a = entidadesColision[i]->getName();
		}

		//Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
		MParticleEffect *rc_message = new MParticleEffect();
		rc_message->setPoint(_entity->getPosition());
		rc_message->setEffect("Spiral");
		_entity->emitInstantMessage(rc_message,this);

		//Envío del mensaje al componente que se encarga de reproducir los sonidos
		MSoundEffect *rc2_message = new MSoundEffect();
		rc2_message->setSoundEffect("media/sounds/teletransporte.mp3");
		_entity->emitInstantMessage(rc2_message,this);


		//Recorremos la lista de entidades y las teletransportamos
		std::list<CEntity*>::const_iterator it, end;
		it = _entidades.begin();
		end = _entidades.end();

		for(int i = 0; i < numColisiones; ++i) {
			//Entidad que daña la granada
			CEntity * entidad = entidadesColision[i];

			//Enviamos mensaje de teletransporte a la entidad
			MTeletransportTo *mTrans = new MTeletransportTo();
			//mTrans->setPosition(entidad->getPosition() + Vector3(0, 10, 0));
			mTrans->setPosition( Vector3 ( rand() % 200 - 100, 5.0f, rand() % 200 - 100));
			entidad->emitMessage(mTrans, this);

			printf("TELETRANSPORTE REALIZADO");
		}

		//Eliminamos la entidad en el siguiente tick
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);

	} // timeElapsed

} // namespace Logic

