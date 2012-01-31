
#ifndef __Logic_SendBillboard_H
#define __Logic_SendBillboard_H

#include "Logic/Entity/Message.h"

#include <OgreBillboardSet.h>

namespace Logic 
{

	class CSendBillboard : public IMessage
	{
	public:
		CSendBillboard();

		void setBillboardSet(Ogre::BillboardSet* b) {_billboardSet = b;}
		Ogre::BillboardSet* getBillboarSet() { return _billboardSet;}
	protected:
		Ogre::BillboardSet* _billboardSet;
	};

} // namespace Logic

#endif // __Logic_SetBillborad_H