#include "Minimap.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"
#include "Logic/Maps/Map.h"
#include "Logic/Server.h"

#include "Logic/Entity/Messages/DayNight.h"
#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/Damaged.h"


#include "Graphics/ModelFactory.h"


namespace Logic 
{
	IMP_FACTORY(CMinimap);
	//---------------------------------------------------------

	bool CMinimap::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{


		return true;
	} // spawn


	bool CMinimap::activate()
	{

		return true;
	} // activate
	//---------------------------------------------------------

	bool CMinimap::accept(IMessage *message)
	{
		return true;
	} // accept
	
	//---------------------------------------------------------

	void CMinimap::process(IMessage *message)
	{
		
	} // process

	void CMinimap::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

	
	}
} // namespace Logic

