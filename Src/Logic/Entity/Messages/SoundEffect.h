/**
@file SoundEffect.h

Contiene la declaración del mensaje enviado para indicar que se quiere reporducir un efecto de sonido

@see Logic::IMessage

@author Alberto Ortega
@date Marzo, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_SoundEffect_H
#define __Logic_SoundEffect_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MSoundEffect : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MSoundEffect();


	protected:

	};



} // namespace Logic

#endif // __Logic_SoundEffect_H