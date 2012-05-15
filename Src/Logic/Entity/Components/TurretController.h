/**
@file TurretController.h

Contiene la declaraci�n del componente que controla lo que debe hacer una torreta.

@see Logic::CTurretController
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/
#ifndef __Logic_TurretController_H
#define __Logic_TurretController_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente es el encargado de controlar las acciones de las torretas.
	
    @ingroup logicGroup

	@author Luis Mendoza
	@date Febrero, 2012
*/
	class CTurretController : public IComponent
	{
		DEC_FACTORY(CTurretController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CTurretController() : IComponent(), _attacking(false), _precision(50) {}
		
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
		Da�o de la torreta.
		*/
		int _damage;

		/**
		Atributo para saber si la torreta est� atacando.
		*/
		bool _attacking;

		/**
		Atributo que indica la punter�a de la torreta.
		*/
		float _precision;

		/**
		Tipos para la lista de entidades.
		*/
		typedef std::list<CEntity*> TEntityList;

		/**
		Entidades objetivo a atacar.
		*/
		std::list<unsigned int> _enemiesID;

	}; // class CTurretController

	REG_FACTORY(CTurretController);

} // namespace Logic

#endif // __Logic_TurretController_H
