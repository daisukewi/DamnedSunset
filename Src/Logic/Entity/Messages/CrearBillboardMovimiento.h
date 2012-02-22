
#ifndef __Logic_CrearBillboardMovimiento_H
#define __Logic_CrearBillboardMovimiento_H

#include "Logic/Entity/Message.h"
namespace Logic 
{

	class MCrearBillboardMovimiento : public IMessage
	{
	public:
		MCrearBillboardMovimiento();
		float getPosX() {return posX;}
		float getPosY() {return posY;}
		void setPosX(float x) {posX = x;}
		void setPosY(float y) {posY = y;}
	protected:
		float posX;
		float posY;
	};

} // namespace Logic

#endif