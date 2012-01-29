
#ifndef __Logic_SetBillborad_H
#define __Logic_SetBillborad_H

#include "Logic/Entity/Message.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{

	class CSetBillboard : public IMessage
	{
	public:
		CSetBillboard();

		void setBillboard(Ogre::Billboard b) {_billboard = b;}
		Ogre::Billboard getBillboard() {return _billboard;}
		
		void setPorcetajeVida(float f) {_porcentajeVida = f;}
		float getPorcentajeVida() {return _porcentajeVida;}

		//void setFuncion(void (*f) (Ogre::BillboardSet*,float)) { _funcion = f;};
		//void (*_funcion) (Ogre::BillboardSet*,float) getFuncion() {return _funcion;};

		void (*_funcion) (Ogre::BillboardSet*,float);

	protected:

		/**
		Nombre del material del billboardSet.
		*/
		float _porcentajeVida;
		/**
		Billboard a anadir a la entidad grafica
		*/
		Ogre::Billboard _billboard;

		
	};

} // namespace Logic

#endif // __Logic_SetBillborad_H