/**
@file Perception.h

Contiene la declaraci�n del componente que controla la percepci�n de los enemigos.

@author Alberto Plaza
@date Mayo, 2012
*/
#ifndef __Logic_Perception_H
#define __Logic_Perception_H

#include "Logic/Entity/Component.h"

// Predeclaraci�n de clases.
namespace Logic
{
	class CEntity;
}

//declaraci�n de la clase
namespace Logic 
{
/**
	Componente encargado de percibir el mundo y notificar a la IA
	cualquier cosa percibida para la toma de decisiones.
	
    @ingroup logicGroup

	@author Alberto Plaza
	@date Mayo, 2012
*/
	class CPerception : public IComponent
	{
		DEC_FACTORY(CPerception);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CPerception() : IComponent(), _distanceOfView(0) {}
		
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
		Distancia de visi�n de la entidad.
		*/
		int _distanceOfView;

		/**
		Lista de los jugadores para comprobar si los veo o no.
		*/
		std::list<Logic::CEntity*> _playerEntities;

	}; // class CPerception

	REG_FACTORY(CPerception);

} // namespace Logic

#endif // __Logic_Perception_H
