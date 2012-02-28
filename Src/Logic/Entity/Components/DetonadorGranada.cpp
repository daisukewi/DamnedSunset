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

