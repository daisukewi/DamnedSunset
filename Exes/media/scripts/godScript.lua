--------------------------------------------------
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
godIdleState = { event = godIdleStateEvent, action = godIdleStateAction }
godSelectedState = { event = godSelectedStateEvent, action = godSelectedStateAction }
godSkillState = { event = godSkillStateEvent, action = godSkillStateAction }

-- Tabla con todos los estados.
godStates = {
	{ name = "idle", state = godIdleState },
	{ name = "selected", state = godSelectedState },
	{ name = "skill", state = godSkillState }
}

-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados.
function godEvent(event)
	local nextState = godStates[god.state].state.event(event)
	god.state = nextState
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual.
function godAction()
	local nextState = godStates[god.state].state.action()
	god.state = nextState
end