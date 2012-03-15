/**
@file CameraController.h

Contiene la declaraci�n del componente que controla el movimiento de la c�mara.

@see Logic::CCamera
@see Logic::IComponent

@author Alberto Plaza
@date Enero, 2012
*/

#ifndef __Logic_CameraController_H
#define __Logic_CameraController_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
	/**
	Clase del componente que se encarga de mover la c�mara por la escena.

	@author Alberto Plaza
	@date Enero, 2012
*/
	class CCameraController : public IComponent
	{
		DEC_FACTORY(CCameraController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CCameraController() : IComponent(), _up(false), _upMouse(false), _down(false), _downMouse(false), 
			_left(false), _leftMouse(false), _right(false), _rightMouse(false), _mouse(false), _speed(0.05f),
		_northVision(0), _southVision(0), _westVision(0), _eastVision(0),
		_northEntity(0), _southEntity(0), _westEntity(0), _eastEntity(0) {}
		
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
		Atributo para saber hasta d�nde puede subir la c�mara.
		*/
		int _northVision;

		/**
		Atributo para saber hasta d�nde puede bajar la c�mara.
		*/
		int _southVision;

		/**
		Atributo para saber hasta d�nde puede ir a la derecha la c�mara.
		*/
		int _eastVision;

		/**
		Atributo para saber hasta d�nde puede ir a la izquierda la c�mara.
		*/
		int _westVision;

		/**
		Atributo para saber cu�ndo se tiene que mover la c�mara para arriba
		por el movimiento del personaje.
		*/
		int _northEntity;

		/**
		Atributo para saber cu�ndo se tiene que mover la c�mara para abajo
		por el movimiento del personaje.
		*/
		int _southEntity;

		/**
		Atributo para saber cu�ndo se tiene que mover la c�mara para la derecha
		por el movimiento del personaje.
		*/
		int _eastEntity;

		/**
		Atributo para saber cu�ndo se tiene que mover la c�mara para la izquierda
		por el movimiento del personaje.
		*/
		int _westEntity;

	}; // class CCameraController

	REG_FACTORY(CCameraController);

} // namespace Logic

#endif // __Logic_CameraController_H
