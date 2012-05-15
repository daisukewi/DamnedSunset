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
	Clase mensaje que se encargará de indicar a un spawner que spawnee enemigos.

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

		/**
		Establece en el mensaje el número de enemigos que hay que spawnear.
		*/
		void setNumEnemies(int numEnemies);

		/**
		Devuelve el número de enemigos que hay que spawnear almacenados en el mensaje.
		*/
		int getNumEnemies();

	protected:

		/**
		Número de enemigos que hay que spawnear.
		*/
		int _numEnemies;

	}; // class MSpawnEnemy

} // namespace Logic

#endif // __Logic_SpawnEnemy_H