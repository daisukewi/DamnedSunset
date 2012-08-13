/**
@file Venom.h

Contiene la declaracióm del mensaje enviado paradormir las IA de los enemigos

@see Logic::IMessage

@author Alberto Ortega
@date Agosto, 2012
*/

#ifndef __Logic_Venom_H
#define __Logic_Venom_H

#include "Logic/Entity/Message.h"

namespace Logic 
{

	class MVenom : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MVenom();

		/**
		Método que devuelve el daño del veneno

		@return int
		*/
		float getVenomDamage();

		/**
		Método que establece el daño del veneno

		@param venomDamage
		*/
		void setVenomDamage(float venomDamage);

		/**
		Método que devuelve el daño del veneno

		@return int
		*/
		int getVenomTime();

		/**
		Método que establece el daño del veneno

		@param venomTime
		*/
		void setVenomTime(int venomTime);

		/**
		Método que devuelve en cuantas veces se reparte el daño del veneno

		@return int
		*/
		float getCount();

		/**
		Método que establece en cuantas veces se reparte el daño del veneno

		@param count
		*/
		void setCount(float count);

	private:
		/**
		Daño del veneno
		*/
		float _venomDamage; //Daño del veneno

		/**
		Tiempo envenenado
		*/
		float _venomTime;

		/**
		En cuantas veces se reparte el daño del veneno
		*/
		float _venomCount;

		
	};

} // namespace Logic

#endif // __Logic_Venom_H