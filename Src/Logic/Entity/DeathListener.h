/**
@file DeathListener.h

Contiene la declaraci�n de un interfaz para un listener de la muerte de una entidad.

@author Alberto Plaza
@date Febrero, 2012
*/

#ifndef __Logic_DeathListener_H
#define __Logic_DeathListener_H

namespace Logic
{
	/**
	Listener de la muerte de una entidad.

	Cada componente que quiera ser avisado de la muerte de una entidad deber�
	implementar esta interfaz cuyos m�todos ser�n llamados por la entidad cuando muera
	y deber�n ser implementados por la clase oyente.

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
		M�todo que ser� llamado por la entidad cuando muera.

		@param entity entidad muerta.
		*/
		virtual void entityDeath(CEntity* entity) = 0;

	}; // IDeathListener

} // namespace Logic

#endif //  __Logic_DeathListener_H