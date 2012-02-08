/**
@file GodState.h

Contiene la interfaz de la que heredarán los demás estados usados para controlar el estado del sistema encargado de gestionar los clicks del ratón

@see Logic::SelectionController.h

@author Alberto Ortega
*/
#ifndef __Logic_GodState_H
#define __Logic_GodState_H

#include <string>

#include "BaseSubsystems/Math.h"

#include "Logic\Entity\Component.h"
#include "Logic\Entity\Entity.h"

namespace Logic
{
	/**
	namespace para los tipos de estado que va a haber
	*/
	namespace State{
			enum TState {FREE, PLAYER_SELECTED, BUILD_SELECTED};
	}

	/**
	Clase base de los estados 
	<p>
	Esta clase no contiene ningún atributo, de forma que son las clases hijas
	las que tendrán los atributos concretos del tipo de mensaje que se quiera mandar.
	
	@ingroup logicGroup

	@author Alberto Ortega
	@date Febrero, 2012
*/
	class IGodState 
	{
	public:

		/**
		Constructor por defecto; 
		*/
		IGodState(){};

		/**
		Destructor (virtual); en la clase base no hace nada.
		*/
		virtual ~IGodState() {}

		/**
		Gestiona los clicks que le serán enviados desde el componente SelectionController.h
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click
		@param button botón del ratón con el que se ha hecho click*/
		virtual void click(CEntity* entity, Vector3 point, int button) = 0;

	protected:
		/*
		*Almacena el componente encaragado de gestionar los estados (SelectionController)
		*/
		IComponent* _selectionController;


		/*
		*Almacena la entidada a la que se ha hecho click
		*/
		CEntity* _entity;


		/**
		*Almacena el punto del mundo donde se ha hecho click
		*/
		Vector3 _point;

		/**
		*Almacena el botón del ratón con el que se ha hecho click
		*/
		int _button;

	}; // class IGodstate

} // namespace Logic

#endif // __Logic_GodState_H

