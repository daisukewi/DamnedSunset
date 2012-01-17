#ifndef __Logic_CameraController_H
#define __Logic_CameraController_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{

	class CCameraController : public IComponent
	{
		DEC_FACTORY(CCameraController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CCameraController() : IComponent(), _up(false), _down(false), 
			_left(false), _right(false), _speed(0.05f) {}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity).

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se registra así mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y ratón.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se deregistra así mismo en el controlador del GUI para dejar de
		recibir las ordenes dadas a partir de los eventos de teclado y ratón.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando está andando o desplazándose lateralmente).

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		Método virtual que elige que mensajes son aceptados. Son válidos
		CAMERA_CONTROL.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

		/**
		Provoca que la entidad avance.
		*/
		void up();

		/**
		Provoca que la entidad retroceda.
		*/
		void down();

		/**
		Provoca que la entidad se desplace a la izquierda.
		*/
		void left();

		/**
		Provoca que la entidad se desplace a la derecha.
		*/
		void right();

		/**
		Provoca que la entidad pare el movimiento hacia delante.
		*/
		void stopUp();

		/**
		Provoca que la entidad pare el movimiento hacia atrás.
		*/
		void stopDown();

		/**
		Provoca que la entidad pare el movimiento hacia la izquierda.
		*/
		void stopLeft();

		/**
		Provoca que la entidad pare el movimiento hacia la derecha.
		*/
		void stopRight();

	protected:

		/**
		Atributo para saber si la entidad está avanzando.
		*/
		bool _up;

		/**
		Atributo para saber si la entidad está retrocediendo.
		*/
		bool _down;

		/**
		Atributo para saber si la entidad está desplazándose
		a la izquierda.
		*/
		bool _left;

		/**
		Atributo para saber si la entidad está desplazándose
		a la derecha.
		*/
		bool _right;

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;

	}; // class CCameraController

	REG_FACTORY(CCameraController);

} // namespace Logic

#endif // __Logic_CameraController_H
