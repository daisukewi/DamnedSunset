/**
@file KinematicMovement.cpp

Contiene distintas clases que heredan de IMovement y que 
implementan distintos tipos de movimiento cinem�ticos.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#include "KinematicMovement.h"
#include "Server.h"
#include "Physics\Server.h"

namespace AI 
{
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l se devuelven los nuevos valores de velocidad.
	*/
	void CKinematicSeek::move(unsigned int msecs, DynamicMovement& currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Seek (cinem�tico)
		// En _entity tenemos un puntero a la entidad
		// En _maxLinearSpeed tenemos la velocidad m�xima a la que se puede mover la entidad
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n
		currentProperties.linearSpeed = _target - _entity->getPosition();
		if (currentProperties.linearSpeed.length() > _maxLinearSpeed) {
			currentProperties.linearSpeed.normalise();
			currentProperties.linearSpeed *= _maxLinearSpeed;
		}
	}
	/////////////////////////////////////////
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l se devuelven los nuevos valores de velocidad.
	*/
	void CKinematicArrive::move(unsigned int msecs, AI::IMovement::DynamicMovement &currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Arrive (cinem�tico)
		// En _entity tenemos un puntero a la entidad
		// En _maxLinearSpeed tenemos la velocidad m�xima a la que se puede mover la entidad.
		// IMovement::ATTENUATION nos da el tiempo que utilizamos para llegar al objetivo.
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n
		currentProperties.linearSpeed = (_target - _entity->getPosition());
		currentProperties.linearSpeed /= IMovement::ATTENUATION;
		if (currentProperties.linearSpeed.squaredLength() > _maxLinearSpeed2) {
			currentProperties.linearSpeed.normalise();
			currentProperties.linearSpeed *= _maxLinearSpeed;
		}
	}
	/////////////////////////////////////////
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l se devuelven los nuevos valores de velocidad.
	*/
	void CKinematicAlignToSpeed::move(unsigned int msecs, DynamicMovement& currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento AlignToSpeed.
		// En _entity tenemos un puntero a la entidad.
		// En _maxAngularSpeed tenemos la velocidad m�xima a la que puede girar la entidad.
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n.
		// Puede ser �til usar el m�todo IA::CServer::correctAngle, que nos sirve para asegurarnos de que, despu�s
		// de restar dos �ngulos, el resultado se mantiene entre -PI y PI.
		currentProperties.angularSpeed = (atan2(-currentProperties.linearSpeed.x, -currentProperties.linearSpeed.z) - _entity->getYaw());
		currentProperties.angularSpeed = CServer::correctAngle(currentProperties.angularSpeed);
		currentProperties.angularSpeed /= IMovement::ATTENUATION;
		if (abs(currentProperties.angularSpeed) > _maxAngularSpeed) {
			currentProperties.angularSpeed = Ogre::Math::Sign(currentProperties.angularSpeed) * _maxAngularSpeed;
		}
	}
	/////////////////////////////////////////
	/**
	Efect�a el movimiento.
		
	@param msecs Tiempo que dura el movimiento.
	@param currentProperties Par�metro de entrada/salida donde se reciben las velocidades actuales y 
	en �l se devuelven los nuevos valores de velocidad.
	*/
	void CKinematicAvoid::move(unsigned int msecs, DynamicMovement& currentProperties)
	{
		assert(_entity);
		// Implementar el movimiento Avoid (cinem�tico)
		// En _entity tenemos un puntero a la entidad
		// En _maxLinearSpeed tenemos la velocidad m�xima a la que se puede mover la entidad
		// currentProperties es un par�metro de entrada/salida en el que se recibe las velocidades/aceleraciones
		// actuales y se modifica con los nuevos valores de velocidad/aceleraci�n

		currentProperties.linearSpeed = _target - _entity->getPosition();
		float angle = 0.5f;
		_time += msecs;
		if (_time >= 700)
		{
			Logic::CEntity* * entidadesColision;
			int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(), 100, entidadesColision);
			int i = 0;
			_obstacle = false;
			while (i < numColisiones && !_obstacle)
			{
				Vector3 toObstacle = entidadesColision[i]->getPosition() - _entity->getPosition();
				_obstacle = Math::ProdEscalar(toObstacle, currentProperties.linearSpeed) > 0
					&& currentProperties.linearSpeed.squaredLength() > toObstacle.squaredLength();
				// Vemos si la entidad obst�culo est� a nuestra izquierda o a nuestra derecha.
				// Si est� a la izquierda y orientada hacia nuestro camino giramos a la derecha.
				// Si est� a la derecha y orientada hacia nuestro camino giramos a la izquierda.
				if (Math::ProdEscalar(toObstacle, Vector3(currentProperties.linearSpeed.z, 
					currentProperties.linearSpeed.y, -currentProperties.linearSpeed.x)) > 0)
				{
					_obstacle &= (Math::AnglePos(_entity->getYaw()) - Math::AnglePos(entidadesColision[i]->getYaw()) > 0
						|| Math::AnglePos(_entity->getYaw()) - Math::AnglePos(entidadesColision[i]->getYaw()) < -Math::PI);
					if (_obstacle)
					{
						_girarDcha = true;
					}
				}
				else
				{
					_obstacle &= (Math::AnglePos(_entity->getYaw()) - Math::AnglePos(entidadesColision[i]->getYaw()) < 0
						|| Math::AnglePos(_entity->getYaw()) - Math::AnglePos(entidadesColision[i]->getYaw()) > Math::PI);
					if (_obstacle)
						_girarDcha = false;
				}
				i++;
			}
		/*	if (_obstacle &&
				Math::ZProdVect(entidadesColision[i-1]->getPosition() - _entity->getPosition(), currentProperties.linearSpeed) > 0)
			{
				angle *= -1;
			}*/
			_time = 0;
		}

		if (_obstacle)
		{
			if (_girarDcha)
				angle *= -1;
			Matrix4 *rotation = new Matrix4(Math::Cos(angle),0,Math::Sin(angle),0,0,1,0,0,-Math::Sin(angle),0,Math::Cos(angle),0,0,0,0,1);
			currentProperties.linearSpeed = rotation->operator*(currentProperties.linearSpeed);
		}
		if (currentProperties.linearSpeed.length() > _maxLinearSpeed) {
			currentProperties.linearSpeed.normalise();
			currentProperties.linearSpeed *= _maxLinearSpeed;
		}
	}
} //namespace AI
