/**
@file SteeringMovement.h

Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cin�ticos o din�micos.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_SteeringMovement_H
#define __Logic_SteeringMovement_H

#include "Logic/Entity/Component.h"
#include "AI/Movement.h"
#include "AI/Server.h"
#include "AI/KinematicMovement.h"

namespace Logic 
{
	/**
	Componente que se encarga de trasladar una entidad de un punto a otro
	usando SteeringMovements. 
	Acepta mensajes MMoveSteering. Los par�metros relevantes del mensaje
	son el _vector, que indica el destino del movimiento, y el _int que indica 
	el tipo de movimiento (ver los tipos en IMovement).
	*/
	class CSteeringMovement : public IComponent
	{
		DEC_FACTORY(CSteeringMovement);

	public:
		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSteeringMovement() : IComponent(), _arrived(true), _maxLinearSpeed(0.05f), _maxAngularSpeed(0.01f),
			_maxLinearAccel(0.001f), _maxAngularAccel(0.001f), _currentMovement(0), 
			_currentMovementType(AI::IMovement::MOVEMENT_NONE), _yaw(0) { };
		/**
		Destructor
		*/
		~CSteeringMovement(void);
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa los atributos
		speed, angularSpeed, accel y angularAccel, que indican los valores m�ximos 
		de velocidad y aceleraci�n lineales y angulares.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);
		/**
		Este componente s�lo acepta mensajes MMoveSteering.
		*/
		virtual bool accept(IMessage *message);
		/**
		Si se recibe un mensaje MMoveSteering, almacena el vector como 
		destino del movimiento y el tipo de movimiento.
		*/
		virtual void process(IMessage *message);


	private:
		/** 
		Valores m�ximos de velocidades y aceleraciones.
		*/
		float _maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel, _tolerance;
		/**
		Este campo indica si se ha alcanzado el objetivo
		*/
		bool _arrived;
		/**
		Destino del movimiento.
		*/
		Vector3 _currentTarget, _target;
		/**
		Tipo de movimiento.
		*/
		int _currentMovementType, _movType;
		/**
		Instancia del movimiento actual.
		*/
		AI::IMovement* _currentMovement;
		/**
		Instancia de un movimiento de giro que se utilizar� para mantener la direcci�n.
		*/
		AI::IMovement* _yaw;
		/**
		Propiedades actuales del movimiento. En esta variable se almacenan las velocidades actuales, que 
		ser�n consultadas por los movimientos din�micos */
		AI::IMovement::DynamicMovement _currentProperties;

		/**
		Env�a un mensaje para cambiar la animaci�n actual.

		@param animation Nueva animaci�n.
		*/
		void sendAnimationMessage(std::string animation);

		void changeExtraVelocity(float velocity);
		/**
		Indica la velocidad extra que tendra para llegar al destino en un movimiento concreto
		**/
		float _extraVelocity;
		/**
		Tiempo que le falta para poder volver a usar la velocidad extra
		*/
		int _coolDownExtraVelocity;
		/**
		Tiempo que tardara en poder volver a usar la velocidad extra
		*/
		int _coolDownCarga;
		/**
		Tiempo que tardara en poder volver a usar la velocidad extra
		*/
		int _duracionCarga;
	};

	REG_FACTORY(CSteeringMovement);

} //namespace Logic

#endif //__Logic_SteeringMovement_H
