/**
@file LUA_Message.h

LUA

Contiene el tipo de datos de un mensaje.

@author Alberto Ortega
*/
#ifndef __ScriptManager_LUA_Message_H
#define __ScriptManager_LUA_Message_H

#include <string>

#include "Logic/Maps/EntityID.h"

namespace ScriptManager
{
	/**
	Clase base de los mensajes que construirá LUA para enviar a C++ y a partir de los cuales se obtendrán los mensajes C++
	
	@ingroup scriptManagerGroup

	@author Alberto Ortega
	@date Abril, 2012
*/

	class LUA_IMessage 
	{

	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		LUA_IMessage() : _type(""),_entityTo(Logic::EntityID::UNASSIGNED) {

		}

		/**
		Destructor (virtual); en la clase base no hace nada.
		*/
		virtual ~LUA_IMessage() {

		}

		/**
		Método para obtener el tipo de mensaje.

		@return Un string indicando el tipo de mensaje.
		*/
		std::string getType() { return _type; }


		/**
		Mètodo para asignar la entidad a la que va dirigido el mensaje

		@param entity  entidada a la que va dirigido
		*/
		void setEntityTo(unsigned int entityTo);
	

		/**
		Método para obtener la entidad a la que va dirigido el mensaje
		*/
		unsigned int getEntityTo() {return _entityTo; }


		/**
		Método que implementará cada mensaje concreto en el que se construirá el mensaje C++ y se enviará
		*/
		virtual void send();

	protected:

		/**
		Tipo del mensaje. El string coincide con el nombre de la clase.
		*/
		std::string _type;

		/**
		Entidad a la que va dirigido el mensaje
		*/
		unsigned int _entityTo;

	}; // class IMessage

} // namespace Logic

#endif // __ScriptManager_LUA_Message_H
