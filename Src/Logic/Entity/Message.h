/**
@file Message.h

Contiene el tipo de datos de un mensaje.

@see Logic::TMessage

@author Alberto Plaza
*/
#ifndef __Logic_Message_H
#define __Logic_Message_H

#include <string>

namespace Logic
{
	/**
	Clase base de los mensajes que se mandarán a las entidades en todo momento.
	<p>
	Esta clase no contiene ningún atributo, de forma que son las clases hijas
	las que tendrán los atributos concretos del tipo de mensaje que se quiera mandar.
	<p>
	Esta clase es la que implementa el funcionamiento del puntero inteligente ya que es
	una función que deben tener todos los mensajes.
	
	@ingroup logicGroup

	@author Alberto Plaza
	@date Enero, 2012
*/

	/*Comprobacion para ver q se crean y se destrullen el mismo numero de mensajes,
	descomentar estas 2 variables estaticas, el constructor y el destructor para comprobarlo
	*/
	//static int numMensajesCreados = 0;
	//static int numMensajesDestruidos = 0;

	class IMessage 
	{

	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		IMessage() : _numPtr(0), _type("") {
			//printf("\nNumMensajes: %d", numMensajesCreados - numMensajesDestruidos); ++numMensajesCreados;
		}

		/**
		Destructor (virtual); en la clase base no hace nada.
		*/
		virtual ~IMessage() {
			//++numMensajesDestruidos;
		}

		/**
		Añade una referencia al número de referencias.
		*/
		void addPtr() { _numPtr++; }

		/**
		Quita una referencia al número de referencias y si es cero o menos
		se destruye el mensaje.
		*/
		void removePtr();

		/**
		Método para obtener el tipo de mensaje.

		@return Un string indicando el tipo de mensaje.
		*/
		std::string getType() { return _type; }

	protected:

		/**
		Contador del número de referencias que apuntan a este mensaje.
		*/
		int _numPtr;

		/**
		Tipo del mensaje. El string coincide con el nombre de la clase.
		*/
		std::string _type;

	}; // class IMessage

} // namespace Logic

#endif // __Logic_Message_H
