/**
@file DeathListener.h

Contiene la declaración de un interfaz para un listener de la muerte de una entidad.

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __Logic_DeathListener_H
#define __Logic_DeathListener_H

namespace Logic
{
	/**
	Listener de la muerte de una entidad.

	Cada componente que quiera ser avisado de la muerte de una entidad deberá
	implementar esta interfaz cuyos métodos serán llamados por la entidad cuando muera
	y deberán ser implementados por la clase oyente.

	@author Alberto Plaza
	@date Febrero, 2012
	*/
	class IDeathListener
	{
	public:

		/**
		Constructor por defecto de la clase. En la clase base no hace nada.
		*/
		IDeathListener() {}

		/**
		Destructor por defecto. En la clase base no hace nada.
		*/
		virtual ~IDeathListener() {}

		/**
		Método que será llamado por la entidad cuando muera.

		@param entity entidad muerta.
		*/
		virtual void entityDeath(CEntity* entity) = 0;

	}; // IDeathListener

} // namespace Logic

#endif //  __Logic_DeathListener_H