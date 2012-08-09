/**
@file DisparosPotentes.h

Contiene la declaracióm del mensaje enviado para disparar en un sector circular.

@see Logic::IMessage

@author Luis Mendoza
@date Agosto, 2012
*/

#ifndef __Logic_DisparosPotentes_H
#define __Logic_DisparosPotentes_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{
	enum OrdenDisparos
	{
		mostrarCono = 0,
		ocultarCono = 1,
		disparar = 2,
	};

	class MDisparosPotentes : public IMessage
	{
	public:
		/**
		Constructor y destructor por defecto.
		*/
		MDisparosPotentes();
		~MDisparosPotentes();

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

		@return OrdenDisparos
		*/
		OrdenDisparos getOrdenDisparos();

		/**
		Método que establece la orden

		@param o OrdenDisparos
		*/
		void setOrdenDisparos(OrdenDisparos o);

	protected:
		/**
		Punto al que disparar
		*/
		Vector2 * _position;

		/**
		Orden
		*/
		enum OrdenDisparos _ordenDisparos;
	};

} // namespace Logic

#endif // __Logic_DisparosPotentes_H