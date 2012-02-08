/**
@file GodState.h

Contiene la interfaz de la que heredar�n los dem�s estados usados para controlar el estado del sistema encargado de gestionar los clicks del rat�n

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
	Esta clase no contiene ning�n atributo, de forma que son las clases hijas
	las que tendr�n los atributos concretos del tipo de mensaje que se quiera mandar.
	
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
		Gestiona los clicks que le ser�n enviados desde el componente SelectionController.h
		@param entity entidad a la que se ha hecho click
		@param point punto donde se ha hecho click
		@param button bot�n del rat�n con el que se ha hecho click*/
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
		*Almacena el bot�n del rat�n con el que se ha hecho click
		*/
		int _button;

	}; // class IGodstate

} // namespace Logic

#endif // __Logic_GodState_H

