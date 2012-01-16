#include "CameraController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


namespace Logic 
{
	IMP_FACTORY(CCameraController);
	
	//---------------------------------------------------------

	bool CCameraController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CCameraController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CCameraController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	void CCameraController::tick(unsigned int msecs)
	{

	} // tick

} // namespace Logic

