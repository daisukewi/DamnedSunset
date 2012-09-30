/**
@file EntityDeathListener.h

Contiene la declaraci�n del mensaje para a�adir o quitar un listener de la muerte de la entidad.

@see Logic::IMessage

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __Logic_EntityDeathListener_H
#define __Logic_EntityDeathListener_H

#include "Logic/Entity/Message.h"

#include "Logic/Entity/DeathListener.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargar� de a�adir o quitar un listener de la muerte de la entidad.

	@author Alberto Plaza
	@date Febrero, 2012
	*/
	class MEntityDeathListener : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MEntityDeathListener();

		/**
		Establece el listener en el mensaje.

		@param listener el listener que se almacena en el mensaje.
		*/
		void setListener(IDeathListener *listener);

		/**
		Establece el ID del listener en el mensaje.

		@param listenerID el ID del listener que se almacena en el mensaje.
		*/
		void setListenerID(unsigned int listenerID);

		/**
		Establece en el mensaje el valor booleano que indica si el listener debe ser quitado o a�adido.

		@param add deber� ser true si se quiere que el listener se a�ada y false en caso contrario.
		*/
		void setAdd(bool add);

		/**
		Devuelve el listener almacenado en el mensaje.

		@return El listener almacenado en el mensaje.
		*/
		IDeathListener* getListener();

		/**
		Devuelve el ID del listener almacenado en el mensaje.

		@return El ID del listener almacenado en el mensaje.
		*/
		unsigned int getListenerID();

		/**
		Devuelve si hay que a�adir o quitar el listener del valor almacenado en el mensaje.

		@return true si el listener deber a�adido y false en caso contrario.
		*/
		bool getAdd();

	protected:

		/**
		Listener que hay que a�adir.
		*/
		IDeathListener *_listener;

		/**
		ID del listener que hay que a�adir.
		*/
		unsigned int _listenerID;

		/**
		Indica si el listener debe ser a�adido o quitado.
		*/
		bool _add;

	}; // class MEntityDeathListener

} // namespace Logic

#endif // __Logic_EntityDeathListener_H