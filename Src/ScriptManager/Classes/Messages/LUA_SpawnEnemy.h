/**
@file LUA_SpawnEnemy.h

Contiene la declaración del mensaje de spawnear enemigo que sirve como intermediario entre lua y C++.

@author Alberto Plaza
@date Abril, 2012
*/

#ifndef __Logic_LUA_SpawnEnemy_H
#define __Logic_LUA_SpawnEnemy_H

#include "LUA_Message.h"

namespace ScriptManager 
{
	/**
	Clase mensaje que se encargará de indicar que hay que spawnear enemigos.

	@author Alberto Plaza
	@date Abril, 2012
	*/
	class LUA_MSpawnEnemy : public LUA_IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		LUA_MSpawnEnemy();

		/**
		Implementación del método send heredado de la clase LUA_IMessage
		*/
		virtual void send();

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

	}; // class LUA_MSpawnEnemy

} // namespace Logic

#endif // __Logic_LUA_SpawnEnemy_H