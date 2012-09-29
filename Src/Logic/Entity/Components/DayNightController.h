/**
@file DayNight.h

Contiene la declaración del componente que controla el cambio del día a la noche

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_DAYNIGHTCONTROLLER_H
#define __Logic_DAYNIGHTCONTROLLER_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"
#include "Logic/Entity/DeathListener.h"

#include "BaseSubsystems/ClockListener.h"

//declaración de la clase
namespace Logic 
{
	/**
	Este componente es el encargado de controlar el cambio entre el día y la noche
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Mayo, 2012

	*/
	//Enumerado usado para saber en que tiempo se está
	enum TIME_TYPE{
		DAY,
		NIGHT,
		DAY_ALARM //Queda poco para que llegue el día
	};

	class CDayNightController : public IComponent,  public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CDayNightController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CDayNightController() : IComponent(){}
		
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
		virtual unsigned int getThaId();

	protected:

		/**
		Método para enviar a todas las entidades un mensaje enviado como parámetro

		@param mensaje a enviar
		*/
		void sendMessageAll(IMessage *message);

		/**
		Tiempo que dura el dia
		*/
		float _dayTime;

		/**
		Tiempo que indica con cuanta antelacións e le avisa la jugador de que se va a hacer de noche
		*/
		float _dayTimeAlarm;

		/**
		Tiempo que dura la noche
		*/
		float _nightTime;

		/**
		Radio de la cúpula donde no afecta el sol
		*/
		float _safeLimit;

		/**
		Punto inicial donde se encuentra el centro de la cúpula
		*/
		Vector3 _initPoint;


		/**
		Guarda el estado del tiempo del mapa (dñia /noche / alarma de día)
		*/
		TIME_TYPE _timeType;


	}; // class CDistanceAtack

	REG_FACTORY(CDayNightController);

} // namespace Logic

#endif // __Logic_DayNightController_H
