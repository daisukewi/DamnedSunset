/**
@file EmplaceBuilding.h

Contiene la declaración del mensaje para construir edificios.

@see Logic::IMessage

@author Daniel Flamenco
@date Enero, 2012
*/

#ifndef __Logic_EmplaceBuilding_H
#define __Logic_EmplaceBuilding_H

#include "Logic/Entity/Message.h"

namespace Logic
{

	/**
	Tipo de acción a realizar cuando se envía un mensaje de construir.
	*/
	namespace BuildingMessage
	{
		enum BuildingAction
		{
			START_BUILDING,
			CANCEL_BUILDING,
			EMPLACE_BUILDING
		};
	}

	typedef BuildingMessage::BuildingAction BuildingAction;

	/**
	Clase mensaje que se encargará de avisar a la entidad jugador, de cuando hay que empezar
	a construir un edificio, cancelar la construcción o fijar el edificio en la posición
	determinada.

	@author Daniel Flamenco
	@date Enero, 2012
	*/
	class MEmplaceBuilding : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MEmplaceBuilding();

		/**
		Método que establece la acción que se quiere realizar con este mensaje.

		@param action Tipo de la acción a realizar.
		*/
		void setAction(BuildingAction action);

		/**
		Método que devuelve la acción que se quiere realizar con este mensaje.

		@return Tipo de la acción a realizar.
		*/
		BuildingAction getAction();

		/**
		Método que establece el tipo de edificio que se quiere construir.

		@param action Tipo de edificio a construir.
		*/
		void setBuildingType(std::string buildingType);

		/**
		Método que devuelve el tipo de edificio que se quiere construir.

		@return Tipo de edificio a construir.
		*/
		std::string getBuildingType();

	protected:

		/**
		Atributo que indica la acción que se va a realizar con este mensaje.
		*/
		BuildingAction _action;

		/**
		Atributo que indica el tipo de edificio a construir.
		*/
		std::string _buildingType;

	}; // class MEmplaceBuilding

} // namespace Logic

#endif // __Logic_EmplaceBuilding_H