#include "SoundController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic/Maps/EntityFactory.h"

#include "Logic/Entity/Messages/ParticleEffect.h"

namespace Logic 
{
	IMP_FACTORY(CSoundController);
	
	//---------------------------------------------------------

	bool CSoundController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSoundController::activate()
	{	
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSoundController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSoundController::accept(IMessage *message)
	{
		return !message->getType().compare("MSoundController");

	} // accept

	//---------------------------------------------------------

	void CSoundController::process(IMessage *message)
	{
		if (!message->getType().compare("MSoundController")){

			MParticleEffect *m = static_cast <MParticleEffect*> (message);
			std::string effect = "Explosion";
			Graphics::CServer::getSingletonPtr()->createParticleEffect(effect,m->getPoint());
		
			//Esto es usado por la granada, para que no se destruya la entidad antes de reproducir el efecto de partículas
			//Si la entidad está desactivada
			if (!_entity->isActivated())
				//Eliminamos la entidad en el siguiente tick
				CEntityFactory::getSingletonPtr()->deferredDeleteEntity(_entity);
		}
	} // process

	//---------------------------------------------------------

	void CSoundController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);	

	} // tick

} // namespace Logic
