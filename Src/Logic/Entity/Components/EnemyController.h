/**
@file EnemyController.h

Contiene la declaración del componente que controla el movimiento 
del enemigo.

@see Logic::CEnemyController
@see Logic::IComponent

@author Luis Mendoza
@date Enero, 2012
*/
#ifndef __Logic_EnemyController_H
#define __Logic_EnemyController_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/ClockListener.h"
#include "Logic/Entity/DeathListener.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente es el encargado de mover al enemigo.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Enero, 2012
*/
	class CEnemyController : public IComponent, public BaseSubsystems::IClockListener, public IDeathListener
	{
		DEC_FACTORY(CEnemyController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CEnemyController() : IComponent(), BaseSubsystems::IClockListener(), IDeathListener(), _moving(false) {}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se moverá el enemigo.

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

		Cuando el enemigo pierde toda su vida se llama a este método.
		El enemigo se deja de mover y pone su animación de muerte.
		A los 10 secs desaparece.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario.

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

		/**
		Método heredado de la interfaz IClockListener que será llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();

		/**
		Método heredado de la interfaz IDeathListener que será llamado
		cuando la entidad muera.
		*/
		virtual void entityDeath(CEntity* entity);

		/**
		La entidad ataca.
		*/
		void attack();

	protected:

		/**
		Atributo para saber si el enemigo está en movimiento.
		*/
		bool _moving;

		/**
		Atributo para saber si el enemigo está atacando.
		*/
		bool _attacking;

		/**
		Jugador al que ataca el enemigo.
		*/
		CEntity* _player;

	}; // class CEnemyController

	REG_FACTORY(CEnemyController);

} // namespace Logic

#endif // __Logic_EnemyController_H
