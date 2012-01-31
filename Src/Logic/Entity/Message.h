/**
@file Message.h

Contiene el tipo de datos de un mensaje.

@see Logic::TMessage

@author David Llansó García
*/
#ifndef __Logic_Message_H
#define __Logic_Message_H

#include <string>

#include "BaseSubsystems/Math.h"

// Predeclaraciones
namespace Logic {
	class CEntity;
};

namespace Logic
{
	/**
	Namespace para los tipos de mensajes posibles.
	*/
	namespace Message
	{
		enum TMessageType
		{
			UNASSIGNED = 0xFFFFFFFF,
			SET_TRANSFORM, // @MENSAJES
			/*SELECTABLE,
			ENTITY_SELECTED,*/
		};
	}

	/**
	Tipo copia para los mensajes. Por simplicidad.
	*/
	typedef Message::TMessageType TMessageType;

	/**
	Contiene el tipo de datos de un mensaje. Tiene una serie de
	atributos genéricos que se interpretarán en función del tipo 
	de mensaje.
	<p>
	@remarks <b>¡¡ESTO NO ES ESCALABLE!!</b> En tu proyecto esto 
	debería ser cambiado.
	Lo suyo sería tener una clase CMesage base y luego clases que
	especializasen a ésta con los atributos necesarios para el 
	mensaje concreto en vez de tener una serie de atributos
	genéricos como es esta estructura que deben de ser interpretados
	externamente en función del tipo de mensaje.
	
    @ingroup logicGroup
    @ingroup entityGroup

	@author David Llansó García
	@date Julio, 2010
    @ingroup grupoEntidad
	*/
	typedef struct
	{
		/**
		Tipo del mensaje.
		*/
		TMessageType _type;

		/**
		Atributo para almacenar una matriz de transformación.
		*/
		Matrix4 _transform;
		
		/**
		Atributo para almacenar un valor int.
		*/
		int _int;

		/**
		Atributo para almacenar un valor float.
		*/
		float _float;
		
		/**
		Atributo para almacenar un valor booleano.
		*/
		bool _bool;
		
		/**
		Atributo para almacenar un string.
		*/
		std::string _string;

		/**
		Atributo para almacenar un vector.
		*/
		Vector3 _vector3;

		/**
		Atributo para almacenar un vector.
		*/
		Vector3 *_pointvector3;

		/**
		Atributo para almacenar una entidad.
		*/
		CEntity *_entity;

		/**
		Atributo para almacenar un vecotr de bidimensioanl
		*/
		Vector2 _vector2;

	} TMessage;

	/*namespace Message
	{*/

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
		class IMessage 
		{
		public:

			/**
			Constructor por defecto; en la clase base no hace nada.
			*/
			IMessage(std::string messageType = "") : _numPtr(0), _type(messageType) {}

			/**
			Destructor (virtual); en la clase base no hace nada.
			*/
			virtual ~IMessage() {}

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

	//} // namespace Message

} // namespace Logic

#endif // __Logic_Message_H
