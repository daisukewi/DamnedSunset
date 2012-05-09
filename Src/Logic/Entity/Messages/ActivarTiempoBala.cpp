/**
@file ActivarTiempoBala.cpp

Contiene la implementacion del mensaje MActivarTiempoBala

@author Isaac Gallarzagoitia
@date Marzo, 2012
*/

#include "ActivarTiempoBala.h"

namespace Logic
{

	MActivarTiempoBala::MActivarTiempoBala()
	{
		IMessage();
		_type = "MActivarTiempoBala";

		_numEntities = 0;

		_entitiesID = NULL;
	}

	MActivarTiempoBala::~MActivarTiempoBala()
	{
		delete _entitiesID;
	}

	void MActivarTiempoBala::invalidateIDs()
	{
		_entitiesID = NULL;
		_numEntities = 0;
	}

	void MActivarTiempoBala::addEntity(unsigned int id)
	{
		++_numEntities;
		unsigned int * newEntitiesID = new unsigned int [_numEntities];
		for (int i =0; i < _numEntities - 1; ++i) {
			newEntitiesID[i] = _entitiesID[i];
		}
		delete _entitiesID;
		_entitiesID = newEntitiesID;
		_entitiesID[_numEntities-1] = id;
	}
} // namespace Logic