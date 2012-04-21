#include "BillboardIndicacionMover.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Entity/Messages/CrearBillboardMovimiento.h"

namespace Logic 
{
	IMP_FACTORY(CBillboardIndicacionMover);
	
	//---------------------------------------------------------

	CBillboardIndicacionMover::CBillboardIndicacionMover() : IComponent() {

	}

	CBillboardIndicacionMover::~CBillboardIndicacionMover() {
		if (_billboard)
			delete _billboard;
	}

	bool CBillboardIndicacionMover::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardMoverMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardMoverMaterial"));
		
		_billboard->setPerpendicular();
		_billboard->setVisible(false);
		_billboardVisible = false;

		if(entityInfo->hasAttribute("billboardMoverDimension"))
			_startDimension = entityInfo->getFloatAttribute("billboardMoverDimension");
		_billboard->setDimensions(_startDimension,_startDimension);
		if(entityInfo->hasAttribute("billboardMoverTime"))
			_startTime = entityInfo->getFloatAttribute("billboardMoverTime");
		return true;

	} // spawn

	//---------------------------------------------------------

	bool CBillboardIndicacionMover::accept(IMessage *message)
	{
		return !message->getType().compare("MCrearBillboardMovimiento");
	} // accept
	
	//---------------------------------------------------------

	void CBillboardIndicacionMover::process(IMessage *message)
	{
		if (!message->getType().compare("MCrearBillboardMovimiento"))
		{
			MCrearBillboardMovimiento *m = static_cast <MCrearBillboardMovimiento*> (message);
			_billboard->setPosition(m->getPosX()-7.5,0.3f,m->getPosY()-7.5);
			_billboardVisible = true;
			_billboard->setVisible(true);
			_time = _startTime;
		} 
	} // process

	void CBillboardIndicacionMover::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		if (_billboardVisible)
		{
			_time -=msecs/1000.0f;
			if (_time <=0 )
			{
				_billboardVisible = false;
				_billboard->setVisible(false);
			} else {
				float timeProportion = _time / _startTime;
				_billboard->setDimensions( _startDimension * timeProportion, _startDimension * timeProportion);
			}
		}

	}

} // namespace Logic

