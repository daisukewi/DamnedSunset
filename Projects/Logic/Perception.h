#ifndef __Logic_Perception_H
#define __Logic_Perception_H

#include "Logic/Entity/Component.h"

namespace Logic
{
	class CPerception : public IComponent
	{
		DEC_FACTORY(CPerception);
	public:

		CPerception() : IComponent() {}

		~CPerception() {}

		virtual void tick(unsigned int msecs);

	private:

	};

	REG_FACTORY(CPerception);

}

#endif