
#ifndef __Logic_CreateBillborad_H
#define __Logic_CreateBillborad_H

#include "Logic/Entity/Message.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{

	class MCreateBillboard : public IMessage
	{
	public:
		MCreateBillboard();
		void setTipoBillboard(std::string s) {_tipoBillboard = s;}
		std::string getTipoBillboard() {return _tipoBillboard;}
	protected:
		/*
		Indica el tipo del billboard, por ejemplo si es para la vida, o para si esta seleccionado
		*/
		std::string _tipoBillboard;
	};

} // namespace Logic

#endif