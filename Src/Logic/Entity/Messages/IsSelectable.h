/**
@file IsSelectable.h

Contiene la declaración del mensaje enviado para preguntar a una entidad si es seleccionable

@see Logic::IMessage

@author Alberto Ortega
@date Enero, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_IsSelectable_H
#define __Logic_IsSelectable_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MIsSelectable : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MIsSelectable();


		/**
		Método que devuelve el punto de contacto del raycast

		@return Punto de contacto del raycast
		*/
		Vector3 getPoint();

		/**
		Método que establece el punto de contacto del raycast

		@param point Punto de contacto del raycast
		*/
		void setPoint(Vector3 point);

	protected:

		/**
		Atributo que contiene el punto de contacto del raycast
		*/
		Vector3 _point;
	};



} // namespace Logic

#endif // __Logic_IsSelectable_H