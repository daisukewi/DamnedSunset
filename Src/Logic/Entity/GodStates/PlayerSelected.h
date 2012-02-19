/**
@file PlayerSelected.h

Contiene la clase que representará al estado en el que no se encuentra ninguna entidad del escenario seleccionada

@see Logic::GodState.h

@author Alberto Ortega
*/
#ifndef __Logic_PlayerSelected_H
#define __Logic_PlayerSelected_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Entity.h"

#include "Logic\Entity\GodStates\GodState.h"



namespace Logic
{
	/**
	Clase del estado PlayerSelected
	<p>
	Esta clase se encarga de gestionar los clicks cuando uno de los jugadores está seleccionado
	@ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class CPlayerSelected : public IGodState
	{
	public:

		/**
		Constructor por defecto; 
		*/
		CPlayerSelected(CSelectionController *component){_selectionController = component;}

		/**
		Destructor (virtual);
		*/
		virtual ~CPlayerSelected() {}

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController.h
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button);


	protected:

	


	}; // class CPlayerSelected

} // namespace Logic

#endif // __Logic_PlayerSelected_h