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
		MEntitySelected() : IMessage("MEntitySelected") {};

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

	protected:

		/**
		Atributo que contiene un puntero a la entidad que se ha seleccionado.
		*/
		CEntity *_selectedEntity;


	}; // class MEntitySelected

} // namespace Logic

#endif // __Logic_EntitySelected_H