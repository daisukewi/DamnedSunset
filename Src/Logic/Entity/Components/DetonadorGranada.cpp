#include "DetonadorGranada.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

#include "Logic/Entity/Messages/ActivarComponente.h"
#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

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

		if(entityInfo->hasAttribute("damage"))
			_damage = entityInfo->getFloatAttribute("damage");
		if(entityInfo->hasAttribute("timeEmpujar"))
			_timeEmpujar = entityInfo->getFloatAttribute("timeEmpujar");
		if(entityInfo->hasAttribute("distEmpujarSeg"))
			_distEmpujarSeg = entityInfo->getFloatAttribute("distEmpujarSeg");

		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(2000, this);
		return true;
	} // spawn


	bool CDetonadorGranada::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorGranada::accept(IMessage *message)
	{
		return  !message->getType().compare("MIsTouched");
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
				m->getEntity()->removeDeathListener(this);
			}
		}
	} // process

	void CDetonadorGranada::entityDeath(CEntity* entity)
	{
		/* 
		Implementación del método que va a ser llamado cuando muera la entidad.
		*/
		_entidades.remove(entity);
		entity->removeDeathListener(this);
	}

	void CDetonadorGranada::timeElapsed()
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


		//Recorremos la lista de entidades y les hacemos daño
		std::list<CEntity*>::const_iterator it, end;
		it = _entidades.begin();
		end = _entidades.end();

		for(int i = 0; i < numColisiones; ++i) {
			//Entidad que daña la granada
			CEntity * entidad = entidadesColision[i];

			//Le decimos a la entidad que no nos avise cuando muera
			entidad->removeDeathListener(this);

			//Enviamos mensaje de daño a la entidad
			MDamaged *mDamaged = new MDamaged();
			mDamaged->setHurt(_damage);
			mDamaged->setKiller(0);
			entidad->removeDeathListener(this);
			entidad->emitMessage(mDamaged, this);

			printf("DAÑO GRANADA");

			MSetEmpujarPropiedades *m = new MSetEmpujarPropiedades();

			MActivarComponente *mActivar = new MActivarComponente();
			mActivar->setActivar(true);
			mActivar->setNombreComponente("CEmpujable");
			//Tiene que ser instantaneo, sino no se empujara ya q no esta activo
			entidad->emitInstantMessage(mActivar, this);

			//Calculamos la direccion a la que tenemos que empujar
			Vector3 pos1 = entidad->getPosition();
			Vector3 pos2 = _entity->getPosition();
			Vector3 direccion = Vector3(pos1.x-pos2.x,pos1.y-pos2.y,pos1.z-pos2.z);
			direccion.normalise();
			//----
			m->setDirection(direccion.x,direccion.y,direccion.z);
			m->setTime(_timeEmpujar);
			m->setDistanciaPorSegundo(_distEmpujarSeg);

			entidad->emitMessage(m, this);
		}

		//Eliminamos la entidad en el siguiente tick
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
	} // timeElapsed

} // namespace Logic

