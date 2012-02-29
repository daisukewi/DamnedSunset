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
#include "Logic/Entity/Messages/AStarRoute.h"

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

			// Enviamos una orden de curación al jugador
			_selectionController->sendHealerMsg(entity, true);

			}
			else
			{
				_selectionController->changeState(State::PLAYER_SELECTED);
				_selectionController->sendHealerMsg(entity, false);

				if (!entity->getType().compare("Enemy"))
				{
					// Dejamos de curar y enviamos una orden de ataque al enemigo
					std::cout << "Dejamos de curar y atacamos a: " << entity->getName() << '\n';
					_selectionController->sendAttackMsg(entity, true);
				}
				else if (!entity->getType().compare("World") || !entity->getType().compare("TurretTrigger"))
				{
					std::cout << "Dejamos de curar y vamos al punto: " << point << '\n';
					_selectionController->moveAStar(entity, point);
				}
			}
		}
		if (button == TMouseAction::LEFT_CLICK){
			_selectionController->changeState(State::PLAYER_SELECTED);
		}	
	}

} // namespace Logic