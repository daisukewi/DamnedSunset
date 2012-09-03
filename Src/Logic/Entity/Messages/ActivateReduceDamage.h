/**
@file ActivateReduceDamage.h

Contiene la declaración del mensaje enviado para activar la  habilidad de reducción de daño

@see Logic::IMessage

@author Alberto Ortega
@date Agost, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_ActivateReduceDamage_H
#define __Logic_ActivateReduceDamage_H

#include "Logic/Entity/Message.h"

namespace Logic
{
	class CEntity;
}

namespace Logic 
{

	class MActivateReduceDamage : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MActivateReduceDamage();


	};

} // namespace Logic

#endif // __Logic_ActivateReduceDamage_H