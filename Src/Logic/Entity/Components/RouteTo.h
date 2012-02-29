/**
@file RouteTo.h

Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cin�ticos o din�micos.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_RouteTo_H
#define __Logic_RouteTo_H

#include "Logic/Entity/Component.h"

#include "BaseSubsystems/Math.h"

namespace Logic
{
	/**
	Componente que se encarga de gestionar el c�lculo y el seguimiento
	de rutas. El componente acepta mensajes de tipo MWayTo con un par�metro
	_vector que indica la posici�n de destino.
	<p>
	Cuando se recibe un mensaje de este tipo, se calcula una nueva ruta
	hasta el destino indicado y se comienza su seguimiento. Para cada 
	segmento de la ruta, el componente env�a un mensaje MMoveSteering, con el 
	destino de ese segmento y el tipo de movimiento necesario como par�metros 
	(estos mensajes pueden ser aceptados por el componente CSteeringMovement).
	<p>
	Cuando se llega al �ltimo punto de la ruta la entidad se detiene y env�a 
	un mensaje del tipo FINISHED_ROUTE.
	<p>
	Si es imposible obtener una ruta hasta el destino se env�a un mensaje FAILED_ROUTE.
	*/
	class CRouteTo : public IComponent
	{
	
		DEC_FACTORY(CRouteTo);
	
	public:
		/**
		Constructor
		*/
		CRouteTo(void) : IComponent (), _recalculateRoute(false), _currentRoute(0), _arrived(true){};
		/**
		Destructor
		*/
		~CRouteTo(void) { if (_currentRoute != 0) delete _currentRoute; };
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad m�xima a la que se mover� la entidad.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(unsigned int msecs);
		/**
		Este componente s�lo acepta mensajes de tipo MWayTo.
		*/
		virtual bool accept(IMessage *message);
		/**
		Si se recibe un mensaje de tipo MWayTo, almacena el vector como 
		destino del movimiento.
		*/
		virtual void process(IMessage *message);

	private:
		/**
		Destino de la ruta.
		*/
		Vector3 _target;
		/**
		Indica si hay que volver a calcular la ruta
		*/
		bool _recalculateRoute;
		/**
		Indica si se ha llegado al destino.
		*/
		bool _arrived;
		/**
		Indica si debe pasar al siguiente punto de la ruta
		*/
		bool _nextWaypoint;
		/**
		Almacena el punto de la ruta al que se est� intentando llegar.
		*/
		unsigned int _currentNode;
		/**
		Almacena la ruta actual
		*/
		std::vector<Vector3> *_currentRoute;
		/** 
		Env�a un mensaje MMoveSteering.

		@param target Destino.
		@movementType Tipo de movimiento.
		*/
		void sendMoveMessage(Vector3 target, int movementType);

		/**
		Devuelve el siguiente punto de la ruta al que se tiene que viajar.
		Optimiza la ruta generada por el A* eliminando nodos innecesarios.

		@return entero que contiene el siguiente nodo de la ruta por el
		        que se tiene que pasar.
		*/
		int getNextRoutePoint();
	};

	REG_FACTORY(CRouteTo);

} // namespace Logic

#endif //#ifndef __Logic_RouteTo_H
