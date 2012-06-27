/**
@file DynamicMovement.cpp

Contiene distintas clases que heredan de IMovement y que 
implementan distintos tipos de movimiento din�mico.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#include "DynamicMovement.h"
#include "Server.h"
#include "Physics\Server.h"

namespace AI 
{

	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l devuelve los nuevos valores de aceleraci�n.
	*/
	void CDynamicSeek::move(unsigned int msecs, DynamicMovement& currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Seek (din�mico)
		// En _entity tenemos un puntero a la entidad.
		// En _maxLinearAccel tenemos la aceleraci�n m�xima que puede tener la entidad.
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n.
		currentProperties.linearAccel = _target - _entity->getPosition();
		if (currentProperties.linearAccel.squaredLength() > _maxLinearAccel2) {
			currentProperties.linearAccel.normalise();
			currentProperties.linearAccel *= _maxLinearAccel;
		}
	}
	/////////////////////////////////////////
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l devuelve los nuevos valores de aceleraci�n.
	*/
	void CDynamicArrive::move(unsigned int msecs, DynamicMovement &currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Arrive (din�mico).
		// En _entity tenemos un puntero a la entidad.
		// En _maxLinearSpeed tenemos la velocidad m�xima a la que se puede mover la entidad y 
		// en _maxLinearAccel la aceleraci�n m�xima.
		// Otras constantes �tiles son IMovement::SLOW_RADIUS (radio a partir del cual empezamos a frenar
		// para aproximarnos a un punto) y IMovement::ATTENUATION (tiempo que utilizamos para llegar al objetivo).
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n.
		Vector3 targetVelocity = (_target - _entity->getPosition());
		float distance = targetVelocity.length();
		float targetSpeed;
		if (distance >= IMovement::SLOW_RADIUS) 
			targetSpeed = _maxLinearSpeed;
		else 
			targetSpeed = distance * _maxLinearSpeed / IMovement::SLOW_RADIUS;
		
		targetVelocity /= distance;
		targetVelocity *= targetSpeed;
		currentProperties.linearAccel = targetVelocity - currentProperties.linearSpeed;
		currentProperties.linearAccel/= IMovement::ATTENUATION;
		if (currentProperties.linearAccel.squaredLength() > _maxLinearAccel2) {
			currentProperties.linearAccel.normalise();
			currentProperties.linearAccel *= _maxLinearAccel;
		}
	}
	/////////////////////////////////////////
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l devuelve los nuevos valores de aceleraci�n.
	*/
	void CDynamicAvoid::move(unsigned int msecs, DynamicMovement &currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Avoid (din�mico).
		// En _entity tenemos un puntero a la entidad.
		// En _maxLinearSpeed tenemos la velocidad m�xima a la que se puede mover la entidad y 
		// en _maxLinearAccel la aceleraci�n m�xima.
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n.
		Vector3 targetVelocity = (_target - _entity->getPosition());
		float distance = targetVelocity.length();
		float targetSpeed;
		if (distance >= IMovement::SLOW_RADIUS) 
			targetSpeed = _maxLinearSpeed;
		else 
			targetSpeed = distance * _maxLinearSpeed / IMovement::SLOW_RADIUS;
		
		targetVelocity /= distance;
		targetVelocity *= targetSpeed;
		currentProperties.linearAccel = targetVelocity - currentProperties.linearSpeed;
		currentProperties.linearAccel/= IMovement::ATTENUATION;

		//Vector3 impact;
		//currentProperties.linearAccel.normalise();
		//Ray disparo = Ray(_entity->getPosition(), currentProperties.linearAccel);
		//Logic::CEntity *entity = Physics::CServer::getSingletonPtr()->raycastGroup(disparo, &impact, 
		//	(Physics::TPhysicGroup)(Physics::TPhysicGroup::PG_CHARACTERS));

		Logic::CEntity* * entidadesColision;
		int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(), 100, entidadesColision);
		int i = 0;
		bool obstacle = false;
		while (i < numColisiones && !obstacle)
		{
			obstacle = Math::ProdEscalar(entidadesColision[i]->getPosition() - _entity->getPosition(), currentProperties.linearAccel) > 0;
			i++;
		}

		if (currentProperties.linearAccel.squaredLength() > _maxLinearAccel2) {
			currentProperties.linearAccel.normalise();
			currentProperties.linearAccel *= _maxLinearAccel;
		}
		
		if (obstacle)
		//	((impact - _entity->getPosition()).length() < currentProperties.linearSpeed.length()*70)
		{
			Matrix4 *rotation = new Matrix4(Math::Cos(0.5f),0,Math::Sin(0.5f),0,0,1,0,0,-Math::Sin(0.5f),0,Math::Cos(0.5f),0,0,0,0,1);
			currentProperties.linearAccel = rotation->operator*(currentProperties.linearAccel);
		}
		
		std::cout << "Destino: " << _target << "\n";
		std::cout << "Posici�n: " << _entity->getPosition() << "\n";
		std::cout << "Velocidad: " << currentProperties.linearAccel << "\n";
	}
}