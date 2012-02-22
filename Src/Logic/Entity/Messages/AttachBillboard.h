
#ifndef __Logic_AttachBillborad_H
#define __Logic_AttachBillborad_H

#include "Logic/Entity/Message.h"

namespace Graphics
{
	class CBillboard;
}

namespace Logic 
{
	class MAttachBillboard : public IMessage
	{
	public:
		MAttachBillboard();
		void setBillboardset(Graphics::CBillboard* b) { _billboardSet = b;}
		Graphics::CBillboard* getBillboardSet() { return _billboardSet;}
	protected:
		Graphics::CBillboard* _billboardSet;
	};
} // namespace Logic

#endif