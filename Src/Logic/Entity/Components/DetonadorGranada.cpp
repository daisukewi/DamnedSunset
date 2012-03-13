#include "DetonadorGranada.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"

namespace Logic 
{
	IMP_FACTORY(CDetonadorGranada);
	
	//---------------------------------------------------------

	CDetonadorGranada::CDetonadorGranada() : IComponent() {

	}

	CDetonadorGranada::~CDetonadorGranada() {

		
	}

	bool CDetonadorGranada::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;


		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(3000, this);

		return true;
	} // spawn


	bool CDetonadorGranada::activate()
	{
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorGranada::accept(IMessage *message)
	{
		return !message->getType().compare("MIsTouched");;
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorGranada::process(IMessage *message)
	{
		if (!message->getType().compare("MIsTouched"))
		{
			MIsTouched *m = static_cast <MIsTouched*> (message);
			if (m->getTouched() && !m->getEntity()->getType().compare("Enemy"))
			{
				_entidades.push_back(m->getEntity());
				_entidades.back()->addDeathListener(this);
			} else if (!m->getTouched())
			{
				_entidades.remove(m->getEntity());
			}
		}
	} // process

	void CDetonadorGranada::entityDeath(CEntity* entity)
	{
		/* 
		Implementaci�n del m�todo que va a ser llamado cuando muera la entidad.
		*/
		_entidades.remove(entity);
		entity->removeDeathListener(this);

	}

	void CDetonadorGranada::timeElapsed()
	{
		//Recorremos la lista de entidades dentro del trigger y les hacemos da�o
		std::list<CEntity*>::const_iterator it, end;
		it = _entidades.begin();
		end = _entidades.end();

		//Env�o del mensaje al componente que se encarga de mostrar los efectos de part�culas
		MParticleEffect *rc_message = new MParticleEffect();
		rc_message->setPoint(_entity->getPosition());
		_entity->emitMessage(rc_message,this);

		for(; it != end; it++) {
			//Entidad que da�a la granada
			CEntity * entidad = *it;

			//Le decimos a la entidad que no nos avise cuando muera
			entidad->removeDeathListener(this);

			//Enviamos mensaje de da�o a la entidad
			MDamaged *mDamaged = new MDamaged();
			mDamaged->setHurt(100.0f);
			mDamaged->setKiller(0);
			entidad->emitMessage(mDamaged, this);

			printf("DA�O GRANADA");
		}

		//Se desactiva le entidad. No se destruye para que si es necesario realizar alguna acci�n que depende de
		//otro componente, pueda hacerlo. Se destruir� en el componente ParticleController, en caso de que la entidad est�
		//desactivada.
		_entity->deactivate();

	} // timeElapsed

} // namespace Logic

