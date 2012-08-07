/**
@file Venom.cpp

Contiene la implementación del mensaje enviado paradormir las IA de los enemigos

@author Alberto Ortega
@date Agosto, 2012
*/

#include "Venom.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Server.h"
#include "Logic/Maps/Map.h"

namespace Logic
{
	MVenom::MVenom()
	{
		IMessage();

		_type = "MVenom";
	
	} // MVenom


	int MVenom::getVenomDamage(){
		return _venomDamage;
	}

	void MVenom::setVenomDamage(int venomDamage){
		_venomDamage = venomDamage;
	}



	int MVenom::getVenomTime(){
		return _venomTime;
	}


	void MVenom::setVenomTime(int venomTime){
		_venomTime = venomTime;
	}

	int MVenom::getCount(){
		return _count;
	}

	void MVenom::setCount(int count){
		_count = count;
	}



} // namespace Logic