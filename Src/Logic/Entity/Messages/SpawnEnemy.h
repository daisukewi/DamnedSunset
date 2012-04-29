/**
@file SpawnEnemy.h

Contiene la declaración del mensaje de spawnear enemigo.

@see Logic::IMessage

@author Alberto Plaza
@date Abril, 2012
*/

#ifndef __Logic_SpawnEnemy_H
#define __Logic_SpawnEnemy_H

#include "Logic/Entity/Message.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargará de indicar a un spawner que spawnee un enemigo.

	@author Alberto Plaza
	@date Enero, 2012
	*/
	class MSpawnEnemy : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MSpawnEnemy();

	}; // class MSpawnEnemy

} // namespace Logic

#endif // __Logic_SpawnEnemy_H