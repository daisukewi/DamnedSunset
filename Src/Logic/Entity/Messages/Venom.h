/**
@file Venom.h

Contiene la declaraci�m del mensaje enviado paradormir las IA de los enemigos

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
		M�todo que devuelve el da�o del veneno

		@return int
		*/
		int getVenomDamage();

		/**
		M�todo que establece el da�o del veneno

		@param venomDamage
		*/
		void setVenomDamage(int venomDamage);

		/**
		M�todo que devuelve el da�o del veneno

		@return int
		*/
		int getVenomTime();

		/**
		M�todo que establece el da�o del veneno

		@param venomTime
		*/
		void setVenomTime(int venomTime);

		/**
		M�todo que devuelve en cuantas veces se reparte el da�o del veneno

		@return int
		*/
		int getCount();

		/**
		M�todo que establece en cuantas veces se reparte el da�o del veneno

		@param count
		*/
		void setCount(int count);

	private:
		/**
		Da�o del veneno
		*/
		int _venomDamage; //Da�o del veneno

		/**
		Tiempo envenenado
		*/
		int _venomTime;

		/**
		En cuantas veces se reparte el da�o del veneno
		*/
		int _count;

		
	};

} // namespace Logic

#endif // __Logic_Venom_H