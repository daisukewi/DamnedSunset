/**
@file PlayerSelected.cpp

Contiene la implementación de la clase encargada de gestionar el estado PlayerSelected

@see Logic::PlayerSelected.h

@author Alberto Ortega
@date Febreo, 2012
*/

#include "PlayerSelected.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Messages/MoveTo.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/CureEntity.h"

#include "Logic/Entity/Components/SelectionController.h"

namespace Logic
{

	void CPlayerSelected::click(CEntity* entity, Vector3 point, int button){
		std::cout << "ESTADO PLAYER SELECTED" << "\n";

		if (button == TMouseAction::LEFT_CLICK)
		{
		
			if (!entity->getType().compare("Player"))
			{
				_selectionController->changeSelectedEntity(entity);

			}
	
		}	
		if (button == TMouseAction::RIGHT_CLICK)
		{
		
			if (!entity->getType().compare("World"))
			{
				
				
				CEntity* selectedEntity = _selectionController->getSelectedEntity();

				MMoveTo *m_moveto = new MMoveTo();
				m_moveto->setPosition(point);
				selectedEntity->emitMessage(m_moveto);

				std::cout << "Mover entidad: " << entity->getName() << " a: " << point;
			}else{

			if (!entity->getType().compare("Enemy"))
			{
				
				CEntity* selectedEntity = _selectionController->getSelectedEntity();

				// Enviamos una orden de ataque al enemigo
				MAttackEntity *m = new MAttackEntity();
				m->setEntity(entity);
				m->setAttack(true);
				selectedEntity->emitMessage(m);

			}
	
			}	
		}
	}

} // namespace Logic