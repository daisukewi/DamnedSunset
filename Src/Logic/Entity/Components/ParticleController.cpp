#include "ParticleController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"



namespace Logic 
{
	IMP_FACTORY(CParticleController);
	
	//---------------------------------------------------------

	bool CParticleController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CParticleController::activate()
	{	
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CParticleController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CParticleController::accept(IMessage *message)
	{
		return !message->getType().compare("MParticleEffect");

	} // accept

	//---------------------------------------------------------

	void CParticleController::process(IMessage *message)
	{
		if (!message->getType().compare("MParticleEffect")){

		}
	} // process

	//---------------------------------------------------------

	void CParticleController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);	

	} // tick

} // namespace Logic
