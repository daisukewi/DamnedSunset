/**
@file DayCameraController.h

Contiene la declaración del componente que controla el movimiento de la cámara en la fase de día

@see Logic::CCamera
@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_DayCameraController_H
#define __Logic_DayCameraController_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/Math.h"
#include "Graphics/Camera.h"
//declaración de la clase
namespace Logic 
{
	/**
	Clase del componente que se encarga de mover la cámara por la escena en la fase de día

	@author Alberto Ortega
	@date Mayo, 2012
*/
	class CDayCameraController : public IComponent
	{
		DEC_FACTORY(CDayCameraController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CDayCameraController() : IComponent(), _graphicsCamera(0), _up(false), _upMouse(false), _down(false), _downMouse(false), 
			_left(false), _leftMouse(false), _right(false), _rightMouse(false), _mouse(false), _speed(0.15f) {}
		
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
		MCameraControl.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);

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
		Provoca que la entidad pare el movimiento hacia delante y/o hacia atrás.
		*/
		void stopUpDown();

		/**
		Provoca que la entidad pare el movimiento hacia la izquierda y/o hacia la derecha.
		*/
		void stopLeftRight();

		/**
		Provoca que la entidad se acerque o se aleje al personaje.

		@param wheel entero que indica el giro de la rueda del ratón.
		*/
		void zoom(int wheel);

	protected:

		/**
		Cámara gráfica.
		*/
		Graphics::CCamera *_graphicsCamera;

		/**
		Atributo para saber si la entidad está avanzando con las teclas.
		*/
		bool _up;

		/**
		Atributo para saber si la entidad está avanzando con el ratón.
		*/
		bool _upMouse;

		/**
		Atributo para saber si la entidad está retrocediendo con las teclas.
		*/
		bool _down;

		/**
		Atributo para saber si la entidad está retrocediendo con el ratón.
		*/
		bool _downMouse;

		/**
		Atributo para saber si la entidad está desplazándose
		a la izquierda con las teclas.
		*/
		bool _left;

		/**
		Atributo para saber si la entidad está desplazándose
		a la izquierda con el ratón.
		*/
		bool _leftMouse;

		/**
		Atributo para saber si la entidad está desplazándose
		a la derecha con las teclas.
		*/
		bool _right;

		/**
		Atributo para saber si la entidad está desplazándose
		a la derecha con el ratón.
		*/
		bool _rightMouse;

		/**
		Atributo para saber si el usuario está moviendo la cámara con ratón.
		*/
		bool _mouse;

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;

		/**
		Entidad a la que debemos mirar siempre.
		*/
		CEntity* _bossEntity;

		/**
		Posición de la entidad.
		*/
		Vector3 _bossPosition;


		/**
		Posición  donde debe de mirar la cámara
		*/
		Vector3 _finalPosition;

		/**
		Movimiento adicional que debe hacer la cámara por el pulsado de teclas o movimiento del ratón
		*/
		Vector3 _movement;

		/**
		Límite de distancia de movimiento del ratón
		*/
		float _mouseDistance;

		/**
		Distancia máxima entre el personaje y la cámara cuando éste se está desplazando
		*/
		float _cameraDistance; 

		/**
		Valor para indicar la velocidad a la que se interpola la posición de la cámara
		Cuanto más alto más despacio se mueve
		*/
		float _cameraVelocity;

		/**
		Valor que indica a que velocidad de zoom
		*/
		float _zoomVelocity;

		/**
		Valor del scroll
		*/
		int _scrollValue;

		/**
		Indica si se ha hecho scroll
		*/
		bool _scroll;

		/**
		Indica la altura de la cámara
		*/
		float _cameraHeight;

	}; // class CDayCameraController

	REG_FACTORY(CDayCameraController);

} // namespace Logic

#endif // __Logic_DayCameraController_H
