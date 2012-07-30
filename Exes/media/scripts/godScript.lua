--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
godIdleState = { event = godIdleStateEvent, action = godIdleStateAction }
godSelectedState = { event = godSelectedStateEvent, action = godSelectedStateAction }
godSkillState = { event = godSkillStateEvent, action = godSkillStateAction }

-- Tabla con todos los estados.
godStates = {
	{ name = "idle", state = godIdleState },
	{ name = "selected", state = godSelectedState },
	{ name = "skill", state = godSkillState }
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function godEvent(event)
	local nextState = godStates[god.state].state.event(event)
	god.state = nextState
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function godAction()
	local nextState = godStates[god.state].state.action()
	god.state = nextState
end