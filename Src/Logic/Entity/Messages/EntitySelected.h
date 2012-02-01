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

	protected:

		/**
		Atributo que contiene un puntero a la entidad que se ha seleccionado.
		*/
		CEntity *_selectedEntity;

		/**
		Atributo que contiene el punto de contacto del raycast
		*/
		Vector3 _point;

	}; // class MEntitySelected

} // namespace Logic

#endif // __Logic_EntitySelected_H