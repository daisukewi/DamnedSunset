/**
@file CameraControl.h

Contiene la declaraci�n del mensaje del control de c�mara.

@see Logic::IMessage

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_UbicarCamara_H
#define __Logic_UbicarCamara_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargar� de avisar a la c�mara que el usuario quiere hacer un movimiento.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class CUbicarCamara : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		CUbicarCamara();

		void setPosition(Vector3 pos) {_position = pos;}
		Vector3 getPosition() {return _position;}
	protected:

		/**
		Posicion que indicara a donde se tiene que mover la camara.
		*/
		Vector3 _position;

	}; // class CCameraControl

} // namespace Logic

#endif // __Logic_CameraControl_H