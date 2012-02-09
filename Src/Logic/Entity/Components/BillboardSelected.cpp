#include "BillboardSelected.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"

#include "Graphics/Billboard.h"

namespace Logic 
{
	IMP_FACTORY(CBillboardSelected);
	
	//---------------------------------------------------------

	CBillboardSelected::CBillboardSelected() : IComponent() {

	}

	CBillboardSelected::~CBillboardSelected() {

	}

	bool CBillboardSelected::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard();
		_billboard->createBillBoard(_entity);
		_billboard->setMaterial("circuloSeleccion");
		_billboard->setDimensions(10,10);
		//_billboard->setPosition(0,0,0);
		_billboard->setDirection(Vector3::UNIT_Z);
		_billboard->setVisible(false);
		billboardVisible = false;
		return true;

	} // spawn

	//---------------------------------------------------------

	bool CBillboardSelected::accept(IMessage *message)
	{
		return !message->getType().compare("MIsSelectable");
	} // accept
	
	//---------------------------------------------------------

	void CBillboardSelected::process(IMessage *message)
	{
		if (!message->getType().compare("MIsSelectable"))
		{
			billboardVisible = !billboardVisible;
			_billboard->setVisible(billboardVisible);
		}
	} // process


} // namespace Logic

