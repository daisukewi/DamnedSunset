
#ifndef __Logic_AttachBillborad_H
#define __Logic_AttachBillborad_H

#include "Logic/Entity/Message.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{

	class MAttachBillboard : public IMessage
	{
	public:
		MAttachBillboard();
		void setBillboardset(Ogre::BillboardSet* b) { _billboardSet = b;}
		Ogre::BillboardSet* getBillboardSet() { return _billboardSet;}
	protected:
		Ogre::BillboardSet* _billboardSet;
	};

} // namespace Logic

#endif