/**
@file AplicarFuerza.h

Contiene la declaración del mensaje para aplicar una fuerza sobre una entidad fisica

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Marzo, 2012
*/

#ifndef __Logic_AplicarVelocidad_H
#define __Logic_AplicarVelocidad_H

#include "Logic/Entity/Message.h"

#include "Physics/PhysicModelSimple.h"

namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad fisica para que aplique una fuerza.
	*/
	class MAplicarVelocidad : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MAplicarVelocidad();

		void setVelocity(float x, float y, float z) {_velocity = NxVec3(x,y,z);}
		NxVec3 getVelocity() {return _velocity;}

	protected:
		NxVec3 _velocity;
	};

}

#endif