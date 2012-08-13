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
		float getVenomDamage();

		/**
		M�todo que establece el da�o del veneno

		@param venomDamage
		*/
		void setVenomDamage(float venomDamage);

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
		float getCount();

		/**
		M�todo que establece en cuantas veces se reparte el da�o del veneno

		@param count
		*/
		void setCount(float count);

	private:
		/**
		Da�o del veneno
		*/
		float _venomDamage; //Da�o del veneno

		/**
		Tiempo envenenado
		*/
		float _venomTime;

		/**
		En cuantas veces se reparte el da�o del veneno
		*/
		float _venomCount;

		
	};

} // namespace Logic

#endif // __Logic_Venom_H