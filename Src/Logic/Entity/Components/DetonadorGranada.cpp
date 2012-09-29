#include "DetonadorGranada.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Map/MapEntity.h"

#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"
#include "Logic/Entity/Messages/ActivarComponente.h"

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

		if(entityInfo->hasAttribute("detonadorGranadaEffect"))
			_detonadorGranadaEffect = entityInfo->getStringAttribute("detonadorGranadaEffect");
		if(entityInfo->hasAttribute("detonadorGranadaSound"))
			_detonadorGranadaSound = entityInfo->getStringAttribute("detonadorGranadaSound");


		if(entityInfo->hasAttribute("radius"))
			_radius = entityInfo->getFloatAttribute("radius");


		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(2000, this);
		_exploited = false;

		return true;
	} // spawn


	bool CDetonadorGranada::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	bool CDetonadorGranada::accept(IMessage *message)
	{
		return  false;
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorGranada::process(IMessage *message)
	{

	} // process

	void CDetonadorGranada::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (!_exploited)
			if ( _entity->getPosition().y < 0 ) {
				_entity->setPosition( Vector3(_entity->getPosition().x, 0 , _entity->getPosition().z) );
			}
	}

	//---------------------------------------------------------

	unsigned int CDetonadorGranada::getThaId()
	{
		return _entity->getEntityID();
	}

	//---------------------------------------------------------

	void CDetonadorGranada::timeElapsed()
	{

		if (!_exploited){

			Logic::CEntity* * entidadesColision;
			int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions( _entity->getPosition(),_radius,entidadesColision);

			for (int i =0; i < numColisiones; ++i)
			{
				std::string a = entidadesColision[i]->getName();
			}

			//Envío del mensaje al componente que se encarga de mostrar los efectos de partículas
			MParticleEffect *rc_message = new MParticleEffect();
			rc_message->setPoint(_entity->getPosition());
			rc_message->setStatic(true);
			rc_message->setEffect(_detonadorGranadaEffect);
			_entity->emitInstantMessage(rc_message,this);

			//Envío del mensaje al componente que se encarga de reproducir los sonidos
			MSoundEffect *rc2_message = new MSoundEffect();
			rc2_message->setSoundEffect(_detonadorGranadaSound);
			_entity->emitInstantMessage(rc2_message,this);

			for(int i = 0; i < numColisiones; ++i)
			{
				//Entidad que daña la granada
				CEntity * entidad = entidadesColision[i];

				if (!(entidad->getTag() == "Player"))
				{
					//Enviamos mensaje de daño a la entidad
					MDamaged *mDamaged = new MDamaged();
					mDamaged->setHurt(_damage);
					mDamaged->setKiller(0);
					entidad->emitMessage(mDamaged, this);

					printf("DAÑO GRANADA");

					//EMPUJAR
			
					//Activamos el componente de empujar
					MActivarComponente *mActivar = new MActivarComponente();
					mActivar->setActivar(true);
					mActivar->setNombreComponente("CEmpujable");
					entidad->emitInstantMessage(mActivar, this); //Tiene que ser instantaneo, sino no se empujara ya q no esta activo

					//Calculamos la direccion a la que tenemos que empujar
					Vector3 pos1 = entidad->getPosition();
					Vector3 pos2 = _entity->getPosition();
					Vector3 direccion = Vector3(pos1.x-pos2.x,pos1.y-pos2.y,pos1.z-pos2.z);
					direccion.normalise();
					//----
					MSetEmpujarPropiedades *m = new MSetEmpujarPropiedades();
					m->setDirection(direccion.x,direccion.y,direccion.z);
					m->setTime(_timeEmpujar);
					m->setDistanciaPorSegundo(_distEmpujarSeg);

					entidad->emitMessage(m, this);
				}
			}
			
			_exploited = true;

			BaseSubsystems::CServer::getSingletonPtr()->addClockListener(6000, this);
			
			_entity->setPosition( Vector3(_entity->getPosition().x, -5 , _entity->getPosition().z) );

		}else{
			
			CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
		
		}

		
	} // timeElapsed

} // namespace Logic

