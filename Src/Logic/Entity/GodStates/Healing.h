/**
@file Building.h

Contiene la clase que representa el estado en el que se encuentra el SelectionController
cuando se está curando

@see Logic::GodState.h
@see Logic::BuilderController.h

@author Alberto Ortega
*/
#ifndef __Logic_Healing_H
#define __Logic_Healing_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Entity.h"

#include "Logic\Entity\GodStates\GodState.h"

namespace Logic
{
	/**
	Clase del estado Healing
	<p>
	Contiene la clase que representa el estado en el que se encuentra el SelectionController
	cuando se tiene seleccionada la opción de curara a una entidad
	@ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class CHealing : public IGodState
	{
	public:

		/**
		Constructor por defecto; 
		*/
		CHealing(CSelectionController *component){_selectionController = component;}

		/**
		Destructor (virtual);
		*/
		virtual ~CHealing(){};

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button);


	protected:


	}; // class CHealing

} // namespace Logic

#endif // __Logic_Healing_H