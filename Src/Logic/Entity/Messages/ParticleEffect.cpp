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
		_altura = 0;
		_orientation.x = 0; _orientation.y = 0; _orientation.z = 0;
		_static= false;
	
	} // MIsSelectable

	Vector3 MParticleEffect::getPoint()
	{
		return _point;
	}

	void MParticleEffect::setPoint(Vector3 point)
	{
		_point = point;
	}

	std::string MParticleEffect::getEffect()
	{
		return _effect;
	}

	void MParticleEffect::setEffect(std::string effect)
	{
		_effect = effect;
	}

	void MParticleEffect::setOrientation(Vector4 &orientation)
	{
		_orientation = orientation;
	}

	Vector4 MParticleEffect::getOrientation()
	{
		return _orientation;
	}

	void MParticleEffect::setAltura(float altura)
	{
		_altura = altura;
	}

	float MParticleEffect::getAltura()
	{
		return _altura;
	}

	bool MParticleEffect::getStatic()
	{
		return _static;
	}

	void MParticleEffect::setStatic(bool statc)
	{
		_static = statc;
	}



} // namespace Logic