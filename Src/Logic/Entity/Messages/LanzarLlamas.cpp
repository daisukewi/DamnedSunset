/**
@file LanzarLlamas.cpp

Contiene la implementación del mensaje enviado para ejecutar el lanzallamas.

@author Luis Mendoza
@date Agosto, 2012
*/

#include "LanzarLlamas.h"

namespace Logic
{
	MLanzarLlamas::MLanzarLlamas()
	{
		IMessage();
		_position = NULL;
		_ordenLlamas = mostrarBLlamas;
		_type = "MLanzarLlamas";
	
	} // MLanzarLlamas

	MLanzarLlamas::~MLanzarLlamas() 
	{
		delete _position;
	}

	Vector2* MLanzarLlamas::getPosition(){
		return _position;
	}

	void MLanzarLlamas::setPosition(Vector2 v){
		_position = new Vector2(v.x,v.y);
	}

	OrdenLlamas MLanzarLlamas::getOrdenLlamas(){
		return _ordenLlamas;
	}

	void MLanzarLlamas::setOrdenLlamas(OrdenLlamas o){
		_ordenLlamas = o;
	}

} // namespace Logic