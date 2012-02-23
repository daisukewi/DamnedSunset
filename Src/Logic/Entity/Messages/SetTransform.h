/**
@file SetTransform.h

Contiene la declaraci�n del mensaje de aplicar una transformaci�n a una entidad.

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
	Clase mensaje que se encargar� de avisar a una entidad que hay que aplicar una transformaci�n a su matriz de transformaci�n.

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
		M�todo que establece en el mensaje la matriz de transformaci�n.

		@param transform Matriz de transformaci�n que debe guardar el mensaje.
		*/
		void setTransform(Matrix4 transform);

		/**
		M�todo que devuelve la matriz de transformaci�n guardada en el mensaje.

		@return La matriz de transformaci�n guardada en el mensaje.
		*/
		Matrix4 getTransform();

		/**
		M�todo que establece en el mensaje si se tiene que forzar la transformaci�n.
		*/
		void setForce(bool force);

		/**
		M�todo que devuelve si se tiene que forzar la transformaci�n.
		*/
		bool getForce();

	protected:

		/**
		Atributo que indica la matriz de transformaci�n que hay que aplicar a la entidad receptora.
		*/
		Matrix4 _transform;

		/**
		Atributo que indica (sobre todo para la f�sica) que esta transformaci�n
		se tiene que forzar su aplicaci�n.
		*/
		bool _force;

	}; // class MSetTransform

} // namespace Logic

#endif // __Logic_SetTransform_H