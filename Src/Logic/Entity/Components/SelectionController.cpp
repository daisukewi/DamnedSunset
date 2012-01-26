#include "SelectionController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "AI/Movement.h"


namespace Logic 
{
	IMP_FACTORY(CSelectionController);
	
	//---------------------------------------------------------

	bool CSelectionController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSelectionController::activate()
	{	
		_entity = NULL;
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSelectionController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSelectionController::accept(const TMessage &message)
	{
		return message._type == Message::ENTITY_SELECTED;

	} // accept
	
	//---------------------------------------------------------

	void CSelectionController::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::ENTITY_SELECTED:
			CEntity *_aux = message._entity;

			if (_aux->getType() == "Player")
			{
				_entity = message._entity;
				std::cout << "ENTIDAD SELECCIONADA: "<< _entity->getName()<< "\n"; 
				std::cout << "POSICION DE LA ENTIDAD: " << _entity->getPosition()<< "\n"; 
				
			}else if ((_aux->getType() == "World") & (_entity != NULL) ){
				if (_entity->getType() == "Player"){
					std::cout << "PUNTO DEL MAPA: " << message._pointvector3->x << "," << message._pointvector3->y << "," << message._pointvector3->z<< "\n"; 
				
					TMessage m;
					m._type = Message::MOVE_TO;
					m._vector3.x = message._pointvector3->x;
					m._vector3.y = message._pointvector3->y;
					m._vector3.z = message._pointvector3->z;

					m._int = AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE;
					_entity->emitMessage(m);
				
				}
			}


			

			
			break;
		}

	} // process

	//---------------------------------------------------------

	void CSelectionController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
			

	} // tick

} // namespace Logic
