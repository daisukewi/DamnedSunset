/**
@file ActivateHealZone.h

Contiene la declaración del mensaje enviado para activar la  habilidad de curación de daño en una zona

@see Logic::IMessage

@author Alberto Ortega
@date Agosto, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_ActivateHealZone_H
#define __Logic_ActivateHealZone_H

#include "Logic/Entity/Message.h"

namespace Logic
{
	class CEntity;
}

namespace Logic 
{

	class MActivateHealZone : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MActivateHealZone();


	};

} // namespace Logic

#endif // __Logic_ActivateHealZone_H