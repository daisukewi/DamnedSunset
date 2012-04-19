#include "Empujable.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"
#include "Logic/Entity/Messages/AvatarWalk.h"

namespace Logic 
{
	IMP_FACTORY(CEmpujable);
	//---------------------------------------------------------

	CEmpujable::CEmpujable() : IComponent() {
	}

	CEmpujable::~CEmpujable() {
	}

	bool CEmpujable::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("afectaEmpujar"))
			_afectaEmpujar = entityInfo->getIntAttribute("afectaEmpujar");
		else
			_afectaEmpujar = 100;
		_distPerSecond = 5; //Valor por defecto

		return true;
	} // spawn


	bool CEmpujable::activate()
	{
		return true;
	} // activate
	//---------------------------------------------------------

	bool CEmpujable::accept(IMessage *message)
	{
		return !message->getType().compare("MSetEmpujarPropiedades");
	} // accept
	
	//---------------------------------------------------------

	void CEmpujable::process(IMessage *message)
	{
		if (!message->getType().compare("MSetEmpujarPropiedades"))
		{
			MSetEmpujarPropiedades *m = static_cast <MSetEmpujarPropiedades*> (message);
			_direccion = m->getDirection();
			_time = m->getTime() * _afectaEmpujar / 100.0f;
			_distPerSecond = m->getDistanciaPorSegundo();
		}
	} // process

	void CEmpujable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Vector3 position =  _entity->getPosition();
		
		unsigned int milisecs = msecs;
		_time -= msecs/1000.0f;

		if (_time < 0 )
		{
			milisecs -= _time*1000; //Si el tiempo fuese mucho menor que 0, moveriamos mas el personaje que lo que tiene q moverse, por lo que lo movemos X msecs menos, donde X es el tiempo que ha pasado de mas
			//Desactivamos el componente
			_active = false;
		}

		float distMover = _distPerSecond * msecs / 1000.0f;

		MAvatarWalk * m = new MAvatarWalk();
		m->setMovement(Vector3(_direccion.x * distMover, _direccion.y * distMover, _direccion.z * distMover));
		_entity->emitMessage(m);
	}
} // namespace Logic

