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
		int getVenomDamage();

		/**
		Método que establece el daño del veneno

		@param venomDamage
		*/
		void setVenomDamage(int venomDamage);

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
		int getCount();

		/**
		Método que establece en cuantas veces se reparte el daño del veneno

		@param count
		*/
		void setCount(int count);

	private:
		/**
		Daño del veneno
		*/
		int _venomDamage; //Daño del veneno

		/**
		Tiempo envenenado
		*/
		int _venomTime;

		/**
		En cuantas veces se reparte el daño del veneno
		*/
		int _count;

		
	};

} // namespace Logic

#endif // __Logic_Venom_H