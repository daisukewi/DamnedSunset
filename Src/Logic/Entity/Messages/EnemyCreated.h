/**
@file EnemyCreated.h

Contiene la declaraci�n del mensaje para avisar que se ha creado un enemigo.

@see Logic::IMessage

@author Alberto Ortega
@date Mayo, 2012
*/

#ifndef __Logic_EnemyCreated_H
#define __Logic_EnemyCreated_H

#include "Logic/Entity/Message.h"

#include "Logic/Entity/Entity.h"

namespace Logic
{

	/**
	Clase mensaje que se encargar� de avisar que se ha creado un enemigo.

	@author Alberto Ortega
	@date Mayo, 2012
	*/
	class MEnemyCreated : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MEnemyCreated();

		/**
		M�todo que establece el enemigoque se ha creado.

		@param entity Puntero al enemigo que se ha creado.
		*/
		void setCreatedEnemy(CEntity *enemy);

		/**
		M�todo que devuelve el enemigo que se ha creado.

		@return Puntero al enemigo que se ha creado.
		*/
		CEntity* getCreatedEnemy();

	protected:

		/**
		Atributo que contiene un puntero al enemigo que se ha creado.
		*/
		CEntity *_createdEnemy;


	}; // class MEnemyCreated

} // namespace Logic

#endif // __Logic_EnemyCreated_H