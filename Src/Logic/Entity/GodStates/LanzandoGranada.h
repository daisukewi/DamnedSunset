/**
@file LanzandoGranada.h

Contiene la clase que representa al estado en el que el jugador esta lanzando una granada.

@see Logic::GodState.h

@author Isaac Gallarzagoitia
*/
#ifndef __Logic_LanzandoGranada_H
#define __Logic_LanzandoGranada_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Entity.h"

#include "Logic\Entity\GodStates\GodState.h"



namespace Logic
{
	/**
	Clase del estado LanzandoGraada
	<p>
	Esta clase se encarga de gestionar los clicks cuando se esta lanzando una granada
	@ingroup logicGroup

	@author Isaac Gallarzagoitia
	@date Febrero, 2012
*/
	class CLanzandoGranada : public IGodState
	{
	public:

		/**
		Constructor por defecto; 
		*/
		CLanzandoGranada(CSelectionController *component){_selectionController = component;}

		/**
		Destructor (virtual);
		*/
		virtual ~CLanzandoGranada() {}

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController.h
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button);


	protected:

	


	};
}

#endif