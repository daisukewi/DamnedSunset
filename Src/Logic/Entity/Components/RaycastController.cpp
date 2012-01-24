#include "RaycastController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"


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

	bool CRaycastController::accept(const TMessage &message)
	{
		return message._type == Message::CAMERA_CLICK;

	} // accept
	
	//---------------------------------------------------------

	void CRaycastController::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::CAMERA_CLICK:
			_mouseRelPosX = message._vector2.x;
			_mouseRelPosY = message._vector2.y;

			_makeRaycast = true;
		}

	} // process

	//---------------------------------------------------------

	void CRaycastController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (_makeRaycast){
			Vector3 *point = new Vector3();
		
			//Obtener el rayo a lanzar.
			Ray mouseRay = Graphics::CServer::getSingletonPtr()->getCameraToViewportRay(_mouseRelPosX, _mouseRelPosY);

			Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastAdvanced(mouseRay, point);

			if (entity != NULL){
		
			std::cout << "Punto: " << point->x << "," << point->y << "," << point->z <<"\n"; 
			std::cout << "Entidad: "<< entity->getName()<< "\n"; 
			std::cout << "Ray: " << mouseRay.getOrigin() << " " << mouseRay.getDirection()<< "\n"; 
			std::cout << "Mouse: " << _mouseRelPosX << " " << _mouseRelPosY << "\n"<< "\n"; 

			TMessage message;
			message._type = Message::SELECTABLE;
			message._entity = entity;
			entity->emitMessage(message);
				
			}else{
		
				std::cout << "Punto: "<< "\n"; 
				std::cout << "Entidad: "<< "\n"; 
				std::cout << "Ray: " << mouseRay.getOrigin() << " " << mouseRay.getDirection();
				std::cout << "Mouse: " << _mouseRelPosX << " " << _mouseRelPosY << "\n"<< "\n";  
			}
			
			_makeRaycast = false;
		}
		

	} // tick

} // namespace Logic

