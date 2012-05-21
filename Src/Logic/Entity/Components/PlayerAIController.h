/**
@file PlayerAIController.h

Contiene la declaración del componente que controla la IA de los personajes.

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_PlayerAIController_H
#define __Logic_PlayerAIController_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
/**
	Componente encargado de controlar la ejecución de la IA
	de los personajes.
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Mayo, 2012
*/
	class CPlayerAIController : public IComponent
	{
		DEC_FACTORY(CPlayerAIController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CPlayerAIController() : IComponent(), _exeFrames(10), _currentExeFrames(0) {}
		
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
		Cada cuántos frames se ejecuta la IA.
		*/
		int _exeFrames;

		/**
		Cuenta de cuántos frames van ejecutados sin hacer la IA.
		*/
		int _currentExeFrames;

	}; // class CPlayerAIController

	REG_FACTORY(CPlayerAIController);

} // namespace Logic

#endif // __Logic_PlayerAIController_H
