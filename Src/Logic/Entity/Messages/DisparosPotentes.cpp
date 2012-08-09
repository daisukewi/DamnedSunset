/**
@file DisparosPotentes.cpp

Contiene la implementación del mensaje enviado para disparar en un sector circular.

@author Luis Mendoza
@date Agosto, 2012
*/

#include "DisparosPotentes.h"

namespace Logic
{
	MDisparosPotentes::MDisparosPotentes()
	{
		IMessage();
		_position = NULL;
		_ordenDisparos = mostrarCono;
		_type = "MDisparosPotentes";
	
	} // MDisparosPotentes

	MDisparosPotentes::~MDisparosPotentes() 
	{
		delete _position;
	}

	Vector2* MDisparosPotentes::getPosition(){
		return _position;
	}

	void MDisparosPotentes::setPosition(Vector2 v){
		_position = new Vector2(v.x,v.y);
	}

	OrdenDisparos MDisparosPotentes::getOrdenDisparos(){
		return _ordenDisparos;
	}

	void MDisparosPotentes::setOrdenDisparos(OrdenDisparos o){
		_ordenDisparos = o;
	}

} // namespace Logic