/**
@file MapUnit.h

Contiene la declaración del componente que se comunica con
el mapa lógico para ocupar y desocupar las casillas necesarias
que ocupe una unidad.

@see Logic::CMapUnit
@see Logic::IComponent

@author Daniel Flamenco
@date Febrero, 2012
*/
#ifndef __Logic_MapUnit_H
#define __Logic_MapUnit_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente se encarga de dar de alta una unidad dentro del mapa lógico
	cuando se hace spawn. Y actualiza la casilla en la que se encuentra cuando la
	entidad se mueve.
	Cuando se destruye la unidad, se encarga de liberar la casilla que estaba ocupando.

    @ingroup logicGroup

	@author Daniel Flamenco
	@date Enero, 2012
*/
	class CMapUnit : public IComponent
	{
		DEC_FACTORY(CMapUnit);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CMapUnit() : IComponent(), _unitWidth(1), _unitHeight(1) {}
		
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
		Método virtual que elige que mensajes son aceptados.

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
		Rellena las casillas que ocupa la unidad en el mapa lógico.
		*/
		void UpdateMapCells();

		/**
		Libera las casillas que ocupaba la unidad en el mapa lógico.
		*/
		void FreeMapCells();

		/**
		Atributos que contienen el tamaño (en casillas)
		que ocupa la unidad en el mapa lógico.
		*/
		unsigned int _unitWidth, _unitHeight;

		/**
		Atributos que indican la posición dentro del mapa lógico,
		de la casilla donde se encuentra la unidad.
		*/
		unsigned int _currentRow, _currentCol;

	}; // class CMapBuilding

	REG_FACTORY(CMapUnit);

} // namespace Logic

#endif // __Logic_MapUnit_H
