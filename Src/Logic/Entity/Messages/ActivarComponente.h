/**
@file ActivarComponente.h

Contiene la declaración del mensaje para activar un componente

@see Logic::IMessage

@author Isaac Gallarzagoitia
@date Marzo, 2012
*/

#ifndef __Logic_ActivarComponente_H
#define __Logic_ActivarComponente_H

#include "Logic/Entity/Message.h"


namespace Logic 
{

	/**
	Clase mensaje que avisa a la entidad fisica para que aplique una fuerza.
	*/
	class MActivarComponente : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MActivarComponente();

		bool getActivar() { return _activar;}
		void setActivar(bool activar) {_activar = activar;}

		std::string getNombreComponent() { return _nombreComponente;}
		void setNombreComponente( std::string s) { _nombreComponente = s;}
	protected:
		bool _activar;
		std::string _nombreComponente;
	};

}

#endif