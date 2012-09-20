
#ifndef __Logic_Aturdido_H
#define __Logic_Aturdido_H

#include "Logic/Entity/Message.h"


namespace Logic 
{
	class MAturdido : public IMessage
	{
	public:
		MAturdido();
		~MAturdido();
		void setAturdido(bool a) {_aturdido = a;}
		bool getAturdido() {return _aturdido;}
	protected:
		bool _aturdido;
	};

} // namespace Logic

#endif