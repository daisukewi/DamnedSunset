#include "SelectionController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"


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
			_entity = message._entity;

			if (_entity != NULL){
				std::cout << "ENTIDAD SELECCIONADA: "<< _entity->getName()<< "\n"; 
				std::cout << "POSICION DE LA ENTIDAD: " << _entity->getPosition(); 
			}else
			{
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
