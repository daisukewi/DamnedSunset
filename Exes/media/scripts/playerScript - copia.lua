--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function playerIdleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	if (event == "OnFollow") then
		print("playerIdleStateEvent ONFOLLOW")
		nextState = 2
	elseif (event == "OnHold") then
		print("playerIdleStateEvent ONHOLD")
		nextState = 3
	end
	
	return nextState
end

-- Acción del estado idle.
function playerIdleStateAction(entity)
	
	return 1
end

--------------------------------------------------
--				Estado atacando					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function playerFollowStateEvent(event, entity)

	local nextState
	if (event == "OnHold") then

		nextState = 3
	else if (event == "OnEnemySeen") then
	
	else if (event == "OnEnemyLost") then
	
	end	
	
	return nextState
end

-- Acción del estado atacando.
function playerFollowStateAction(entity)
	
	
	return nextState
end

--------------------------------------------------
--				Estado moviendo					--
--------------------------------------------------

-- Recogida de eventos del mantener posición.
function playerHoldStateEvent(event, entity)
	local nextState
	if (event == "OnFollow") then
		
		nextState = 2
	else if (event == "OnEnemySeen") then
	
		if (playerEventParam.distance < distance) then
			distance = playerEventParam.distance
			
			local mensaje = LUA_MAttackDistance()
			mensaje:setAttack(true)
			mensaje:setEntityTo(entity)
			mensaje:setEntity(playerEventParam.target)
			mensaje:send()
		end
		
		nextState = 3
		
	else if (event == "OnEnemyLost") then
		
		local mensaje = LUA_MAttackDistance()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:setEntity(playerEventParam.target)
		mensaje:send()
	
		nextState = 3
	end
	
	return nextState
end

-- Acción del estado mantener posición.
function playerHoldStateAction(entity)
	local nextState
	nextState = 3
	
	return nextState
end

--------------------------------------------------
--				Estado huyendo					--
--------------------------------------------------

-- Recogida de eventos del estado volviendo.
function playerReturnStateEvent(event, entity)
	local nextState
	
	return nextState
end

-- Acción del estado volviendo.
function playerReturnStateAction(entity)
	local nextState
	
	return nextState
end

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
playerIdleState = { event = playerIdleStateEvent, action = playerIdleStateAction }
playerFollowState = { event = playerFollowStateEvent, action = playerFollowStateAction }
playerHoldState = { event = playerHoldStateEvent, action = playerHoldStateAction }
playerReturnState = { event = playerReturnStateEvent, action = playerReturnStateAction }

-- Tabla con todos los estados.
playerStates = {
	{ name = "idle", state = playerIdleState },
	{ name = "follow", state = playerFollowState },
	{ name = "hold", state = playerHoldState },
	{ name = "return", state = playerReturnState }
}

-- Contiene la distancia a la que está la entidad que se está atacando
distance = 0

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function playerEvent(event, entity)
	local nextState = states[players[entity].state].state.event(event, entity)
	players[entity].state = nextState
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerAIAction(entity)
	local nextState = playerStates[players[entity].state].state.action(entity)
	players[entity].state = nextState
end