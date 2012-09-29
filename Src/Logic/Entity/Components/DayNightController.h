/**
@file DayNight.h

Contiene la declaraci�n del componente que controla el cambio del d�a a la noche

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

//declaraci�n de la clase
namespace Logic 
{
	/**
	Este componente es el encargado de controlar el cambio entre el d�a y la noche
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Mayo, 2012

	*/
	//Enumerado usado para saber en que tiempo se est�
	enum TIME_TYPE{
		DAY,
		NIGHT,
		DAY_ALARM //Queda poco para que llegue el d�a
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

		/**
		M�todo heredado de la interfaz IClockListener que ser� llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed();
		virtual unsigned int getThaId();

	protected:

		/**
		M�todo para enviar a todas las entidades un mensaje enviado como par�metro

		@param mensaje a enviar
		*/
		void sendMessageAll(IMessage *message);

		/**
		Tiempo que dura el dia
		*/
		float _dayTime;

		/**
		Tiempo que indica con cuanta antelaci�ns e le avisa la jugador de que se va a hacer de noche
		*/
		float _dayTimeAlarm;

		/**
		Tiempo que dura la noche
		*/
		float _nightTime;

		/**
		Radio de la c�pula donde no afecta el sol
		*/
		float _safeLimit;

		/**
		Punto inicial donde se encuentra el centro de la c�pula
		*/
		Vector3 _initPoint;


		/**
		Guarda el estado del tiempo del mapa (d�ia /noche / alarma de d�a)
		*/
		TIME_TYPE _timeType;


	}; // class CDistanceAtack

	REG_FACTORY(CDayNightController);

} // namespace Logic

#endif // __Logic_DayNightController_H
