/**
@file Free.h

Contiene la clase que representará al estado en el que no se encuentra ninguna entidad del escenario seleccionada

@see Logic::GodState.h

@author Alberto Ortega
*/
#ifndef __Logic_CFree_H
#define __Logic_CFree_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Entity.h"

#include "Logic\Entity\GodStates\GodState.h"

namespace Logic
{
	/**
	Clase del estado Free
	<p>
	Esta clase se encarga de gestionar los clicks cuando ninguna entidad del escenario está seleccionada

	@ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class CFree : public IGodState
	{
	public:

		/**
		Constructor por defecto; 
		*/
		CFree(IComponent *component){_selectionController = component;}

		/**
		Destructor (virtual);
		*/
		virtual ~CFree() {}

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController.h
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button);


	protected:
	


	}; // class CFree

} // namespace Logic

#endif // __Logic_CFree_H

