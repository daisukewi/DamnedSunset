/**
@file Healing.cpp

Contiene la implementación la clase que representa el estado en el que se encuentra el SelectionController
cuando se está construyendo. 

@see Logic::Healing.h

@author Alberto Ortega
@date Febreo, 2012
*/

#include "Healing.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Components/SelectionController.h"

#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/AttackEntity.h"

namespace Logic
{


	void CHealing::click(CEntity* entity, Vector3 point, int button){
		std::cout << "ESTADO HEALING" << "\n";
		if (button == TMouseAction::RIGHT_CLICK){
			if (!entity->getType().compare("Player"))
			{
			/*CEntity* selectedEntity = _selectionController->getSelectedEntity();

			// Enviamos una orden de curación al jugador
			MCureEntity *m = new MCureEntity();
			m->setEntity(entity);
			m->setCure(true);
			selectedEntity->emitMessage(m);*/

			CEntity* selectedEntity = _selectionController->getSelectedEntity();

			// Enviamos una orden de curación al jugador
			MAttackEntity *m = new MAttackEntity();
			m->setEntity(entity);
			m->setAttack(true);
			selectedEntity->emitMessage(m);
			}
		}
		if (button == TMouseAction::LEFT_CLICK){
			_selectionController->changeState(State::PLAYER_SELECTED);
		}	
	}

} // namespace Logic