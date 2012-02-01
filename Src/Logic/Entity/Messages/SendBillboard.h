
#ifndef __Logic_SendBillboard_H
#define __Logic_SendBillboard_H

#include "Logic/Entity/Message.h"

#include <OgreBillboardSet.h>

namespace Logic 
{

	class MSendBillboard : public IMessage
	{
	public:
		MSendBillboard();

		void setBillboardSet(Ogre::BillboardSet* b) {_billboardSet = b;}
		Ogre::BillboardSet* getBillboarSet() { return _billboardSet;}

		void setTipoBillboard(std::string s) {_tipoBillboard = s;}
		std::string getTipoBillboard() {return _tipoBillboard;}
	protected:
		Ogre::BillboardSet* _billboardSet;
		/*
		Indica el tipo del billboard, por ejemplo si es para la vida, o para si esta seleccionado
		*/
		std::string _tipoBillboard;
	};

} // namespace Logic

#endif // __Logic_SetBillborad_H