#include "DetonadorGranada.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Maps/EntityFactory.h"

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
		return false;
	} // accept
	
	//---------------------------------------------------------

	void CDetonadorGranada::process(IMessage *message)
	{

	} // process

	void CDetonadorGranada::timeElapsed()
	{
		/* 
		@TEMPORIZADOR Implementación del método de la interfaz que va a ser llamado cuando se acabe el tiempo.
		Aunque parezca que el método es asíncrono en realidad no lo es. Está enganchado al tick del reloj
		que se ejecuta al final de cada frame. Por lo tanto esta llamada se ejecutará al final del frame
		en el que se termine el temporizador. Ahora mismo no creo que haya mucha diferencia pero está bien
		que lo sepáis por si en un futuro ocurren cosas raras.
		Aquí irá el código que queréis que se ejecute cuando el temporizador llegue a cero.
		*/

		int a = 5;
		CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
		

	} // timeElapsed

} // namespace Logic

