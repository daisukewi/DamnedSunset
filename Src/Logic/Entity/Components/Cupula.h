/**
@file Cupula.h

Contiene la declaraci�n del componente que controla la posici�n de la c�pula central y se encarga de controlar
las entidades que se encuentran fuera de �sta cuando se hace de d�a.

@see Logic::IComponent

@author Alberto Ortega
@date Mayo, 2012
*/
#ifndef __Logic_Cupula_H
#define __Logic_Cupula_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/Math.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente controla la posici�n de la c�pula en el mapa
	
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
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.
		<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se registra as� mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y rat�n.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
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
		Posici�n de la c�pula
		*/
		Vector3 _position;

		/**
		Tama�o de la c�pula
		*/
		float _radius;



	}; // class CCupula

	REG_FACTORY(CCupula);

} // namespace Logic

#endif // __Logic_CCupula_H
