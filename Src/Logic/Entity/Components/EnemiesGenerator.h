/**
@file EnemiesGenerator.h

Contiene la declaraci�n del componente que controla la generaci�n en 
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

//declaraci�n de la clase
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
		Se encarga de crear un enemigo seg�n ciertas condiciones.

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

		/**
		Spawnea en una posici�n aleatoria alrededor del spawner.

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
		Cada cu�ntos milisegundos se crea un enemigo.
		*/
		unsigned int _periodo;

		/**
		Indica si hay que spawnear enemigos autom�ticamente o no.
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
