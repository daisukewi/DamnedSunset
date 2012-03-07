#include "DetonadorGranada.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/IsTouched.h"
#include "Logic/Entity/Messages/Damaged.h"

namespace Logic 
{
	IMP_FACTORY(CDetonadorGranada);
	
	//---------------------------------------------------------

	CDetonadorGranada::CDetonadorGranada() : IComponent() {

	}

	CDetonadorGranada::~CDetonadorGranada() {

		std::list<CEntity*>::const_iterator it, end;
		it = _entidades.begin();
		end = _entidades.end();

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
	}

	bool CDetonadorGranada::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;


		BaseSubsystems::CServer::getSingletonPtr()->addClockListener(500, this);

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
		/* 
		@TEMPORIZADOR Implementaci�n del m�todo de la interfaz que va a ser llamado cuando se acabe el tiempo.
		Aunque parezca que el m�todo es as�ncrono en realidad no lo es. Est� enganchado al tick del reloj
		que se ejecuta al final de cada frame. Por lo tanto esta llamada se ejecutar� al final del frame
		en el que se termine el temporizador. Ahora mismo no creo que haya mucha diferencia pero est� bien
		que lo sep�is por si en un futuro ocurren cosas raras.
		Aqu� ir� el c�digo que quer�is que se ejecute cuando el temporizador llegue a cero.
		*/

		int a = 5;
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
		

	} // timeElapsed

} // namespace Logic

