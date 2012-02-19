/**
@file Building.h

Contiene la clase que representa el estado en el que se encuentra el SelectionController
cuando se está construyendo. 

@see Logic::GodState.h
@see Logic::BuilderController.h

@author Alberto Ortega
*/
#ifndef __Logic_Building_H
#define __Logic_Building_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Entity.h"

#include "Logic\Entity\GodStates\GodState.h"

namespace Logic
{
	/**
	Clase del estado Building
	<p>
	Contiene la clase que representa el estado en el que se encuentra el SelectionController
	cuando se está construyendo. Para ello, hace uso del componente BuilderController.
	@ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class CBuilding : public IGodState
	{
	public:

		/**
		Constructor por defecto; 
		*/
		CBuilding(CSelectionController *component){_selectionController = component;}

		/**
		Destructor (virtual);
		*/
		virtual ~CBuilding(){};

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button);


	protected:


	}; // class CBuilding

} // namespace Logic

#endif // __Logic_Building_H