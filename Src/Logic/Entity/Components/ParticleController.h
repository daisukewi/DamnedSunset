/**
@file ParticleController.h

Contiene la declaración del componente que se encargar de gestionar 
los efectos de partículas

@see Logic::IComponent

@author Alberto Ortega
@date Marzo, 2012
*/
#ifndef __Logic_ParticleController_H
#define __Logic_ParticleController_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente se encarga de recibir mensajes de tipo MParticleEffect de otros componentes que
	para realizar los efectos de partículas

    @ingroup logicGroup

	@author Alberto Ortega
	@date Marzo, 2012
*/
	class CParticleController : public IComponent
	{
		DEC_FACTORY(CParticleController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CParticleController() : IComponent() {};
		
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


	}; // class CParticleController

	REG_FACTORY(CParticleController);

} // namespace Logic

#endif // __Logic_ParticleController_H
