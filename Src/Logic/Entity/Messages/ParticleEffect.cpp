/**
@file ParticleEffect.cpp

Contiene la implementación del mensaje enviado para indicar que se quiere mostrar un efecto de partículas

@author Alberto Ortega
@date Marzo, 2012
*/

#include "ParticleEffect.h"

namespace Logic
{
	MParticleEffect::MParticleEffect()
	{
		IMessage();

		_type = "MParticleEffect";
	
	} // MIsSelectable

	Vector3 MParticleEffect::getPoint()
	{
		return _point;
	}

	void MParticleEffect::setPoint(Vector3 point)
	{
		_point = point;
	}


} // namespace Logic