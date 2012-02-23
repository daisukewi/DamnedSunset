/**
@file SetTransform.h

Contiene la declaración del mensaje de aplicar una transformación a una entidad.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_SetTransform_H
#define __Logic_SetTransform_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de avisar a una entidad que hay que aplicar una transformación a su matriz de transformación.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MSetTransform : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MSetTransform();

		/**
		Método que establece en el mensaje la matriz de transformación.

		@param transform Matriz de transformación que debe guardar el mensaje.
		*/
		void setTransform(Matrix4 transform);

		/**
		Método que devuelve la matriz de transformación guardada en el mensaje.

		@return La matriz de transformación guardada en el mensaje.
		*/
		Matrix4 getTransform();

		/**
		Método que establece en el mensaje si se tiene que forzar la transformación.
		*/
		void setForce(bool force);

		/**
		Método que devuelve si se tiene que forzar la transformación.
		*/
		bool getForce();

	protected:

		/**
		Atributo que indica la matriz de transformación que hay que aplicar a la entidad receptora.
		*/
		Matrix4 _transform;

		/**
		Atributo que indica (sobre todo para la física) que esta transformación
		se tiene que forzar su aplicación.
		*/
		bool _force;

	}; // class MSetTransform

} // namespace Logic

#endif // __Logic_SetTransform_H