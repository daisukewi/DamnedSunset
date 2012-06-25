/**
@file FreState.cpp

Contiene la implementación de la clase encargadade gestionar el estado free

@author Alberto Ortega
@date Febreo, 2012
*/

#include "Free.h"


#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Components/SelectionController.h"

namespace Logic
{


	void CFree::click(CEntity* entity, Vector3 point, int button){
	std::cout << "ESTADO FREE" << "\n";
		if (button == TMouseAction::LEFT_CLICK){
		
			if (!entity->getTag().compare("Player"))
			{
				//_selectionController->changeSelectedEntity(entity);
				//_selectionController->changeState(State::PLAYER_SELECTED);
			}

			if (!entity->getType().compare("Building"))
			{
			}
		
		
		}	
	}

} // namespace Logic
