/**
@file DayCameraController.h

Contiene la declaraci�n del componente que controla el movimiento de la c�mara en la fase de d�a

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
//declaraci�n de la clase
namespace Logic 
{
	/**
	Clase del componente que se encarga de mover la c�mara por la escena en la fase de d�a

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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity).

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se registra as� mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y rat�n.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se deregistra as� mismo en el controlador del GUI para dejar de
		recibir las ordenes dadas a partir de los eventos de teclado y rat�n.
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		M�todo virtual que elige que mensajes son aceptados. Son v�lidos
		MCameraControl.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		M�todo virtual que procesa un mensaje.

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
		Provoca que la entidad pare el movimiento hacia delante y/o hacia atr�s.
		*/
		void stopUpDown();

		/**
		Provoca que la entidad pare el movimiento hacia la izquierda y/o hacia la derecha.
		*/
		void stopLeftRight();

		/**
		Provoca que la entidad se acerque o se aleje al personaje.

		@param wheel entero que indica el giro de la rueda del rat�n.
		*/
		void zoom(int wheel);

	protected:

		/**
		C�mara gr�fica.
		*/
		Graphics::CCamera *_graphicsCamera;

		/**
		Atributo para saber si la entidad est� avanzando con las teclas.
		*/
		bool _up;

		/**
		Atributo para saber si la entidad est� avanzando con el rat�n.
		*/
		bool _upMouse;

		/**
		Atributo para saber si la entidad est� retrocediendo con las teclas.
		*/
		bool _down;

		/**
		Atributo para saber si la entidad est� retrocediendo con el rat�n.
		*/
		bool _downMouse;

		/**
		Atributo para saber si la entidad est� desplaz�ndose
		a la izquierda con las teclas.
		*/
		bool _left;

		/**
		Atributo para saber si la entidad est� desplaz�ndose
		a la izquierda con el rat�n.
		*/
		bool _leftMouse;

		/**
		Atributo para saber si la entidad est� desplaz�ndose
		a la derecha con las teclas.
		*/
		bool _right;

		/**
		Atributo para saber si la entidad est� desplaz�ndose
		a la derecha con el rat�n.
		*/
		bool _rightMouse;

		/**
		Atributo para saber si el usuario est� moviendo la c�mara con rat�n.
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
		Posici�n de la entidad.
		*/
		Vector3 _bossPosition;


		/**
		Posici�n  donde debe de mirar la c�mara
		*/
		Vector3 _finalPosition;

		/**
		Movimiento adicional que debe hacer la c�mara por el pulsado de teclas o movimiento del rat�n
		*/
		Vector3 _movement;

		/**
		L�mite de distancia de movimiento del rat�n
		*/
		float _mouseDistance;

		/**
		Distancia m�xima entre el personaje y la c�mara cuando �ste se est� desplazando
		*/
		float _cameraDistance; 

		/**
		Valor para indicar la velocidad a la que se interpola la posici�n de la c�mara
		Cuanto m�s alto m�s despacio se mueve
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
		Indica la altura de la c�mara
		*/
		float _cameraHeight;

	}; // class CDayCameraController

	REG_FACTORY(CDayCameraController);

} // namespace Logic

#endif // __Logic_DayCameraController_H
