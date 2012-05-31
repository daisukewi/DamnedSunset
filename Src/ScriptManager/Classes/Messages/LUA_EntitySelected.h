/**
@file LUA_EntitySelected.h

Contiene la declaraci�n del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Luis Mendoza
@date Mayo, 2012
*/

#ifndef __Logic_LUA_EntitySelected_H
#define __Logic_LUA_EntitySelected_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargar� de seleccionar una entidad.

	@author Luis Mendoza
	@date Mayo, 2012
	*/
	class LUA_MEntitySelected : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MEntitySelected();

		/**
		Implementaci�n del m�todo send heredado de la clase LUA_IMessage
		*/
		virtual void send();

		/**
		Establece en el mensaje la entidad seleccionada.
		*/
		void setSelectedEntity(std::string entity);

		/**
		Establece en el mensaje la entidad seleccionada.
		*/
		void setSelectedEntity(unsigned int entityID);

	protected:

		/**
		Atributo que indica la entidad seleccionada.
		*/
		std::string _selectedEntity;

		unsigned int _selectedEntityID;

	}; // class LUA_MEntitySelected

} // namespace Logic

#endif // __Logic_LUA_EntitySelected_H