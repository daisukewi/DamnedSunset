#include "Selectable.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics\Server.h"
#include "Physics\Server.h"

#include "Logic/Maps/Map.h"
#include "Logic/Entity/Messages/EntitySelected.h"

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

	bool CSelectable::accept(IMessage *message)
	{
		return !message->getType().compare("MSelectable");

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

	void CSelectable::process(IMessage *message)
	{
		if (!message->getType().compare("MSelectable")){

			//Obtener la entidad encargadad de controllar el gameplay
			CEntity *entity = _entity->getMap()->getEntityByName("PlayerGod");
			
			//Crear y enviar el mensaje de entity selected
			MEntitySelected* m_selected = new MEntitySelected();
			m_selected->setSelectedEntity(_entity);
			entity->emitMessage(m_selected);

			
			//std::cout << "SELECTABLE PROCESS ENTIDAD: " << _entity->getType();
			

			//Logic::CSetBillboard *ms = new Logic::CSetBillboard();
			//ms->_funcion = generarBillboardSelectable;
			//ms->setPorcetajeVida(0);
			//_entity->emitMessage(ms);

		}

	} // process

	//---------------------------------------------------------

	void CSelectable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		

	} // tick

} // namespace Logic
