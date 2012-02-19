/**
@file Life.cpp

Contiene la implementación del componente que controla el movimiento de una entidad (habiendo hecho click en el escenario)
 
@see Logic::CMove
@see Logic::IComponent

@author Alberto Ortega
@date Febrero, 2011
*/

#include "Move.h"

#include "Logic/Entity/Entity.h"


#include "assert.h"

//Mensajes
#include "Logic/Entity/Messages/MoveTo.h"

#include "Logic/Entity/Messages/MoveSteering.h"

#include "AI/Movement.h"


namespace Logic 
{
	IMP_FACTORY(CMove);
	
	//---------------------------------------------------------

	CMove::CMove(){
	}

	CMove::~CMove() {

	}

	bool CMove::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
	} // spawn
	
	//---------------------------------------------------------

	bool CMove::accept(IMessage *message)
	{
		return (message->getType().compare("MMoveTo") == 0);

	} // accept
	
	//---------------------------------------------------------

	void CMove::process(IMessage *message)
	{
		MMoveTo *m_move =  static_cast<MMoveTo*> (message);
		Vector3 point = m_move->getPosition();
		
		
		MMoveSteering *m_movement = new MMoveSteering();
		m_movement->setMovementType(AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);
		m_movement->setTarget(point);
		_entity->emitMessage(m_movement, this);

		std::cout << "Mensaje MMoveTo procesado" ;
	} // process
} // namespace Logic
