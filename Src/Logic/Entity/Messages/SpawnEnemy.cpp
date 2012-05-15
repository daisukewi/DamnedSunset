/**
@file SpawnEnemy.cpp

Contiene la implementación del mensaje de spawnear enemigo.

@author Alberto Plaza
@date Abril, 2012
*/

#include "SpawnEnemy.h"

namespace Logic
{

	MSpawnEnemy::MSpawnEnemy()
	{
		IMessage();

		_type = "MSpawnEnemy";

	} // MSpawnEnemy

	//---------------------------------------------------------

	void MSpawnEnemy::setNumEnemies(int numEnemies)
	{
		_numEnemies = numEnemies;

	} // setNumEnemies

	//---------------------------------------------------------

	int MSpawnEnemy::getNumEnemies()
	{
		return _numEnemies;

	} // getNumEnemies

	//---------------------------------------------------------

} // namespace Logic