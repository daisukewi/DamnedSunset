/**
@file ActivateReduceDamage.h

Contiene la declaraci�n del mensaje enviado para activar la  habilidad de reducci�n de da�o

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