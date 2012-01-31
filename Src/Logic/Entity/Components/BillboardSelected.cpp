#include "BillboardSelected.h"


namespace Logic 
{
	IMP_FACTORY(CBillboardSelected);
	
	//---------------------------------------------------------

	bool CBillboardSelected::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{

		return true;

	} // spawn

	//---------------------------------------------------------

	bool CBillboardSelected::accept(IMessage *message)
	{
		return !message->getType().compare("Mensaje a recibir");

	} // accept
	
	//---------------------------------------------------------

	void CBillboardSelected::process(IMessage *message)
	{
		if (!message->getType().compare("Mensaje a recibir"))
		{

		}

	} // process


} // namespace Logic

