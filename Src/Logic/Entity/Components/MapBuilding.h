/**
@file MapBuilding.h

Contiene la declaraci�n del componente que se comunica con
el mapa l�gico para ocupar y desocupar las casillas necesarias
que ocupe un edificio.

@see Logic::CMapBuilding
@see Logic::IComponent

@author Daniel Flamenco
@date Febrero, 2012
*/
#ifndef __Logic_MapBuilding_H
#define __Logic_MapBuilding_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente se encarga de dar de alta un edificio dentro del mapa l�gico
	cuando se hace spawn.
	Cuando el edificio es borrado, se encarga de liberar las casillas que estaba ocupando.

    @ingroup logicGroup

	@author Daniel Flamenco
	@date Enero, 2012
*/
	class CMapBuilding : public IComponent
	{
		DEC_FACTORY(CMapBuilding);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CMapBuilding() : IComponent() {}

		/**
		Destructor. Tiene que liberar las casillas ocupadas por el edificio
		en el mapa l�gico.
		*/
		~CMapBuilding();
		
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
		M�todo virtual que elige que mensajes son aceptados.

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
		Rellena las casillas que ocupa el edificio en el mapa l�gico.
		*/
		void FillMapCells();

		/**
		Libera las casillas que ocupaba el edificio en el mapa l�gico.
		*/
		void FreeMapCells();

		/**
		Atributo que contiene el tama�o (en casillas)
		que ocupa el edificio en el mapa l�gico.
		*/
		Vector2 _buildingSize;

	}; // class CMapBuilding

	REG_FACTORY(CMapBuilding);

} // namespace Logic

#endif // __Logic_MapBuilding_H
