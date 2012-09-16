#include "DetonadorGranadaAturdir.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/IASleep.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

#include "Logic/Entity/Entity.h"



namespace Logic 
{
	IMP_FACTORY(CDetonadorGranadaAturdir);
	
	//---------------------------------------------------------

	CDetonadorGranadaAturdir::CDetonadorGranadaAturdir() : IComponent() {

	}

	CDetonadorGranadaAturdir::~CDetonadorGranadaAturdir() {
	}

	bool CDetonadorGranadaAturdir::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("time"))
			_time = entityInfo->getFloatAttribute("time");


		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(2000, this);
		return true;
	} // spawn

	void CDetonadorGranadaAturdir::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if ( _entity->getPosition().y < 0 ) {
			_entity->setPosition( Vector3(_entity->getPosition().x, 0 , _entity->getPosition().z) );
		}
	}

	bool CDetonadorGranadaAturdir::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorGranadaAturdir::accept(IMessage *message)
	{
		return  false;
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorGranadaAturdir::process(IMessage *message)
	{

	} // process

	void CDetonadorGranadaAturdir::timeElapsed()
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
		rc_message->setEffect("Explosion");
		_entity->emitInstantMessage(rc_message,this);

		//Envío del mensaje al componente que se encarga de reproducir los sonidos
		MSoundEffect *rc2_message = new MSoundEffect();
		rc2_message->setSoundEffect("media/sounds/rocket_explosion.wav");
		_entity->emitInstantMessage(rc2_message,this);

		for(int i = 0; i < numColisiones; ++i)
		{
			//Entidad que daña la granada
			CEntity * entidad = entidadesColision[i];

			//Enviamos mensaje de dormir la IA de la entidad
			MIASleep *m = new MIASleep();
			m->setTime(_time);
			entidad->emitMessage(m, this);

			printf("SLEEP IA");

		}
		//Eliminamos la entidad en el siguiente tick
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
	} // timeElapsed

} // namespace Logic

