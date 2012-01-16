/**
@file SunController.cpp

Contiene la implementación del componente que controla el movimiento 
del sol y el control del la luz ambiental.
 
@see Logic::CSunController
@see Logic::IComponent

@author Daniel Flamenco
@date Enero, 2012
*/

#include "SunController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


namespace Logic 
{
	IMP_FACTORY(CSunController);
	
	//---------------------------------------------------------

	bool CSunController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		_phi = entity->getPosition().angleBetween(Vector3(0, 0, entity->getPosition().length())).valueRadians();

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSunController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSunController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSunController::accept(const TMessage &message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CSunController::process(const TMessage &message)
	{

	} // process
	
	//---------------------------------------------------------

	void CSunController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (++_lastUpdate < 60)
			return;

		_lastUpdate = 0;

		Vector3 oldPosition = _entity->getPosition();
		Vector3 newPosition;
		float distance = oldPosition.length();
		
		_phi += Math::fromDegreesToRadians(1.0f);
		_phi = (_phi > Math::PI * 2) ? 0 : _phi;

		newPosition.x += distance * Ogre::Math::Cos(_phi) * Ogre::Math::Sin(_theta);
		newPosition.y += distance * Ogre::Math::Sin(_phi) * Ogre::Math::Sin(_theta);
		newPosition.z += distance * Ogre::Math::Cos(_theta);

		_entity->setPosition(newPosition);

	} // tick

} // namespace Logic

