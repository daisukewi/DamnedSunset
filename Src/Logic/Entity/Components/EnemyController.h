/**
@file EnemyController.h

Contiene la declaraci�n del componente que controla el movimiento 
del enemigo.

@see Logic::CEnemyController
@see Logic::IComponent

@author Luis Mendoza
@date Enero, 2012
*/
#ifndef __Logic_EnemyController_H
#define __Logic_EnemyController_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente es el encargado de mover al enemigo.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Enero, 2012
*/
	class CEnemyController : public IComponent
	{
		DEC_FACTORY(CEnemyController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CEnemyController() : IComponent(), _moving(false), _speed(0.04f), _destino(Vector3::ZERO) {}
		
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se mover� el enemigo.

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
		necesario.

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
		Atributo para saber la velocidad a la que avanza el enemigo.
		*/
		float _speed;

		/**
		Atributo para saber si el enemigo est� en movimiento.
		*/
		bool _moving;

		/**
		Atributo para saber el destino del enemigo.
		*/
		Vector3 _destino;

	}; // class CEnemyController

	REG_FACTORY(CEnemyController);

} // namespace Logic

#endif // __Logic_EnemyController_H
