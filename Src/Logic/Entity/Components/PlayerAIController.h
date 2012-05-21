/**
@file PlayerAIController.h

Contiene la declaraci�n del componente que controla la IA de los personajes.

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_PlayerAIController_H
#define __Logic_PlayerAIController_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Componente encargado de controlar la ejecuci�n de la IA
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

	protected:

		/**
		Cada cu�ntos frames se ejecuta la IA.
		*/
		int _exeFrames;

		/**
		Cuenta de cu�ntos frames van ejecutados sin hacer la IA.
		*/
		int _currentExeFrames;

	}; // class CPlayerAIController

	REG_FACTORY(CPlayerAIController);

} // namespace Logic

#endif // __Logic_PlayerAIController_H
