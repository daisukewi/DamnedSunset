/**
@file LanzandoGranada.cpp

Contiene la implementación de la clase encargada de gestionar el estado LanzandoGranada

@see Logic::PlayerSelected.h

@author Isaac Gallarzagoitia
@date Febreo, 2012
*/

#include "LanzandoGranada.h"

#include "Logic/Entity/Messages/MouseEvent.h"

#include "Logic/Entity/Messages/LanzarGranada.h"

#include "Logic/Entity/Components/SelectionController.h"

namespace Logic
{

	void CLanzandoGranada::click(CEntity* entity, Vector3 point, int button)
	{
		std::cout << "ESTADO LANZANDO GRANADA" << "\n";

		if (button == TMouseAction::LEFT_CLICK)
		{
			Logic::MLanzarGranada *mLanzarGranada = new Logic::MLanzarGranada();
			mLanzarGranada->setOrdenGranada(ocultar);
			//_entity->emitMessage(mLanzarGranada);

			_selectionController->changeState(State::PLAYER_SELECTED);

		}	
		if (button == TMouseAction::RIGHT_CLICK)
		{

		}
	}

} // namespace Logic