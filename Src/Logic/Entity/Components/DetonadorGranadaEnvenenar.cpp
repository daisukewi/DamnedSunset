#include "DetonadorGranadaEnvenenar.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/Venom.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

#include "Logic/Entity/Entity.h"



namespace Logic 
{
	IMP_FACTORY(CDetonadorGranadaEnvenenar);
	
	//---------------------------------------------------------

	CDetonadorGranadaEnvenenar::CDetonadorGranadaEnvenenar() : IComponent() {

	}

	CDetonadorGranadaEnvenenar::~CDetonadorGranadaEnvenenar() {
	}

	bool CDetonadorGranadaEnvenenar::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("time"))
			_venomTime = entityInfo->getFloatAttribute("time");

		if(entityInfo->hasAttribute("damage"))
			_venomDamage = entityInfo->getFloatAttribute("damage");

		if(entityInfo->hasAttribute("count"))
			_venomCount = entityInfo->getFloatAttribute("count");


		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(2000, this);
		return true;
	} // spawn


	bool CDetonadorGranadaEnvenenar::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorGranadaEnvenenar::accept(IMessage *message)
	{
		return  false;
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorGranadaEnvenenar::process(IMessage *message)
	{

	} // process

	void CDetonadorGranadaEnvenenar::timeElapsed()
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

			//Enviamos mensaje de envenenar a la entidad
			MVenom *m = new MVenom();
			m->setVenomTime(_venomTime);
			m->setVenomDamage(_venomDamage);
			m->setCount(_venomCount);
			entidad->emitMessage(m, this);

			printf("VENOM");

		}
		//Eliminamos la entidad en el siguiente tick
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
	} // timeElapsed

} // namespace Logic

