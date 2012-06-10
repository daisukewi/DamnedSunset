/**
@file SelectionController.h

Contiene la declaraci�n del componente que se encarga de decidir
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


//declaraci�n de la clase
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se mover� el jugador.

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

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
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
		M�todo virtual que elige que mensajes son aceptados..

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(IMessage *message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(IMessage *message);


	private:
		/**
		M�todo para procesar la pulsaci�n de las teclas
		*/
		void processKeyboardEvent(GUI::Key::TKeyID key);

		/**
		M�todo para avisar a lua de que personajes han sido seleccionados
		*/
		void processMultipleSelection(bool player1inside, bool player2inside, bool player3inside);

		/**
		M�todo para comprobar si una entidad est� dentro del cuadrado de selecci�n m�ltiple

		Numeraci�n de los v�rtices del cuadrado de selecci�n
		
		1-------2
		|		|
		|		|
		4-------3

		@param entity
		@param worldColissionPoint1 v�rtice 1 del cuadrado
		@param worldColissionPoint2 v�rtice 2 del cuadrado
		@param worldColissionPoint1 v�rtice 3 del cuadrado
		@param worldColissionPoint2 v�rtice 4 del cuadrado
 		*/
		bool checkEntityPosition(CEntity* entity, Vector3 &worldColissionPoint1, 
												  Vector3 &worldColissionPoint2,
												  Vector3 &worldColissionPoint3,
												  Vector3 &worldColissionPoint4);


		/**
		Metodo que se encarga de comprobar hecho una selecci�n m�ltiplea, en caso contrario, llamar a prepareSelectionClick
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
		Atributo que almacena la posici�n del rat�n en pantalla cuando se ha presionado
		*/
		Vector2 _mousePositionPressed;

		/**
		Atributo que almacen la posici�n del rat�n en pantalla cuando se ha soltado
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
