/**
@file PlayerSelected.cpp

Contiene la implementación de la clase encargada de gestionar el estado PlayerSelected

@see Logic::PlayerSelected.h

@author Alberto Ortega
@date Febreo, 2012
*/

#include "PlayerSelected.h"

#include "Logic/Entity/Messages/MouseEvent.h"
#include "Logic/Entity/Messages/AStarRoute.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/CrearBillboardMovimiento.h"

#include "Logic/Entity/Components/SelectionController.h"

#include "ScriptManager/Server.h"

namespace Logic
{

	void CPlayerSelected::click(CEntity* entity, Vector3 point, int button){
		std::cout << "ESTADO PLAYER SELECTED" << "\n";

		if (button == TMouseAction::LEFT_CLICK)
		{
		
			if (!entity->getType().compare("Player"))
			{
				//_selectionController->changeSelectedEntity(entity);

			}
	
		}	
		if (button == TMouseAction::RIGHT_CLICK)
		{
		
			if (!entity->getType().compare("World") || !entity->getType().compare("TurretTrigger"))
			{

				// Dejamos de atacar
				//_selectionController->sendAttackMsg(entity, false);
				
				//_selectionController->moveAStar(entity, point);

				//Mensaje para que se cree el billboard de movimiento en el mundo
				Logic::MCrearBillboardMovimiento *mCrearBillboardMovimiento = new Logic::MCrearBillboardMovimiento();
				mCrearBillboardMovimiento->setPosX(point.x);
				mCrearBillboardMovimiento->setPosY(point.z);
				entity->emitMessage(mCrearBillboardMovimiento);

				std::cout << "Mover entidad: " << entity->getName() << " a: " << point;
			}else{

			if (!entity->getType().compare("Enemy"))
			{

				// Enviamos una orden de ataque al enemigo
				//_selectionController->sendAttackDistanceMsg(entity);

			}
	
			}	
		}
	}

} // namespace Logic