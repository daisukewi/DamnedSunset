-- Recogida de eventos del estado idle.
function idleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState;

	if (event == "OnPlayerSeen") then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemyEventParam.target)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		nextState = 2
	else
		nextState = 1
	end
	
	return nextState;
end

-- Acción del estado idle.
function idleStateAction(entity)
-- El estado de idle es el estado 1.
	return 1
end

-- Recogida de eventos del estado atacando.
function attackStateEvent(event, entity)
-- El estado de atacando es el estado 2.
	local nextState;
	
	if (event == "OnPlayerLost") then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		nextState = 1
	else
		nextState = 2
	end
	
	return nextState;
end

-- Acción del estado atacando.
function attackStateAction(entity)
-- El estado de atacando es el estado 2.
	return 2
end

-- Definición de los distintos estados y sus acciones.
idleState = { event = idleStateEvent, action = idleStateAction }
attackState = { event = attackStateEvent, action = attackStateAction }

-- Tabla con todos los estados.
states = {
	{ name = "idle", state = idleState },
	{ name = "attack", state = attackState }
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function enemyEvent(event, entity)
	local nextState = states[enemies[entity].state].state.event(event, entity)
	enemies[entity].state = nextState
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function AIAction(entity)
	local nextState = states[enemies[entity].state].state.action(entity)
	enemies[entity].state = nextState
end