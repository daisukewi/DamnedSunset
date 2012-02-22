/**
@file EnemiesGenerator.h

Contiene la declaración del componente que controla la generación en 
el mapa de enemigos.

@see Logic::CEnemiesGenerator
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/
#ifndef __Logic_EnemiesGenerator_H
#define __Logic_EnemiesGenerator_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente es el encargado de generar enemigos.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Febrero, 2012
*/
	class CEnemiesGenerator : public IComponent
	{
		DEC_FACTORY(CEnemiesGenerator);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CEnemiesGenerator() : IComponent(), _origen(Vector3::ZERO), _ticks(0), _enemy(0), _periodo(500) {}
		
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
		Se encarga de crear un enemigo según ciertas condiciones.

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

	protected:

		/**
		Atributo para saber el lugar donde se crea el enemigo.
		*/
		Vector3 _origen;

		/**
		Contador de ticks.
		*/
		unsigned int _ticks;

		/**
		Contador de enemigos.
		*/
		unsigned int _enemy;

		/**
		Cada cuántos ticks se crea un enemigo.
		*/
		unsigned int _periodo;

	}; // class CEnemiesGenerator

	REG_FACTORY(CEnemiesGenerator);

} // namespace Logic

#endif // __Logic_EnemiesGenerator_H
