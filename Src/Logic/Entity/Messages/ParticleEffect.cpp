/**
@file ParticleEffect.cpp

Contiene la implementaci�n del mensaje enviado para indicar que se quiere mostrar un efecto de part�culas

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