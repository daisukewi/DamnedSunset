/**
@file Building.cpp

Contiene la implementación la clase que representa el estado en el que se encuentra el SelectionController
cuando se está construyendo. 

@see Logic::Building.h

@author Alberto Ortega
@date Febreo, 2012
*/

#include "Building.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Components/SelectionController.h"

#include "Logic/Entity/Messages/EmplaceBuilding.h"

namespace Logic
{


	void CBuilding::click(CEntity* entity, Vector3 point, int button){
		std::cout << "ESTADO BUILDING" << "\n";
		if (button == TMouseAction::LEFT_CLICK){
			MEmplaceBuilding *m_emplace = new MEmplaceBuilding();
			m_emplace->setAction(BuildingMessage::EMPLACE_BUILDING);
			_selectionController->getEntity()->emitMessage(m_emplace);
		}			
	}

} // namespace Logic