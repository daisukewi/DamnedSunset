#include "Selectable.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic/Maps/Map.h"

#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

namespace Logic 
{
	IMP_FACTORY(CSelectable);
	
	//---------------------------------------------------------

	bool CSelectable::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSelectable::activate()
	{	
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CSelectable::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CSelectable::accept(const TMessage &message)
	{
		return false;//message._type == Message::SELECTABLE;

	} // accept
	
	//---------------------------------------------------------


	void generarBillboardSelectable(Ogre::BillboardSet* b, float unused) {
		//Tendria q haber 2 billboard creados, si no estan los creamos
		Ogre::Billboard* billboard;
		while (b->getNumBillboards() < 2 ) {
			billboard = b->createBillboard(0,13,0);
			billboard->setDimensions(0,0);
		}
		//El ultimo billboard es el q nos interesa: El '1'
		billboard = b->getBillboard(1);
		billboard->setDimensions(4,4);
		billboard->setPosition(0,16,0);
		billboard->setTexcoordRect(0.0f/*inicioX*/, 0.2f, 0.4f/*finX*/, 0.6f);
	}

	void CSelectable::process(const TMessage &message)
	{
		switch(message._type)
		{
		/*case Message::SELECTABLE:
			//Obtener la entidad encargadad de controllar el gameplay
			CEntity *entity = _entity->getMap()->getEntityByName("TargetCamera");
			TMessage m;
			m._type = Message::ENTITY_SELECTED;
			m._entity = _entity;
			m._pointvector3 = message._pointvector3;
			entity->emitMessage(m);*/
			

			//Logic::CSetBillboard *ms = new Logic::CSetBillboard();
			//ms->_funcion = generarBillboardSelectable;
			//ms->setPorcetajeVida(0);
			//_entity->emitMessage(ms);


			break;
		}

	} // process

	//---------------------------------------------------------

	void CSelectable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		

	} // tick

} // namespace Logic
