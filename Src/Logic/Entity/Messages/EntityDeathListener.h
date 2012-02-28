/**
@file EntityDeathListener.h

Contiene la declaración del mensaje para añadir o quitar un listener de la muerte de la entidad.

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
	Clase mensaje que se encargará de añadir o quitar un listener de la muerte de la entidad.

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
		Establece en el mensaje el valor booleano que indica si el listener debe ser quitado o añadido.

		@param add deberá ser true si se quiere que el listener se añada y false en caso contrario.
		*/
		void setAdd(bool add);

		/**
		Devuelve el listener almacenado en el mensaje.

		@return El listener almacenado en el mensaje.
		*/
		IDeathListener* getListener();

		/**
		Devuelve si hay que añadir o quitar el listener del valor almacenado en el mensaje.

		@return true si el listener deber añadido y false en caso contrario.
		*/
		bool getAdd();

	protected:

		/**
		Listener que hay que añadir.
		*/
		IDeathListener *_listener;

		/**
		Indica si el listener debe ser añadido o quitado.
		*/
		bool _add;

	}; // class MEntityDeathListener

} // namespace Logic

#endif // __Logic_EntityDeathListener_H