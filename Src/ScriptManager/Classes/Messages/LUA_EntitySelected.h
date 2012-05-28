/**
@file LUA_EntitySelected.h

Contiene la declaración del mensaje de entidad seleccionada que sirve como intermediario entre lua y C++.

@author Luis Mendoza
@date Mayo, 2012
*/

#ifndef __Logic_LUA_EntitySelected_H
#define __Logic_LUA_EntitySelected_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de seleccionar una entidad.

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
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

		/**
		Establece en el mensaje la entidad seleccionada.
		*/
		void setSelectedEntity(std::string entity);

		/**
		Devuelve la entidad almacenada en el mensaje.
		*/
		std::string getSelectedEntity();

		/**
		Establece en el mensaje si el mensaje ha sido enviado desde la interfaz.
		*/
		void setInterface(bool interface);

		/**
		Devuelve si el mensaje ha sido enviado desde la interfaz.
		*/
		bool getInterface();

	protected:

		/**
		Atributo que indica la entidad seleccionada.
		*/
		std::string _selectedEntity;

		/**
		Atributo que contiene si el mensaje ha sido enviado desde la interfaz
		*/
		bool _interface;

	}; // class LUA_MEntitySelected

} // namespace Logic

#endif // __Logic_LUA_EntitySelected_H