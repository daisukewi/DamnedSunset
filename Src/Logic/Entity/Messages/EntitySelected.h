/**
@file EntitySelected.h

Contiene la declaraci�n del mensaje para avisar que se ha seleccionado una entidad.

@see Logic::IMessage

@author Daniel Flamenco
@date Enero, 2012
*/

#ifndef __Logic_EntitySelected_H
#define __Logic_EntitySelected_H

#include "Logic/Entity/Message.h"

#include "Logic/Entity/Entity.h"

namespace Logic
{
	/**
	Tipo de selecci�n
	*/
	namespace EntitySelectedMessage
	{
		enum SelectedType
		{
			PRIMARY,
			SECONDARY
		};
	}

	typedef EntitySelectedMessage::SelectedType SelectedType;
	/**
	Clase mensaje que se encargar� de avisar que se ha seleccionado una entidad.

	@author Daniel Flamenco
	@date Enero, 2012
	*/
	class MEntitySelected : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MEntitySelected();

		/**
		M�todo que establece la entidad que se ha seleccionado.

		@param entity Puntero a la entidad que se ha seleccionado.
		*/
		void setSelectedEntity(CEntity *entity);

		/**
		M�todo que devuelve la entidad que se ha seleccionado.

		@return Puntero a la entidad que se ha seleccionado.
		*/
		CEntity* getSelectedEntity();

		/**
		M�todo que devuelve el punto de contacto del raycast

		@return Punto de contacto del raycast
		*/
		Vector3 getPoint();

		/**
		M�todo que establece el punto de contacto del raycast

		@param point Punto de contacto del raycast
		*/
		void setPoint(Vector3 point);


		/**
		M�todo que establece  si el mensaje ha sido enviado desde la interfaz

		@param interface (true7/false)
		*/
		void setInterface(bool interface);


		/**
		M�todo que devuelve si el mensaje ha sido enviado desde la interfaz

		@return _interface
		*/
		bool getInterface();

		/**
		M�todo que establece el tipo de selecci�n

		@param selectedType
		*/
		void setSelectedType(SelectedType selectedType);

		/**
		M�todo que devuelve el tipo de selecci�n

		@return _selectedType
		*/
		SelectedType getSelectedType();
	protected:

		/**
		Atributo que contiene un puntero a la entidad que se ha seleccionado.
		*/
		CEntity *_selectedEntity;

		/**
		Atributo que contiene el punto de contacto del raycast
		*/
		Vector3 _point;

		/**
		Atributo que contiene si el mensaje ha sido enviado desde la interfaz
		*/
		bool _interface;

		SelectedType _selectedType;

	}; // class MEntitySelected

} // namespace Logic

#endif // __Logic_EntitySelected_H