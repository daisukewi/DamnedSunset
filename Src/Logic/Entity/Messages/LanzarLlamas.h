/**
@file LanzarLlamas.h

Contiene la declaración del mensaje enviado para ejecutar el lanzallamas.

@see Logic::IMessage

@author Luis Mendoza
@date Agosto, 2012
*/

#ifndef __Logic_LanzarLlamas_H
#define __Logic_LanzarLlamas_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{
	enum OrdenLlamas
	{
		mostrarBLlamas = 0,
		ocultarBLamas = 1,
		lanzarLlamas = 2,
	};

	class MLanzarLlamas : public IMessage
	{
	public:
		/**
		Constructor y destructor por defecto.
		*/
		MLanzarLlamas();
		~MLanzarLlamas();

		/**
		Método que devuelve el punto al que disparar

		@return Vector2
		*/
		Vector2* getPosition();

		/**
		Método que establece el punto al que disparar

		@param v Vector2
		*/
		void setPosition(Vector2 v);

		/**
		Método que devuelve la orden

		@return OrdenLlamas
		*/
		OrdenLlamas getOrdenLlamas();

		/**
		Método que establece la orden

		@param o OrdenLlamas
		*/
		void setOrdenLlamas(OrdenLlamas o);

	protected:
		/**
		Punto al que disparar
		*/
		Vector2 * _position;

		/**
		Orden
		*/
		enum OrdenLlamas _ordenLlamas;
	};

} // namespace Logic

#endif // __Logic_LanzarLlamas_H