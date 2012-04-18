/**
@file SetEmpujarPropiedades.h


@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Abril, 2012
*/

#ifndef __Logic_SetEmpujarPropiedades_H
#define __Logic_SetEmpujarPropiedades_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad fisica para que aplique una fuerza.
	*/
	class MSetEmpujarPropiedades : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MSetEmpujarPropiedades();

		void setDirection(float x, float y, float z) {_direction = Vector3(x,y,z);}
		Vector3 getDirection() {return _direction;}
		float getTime() {return _time;}
		void setTime(float t) {_time = t;}
		float getDistanciaPorSegundo() {return _distanciaPorSegundo;}
		void setDistanciaPorSegundo(float d) {_distanciaPorSegundo = d;}

	protected:
		Vector3 _direction;
		float _time;
		float _distanciaPorSegundo;
	};

}

#endif