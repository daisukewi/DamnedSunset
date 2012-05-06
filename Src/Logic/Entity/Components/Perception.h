/**
@file Perception.h

Contiene la declaración del componente que controla la percepción de los enemigos.

@author Alberto Plaza
@date Mayo, 2012
*/
#ifndef __Logic_Perception_H
#define __Logic_Perception_H

#include "Logic/Entity/Component.h"

// Predeclaración de clases.
namespace Logic
{
	class CEntity;
}

//declaración de la clase
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
		Distancia de visión de la entidad.
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
