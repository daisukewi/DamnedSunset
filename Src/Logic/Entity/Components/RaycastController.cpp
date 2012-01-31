#include "RaycastController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic\Entity\Message.h"
#include "Logic\Entity\Messages\ControlRaycast.h"
#include "Logic/Entity/Messages/MouseMove.h"


namespace Logic 
{
	IMP_FACTORY(CRaycastController);
	
	//---------------------------------------------------------

	bool CRaycastController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CRaycastController::activate()
	{	
		_makeRaycast = false;
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CRaycastController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CRaycastController::accept(IMessage *message)
	{
		return ((!message->getType().compare("MControlRaycast")) || (!message->getType().compare("MMouseMove")));

	} // accept
	
	//---------------------------------------------------------

	void CRaycastController::process(IMessage *message)
	{
		if (!message->getType().compare("MMouseMove"))
		{
			MMouseMove *m = static_cast <MMouseMove*> (message);

			_mouseRelPosX = m->getPoint().x;
			_mouseRelPosY = m->getPoint().y;
		}
		else if (!message->getType().compare("MControlRaycast"))
		{
			MControlRaycast *m_building = static_cast <MControlRaycast*> (message);
			switch (m_building->getAction())
			{
			case RaycastMessage::START_RAYCAST:
				_makeRaycast = true;
				break;
			case RaycastMessage::STOP_RAYCAST:
				_makeRaycast = false;
				break;
			}
		}
	} // process

	//---------------------------------------------------------

	void CRaycastController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (!_makeRaycast) return;

		Vector3 point;
			
		// Lanzar un rayo desde la camara hasta el plano del escenario.
		Ray mouseRay = Graphics::CServer::getSingletonPtr()->getCameraToViewportRay(_mouseRelPosX, _mouseRelPosY);

		Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastAdvanced(mouseRay, &point);

		if (entity == NULL) return;

		// Mandar el mensaje a todos los componentes de esta entidad (_entity)
		MControlRaycast *rc_message = new MControlRaycast();
		rc_message->setAction(RaycastMessage::HIT_RAYCAST);
		rc_message->setCollisionPoint(point);
		rc_message->setCollisionEntity(entity);
		_entity->emitMessage(rc_message);

	} // tick

} // namespace Logic

