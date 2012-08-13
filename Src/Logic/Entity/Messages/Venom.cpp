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


	float MVenom::getVenomDamage(){
		return _venomDamage;
	}

	void MVenom::setVenomDamage(float venomDamage){
		_venomDamage = venomDamage;
	}



	int MVenom::getVenomTime(){
		return _venomTime;
	}


	void MVenom::setVenomTime(int venomTime){
		_venomTime = venomTime;
	}

	float MVenom::getCount(){
		return _venomCount;
	}

	void MVenom::setCount(float count){
		_venomCount = count;
	}



} // namespace Logic