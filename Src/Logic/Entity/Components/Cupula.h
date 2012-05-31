/**
@file Cupula.h

Contiene la declaración del componente que controla la posición de la cúpula central y se encarga de controlar
las entidades que se encuentran fuera de ésta cuando se hace de día.

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_Cupula_H
#define __Logic_Cupula_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/Math.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente controla la posición de la cúpula en el mapa
	
    @ingroup logicGroup

	@author Alberto Ortega
	@date Mayo, 2012
*/
	class CCupula : public IComponent
	{
		DEC_FACTORY(CCupula);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CCupula() : IComponent(){};

		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se registra así mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y ratón.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando está andando o desplazándose lateralmente).

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(unsigned int msecs);

		/**
		En principio no acepta mensajes
		*/
		virtual bool accept(IMessage *message);

		/**
		En principio no acepta mensajes
		*/
		virtual void process(IMessage *message);
	
	private:
		/**
		Posición de la cúpula
		*/
		Vector3 _position;

		/**
		Tamaño de la cúpula
		*/
		float _radius;



	}; // class CCupula

	REG_FACTORY(CCupula);

} // namespace Logic

#endif // __Logic_CCupula_H
