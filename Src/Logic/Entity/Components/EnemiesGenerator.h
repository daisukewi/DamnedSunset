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
		CEnemiesGenerator() : IComponent(), _origen(Vector2::ZERO), _time(0), _enemy(0), _periodo(10000), _spawn(0) {}
		
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

		/**
		Spawnea en una posición aleatoria alrededor del spawner.

		@return La referencia del enemigo spawneado.
		*/
		Logic::CEntity* spawnEnemy();

	protected:

		/**
		Atributo para saber el lugar donde se crea el enemigo.
		*/
		Vector2 _origen;

		/**
		Contador de tiempo.
		*/
		unsigned int _time;

		/**
		Contador de enemigos.
		*/
		unsigned int _enemy;

		/**
		Cada cuántos milisegundos se crea un enemigo.
		*/
		unsigned int _periodo;

		/**
		Indica si hay que spawnear enemigos automáticamente o no.
		*/
		bool _automaticSpawn;

		/**
		Indica si hay que spawnear un enemigo en el tick del componente y cuantos.

		Hecho para no spawnear mas de un enemigo por tick.
		*/
		int _spawn;

	}; // class CEnemiesGenerator

	REG_FACTORY(CEnemiesGenerator);

} // namespace Logic

#endif // __Logic_EnemiesGenerator_H
