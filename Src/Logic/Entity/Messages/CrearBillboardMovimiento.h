
#ifndef __Logic_CrearBillboardMovimiento_H
#define __Logic_CrearBillboardMovimiento_H

#include "Logic/Entity/Message.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{

	class MCrearBillboardMovimiento : public IMessage
	{
	public:
		MCrearBillboardMovimiento();
		void setBillboardset(Ogre::BillboardSet* b) { _billboardSet = b;}
		Ogre::BillboardSet* getBillboardSet() { return _billboardSet;}
		float getPosX() {return posX;}
		float getPosY() {return posY;}
		void setPosX(float x) {posX = x;}
		void setPosY(float y) {posY = y;}
	protected:
		Ogre::BillboardSet* _billboardSet;
		float posX;
		float posY;
	};

} // namespace Logic

#endif