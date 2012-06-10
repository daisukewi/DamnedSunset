/**
@file SelectionController.h

Contiene la declaración del componente que se encarga de decidir
que cosas se seleccionan cuando se hace click izquierdo, y que sobre que
entidades se actua cuando se hace click derecho.

@see Logic::CSelectionController
@see Logic::IComponent

@author Daniel Flamenco
@date Mayo, 2012
*/
#ifndef __Logic_SelectionController_H
#define __Logic_SelectionController_H

#include "Logic/Entity/Component.h"
#include "GUI/Server.h"

#include "BaseSubsystems/Math.h"


//declaración de la clase
namespace Logic 
{

	class CSelectionController : public IComponent
	{
		DEC_FACTORY(CSelectionController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSelectionController() : IComponent() {}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se moverá el jugador.

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

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		<p>
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
		Método virtual que elige que mensajes son aceptados..

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);


	private:
		/**
		Método para procesar la pulsación de las teclas
		*/
		void processKeyboardEvent(GUI::Key::TKeyID key);

		/**
		Método para avisar a lua de que personajes han sido seleccionados
		*/
		void processMultipleSelection(bool player1inside, bool player2inside, bool player3inside);

		/**
		Método para comprobar si una entidad está dentro del cuadrado de selección múltiple

		Numeración de los vértices del cuadrado de selección
		
		1-------2
		|		|
		|		|
		4-------3

		@param entity
		@param worldColissionPoint1 vértice 1 del cuadrado
		@param worldColissionPoint2 vértice 2 del cuadrado
		@param worldColissionPoint1 vértice 3 del cuadrado
		@param worldColissionPoint2 vértice 4 del cuadrado
 		*/
		bool checkEntityPosition(CEntity* entity, Vector3 &worldColissionPoint1, 
												  Vector3 &worldColissionPoint2,
												  Vector3 &worldColissionPoint3,
												  Vector3 &worldColissionPoint4);


		/**
		Metodo que se encarga de comprobar hecho una selección múltiplea, en caso contrario, llamar a prepareSelectionClick
		*/
		void prepareMultipleSelectionClick();


		/**
		Metodo que se encarga de comprobar que se ha hecho click izquierdo
		y si hay una entidad, comprobar que se puede seleccionar.
		*/
		void prepareSelectionClick();

		/**
		Metodo que se encarga de comprobar que se ha hecho click derecho
		y si hay una entidad, comprobar que se puede realizar una accion sobre ella.
		*/
		void prepareActionClick();

		/**
		Metodo que se encarga de procesar que se ha hecho click izquierdo
		y se ha seleccionado una entidad.
		<p>
		Envia un mensaje a la entidad indicando el evento de seleccion.
		*/
		void processSelectionClick();

		/**
		Metodo que se encarga de procesar que se ha hecho click derecho
		y se va a actuar sobre una entidad.
		<p>
		Envia un mensaje a la entidad indicando el evento de actuar.
		*/
		void processActionClick();

		/**
		Flag que se activa cuando se esta esperando una respuesta
		de una entidad que sea seleccionable.
		*/
		bool _waitingForSelectable;

		/**
		Flag que se activa cuando se esta esperando una respuesta
		de una entidad sobre la que se pueda actuar.
		*/
		bool _waitingForActuable;

		/**
		Atributo que almacena el punto de colision del ultimo click
		de raton que se hizo sobre el mapa.
		*/
		Vector3 _worldCollisionPoint;

		/**
		Atributo que contiene el ID de la entidad sobre la que se va a
		realizar la seleccion o la accion.
		*/
		int _targetEntityID;

		/**
		Atributo que almacena la posición del ratón en pantalla cuando se ha presionado
		*/
		Vector2 _mousePositionPressed;

		/**
		Atributo que almacen la posición del ratón en pantalla cuando se ha soltado
		*/
		Vector2 _mousePositionReleased;

		/**
		Atributos que almacenan los IDs de los personajes
		*/
		CEntity* _player1;
		CEntity* _player2;
		CEntity* _player3;

		
	}; // class CSelectedController

	REG_FACTORY(CSelectionController);

} // namespace Logic

#endif // __Logic_SelectionController_H
