#include "Empujable.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/SetEmpujarPropiedades.h"

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
		_distPerSecond = 5;

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
		}
	} // process

	void CEmpujable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Vector3 position =  _entity->getPosition();
		float distMover = _distPerSecond * msecs / 1000.0f;
		Vector3 newPosition = Vector3(	position.x + _direccion.x * distMover,
										position.y + _direccion.y * distMover,
										position.z + _direccion.z * distMover );
		_entity->setPosition( newPosition, true );
	}
} // namespace Logic

