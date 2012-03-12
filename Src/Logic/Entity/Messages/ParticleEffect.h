/**
@file ParticleEffect.h

Contiene la declaración del mensaje enviado para indicar que se quiere mostrar un efecto de partículas

@see Logic::IMessage

@author Alberto Ortega
@date Marzo, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_ParticleEffect_H
#define __Logic_ParticleEffect_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MParticleEffect : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MParticleEffect();


		/**
		Método que devuelve el punto donde se muestra el efecto de partículas

		@return punto donde se muestra el efecto de partículas
		*/
		Vector3 getPoint();

		/**
		Método que establece el punto donde se muestra el efecto de partículas

		@param point punto donde se muestra el efecto de partículas
		*/
		void setPoint(Vector3 point);

	protected:

		/**
		Atributo que contiene el punto donde se quiere mostrar el efecto de partículas
		*/
		Vector3 _point;
	};



} // namespace Logic

#endif // __Logic_ParticleEffect_H