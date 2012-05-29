--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function playerIdleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	return 1
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

	
	return nextState
end

-- Acción del estado atacando.
function playerFollowStateAction(entity)
	
	local nextState
	
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
	elseif (event == "OnEnemySeen") then
	
		if (playerEventParam.distance < distance) then
			distance = playerEventParam.distance
			
			local mensaje = LUA_MAttackDistance()
			mensaje:setAttack(true)
			mensaje:setEntityTo(entity)
			mensaje:setEntity(playerEventParam.target)
			mensaje:send()
		end
		
		nextState = 3
		
	elseif (event == "OnEnemyLost") then
		
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
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
playerIdleState = { event = playerIdleStateEvent, action = playerIdleStateAction }
playerFollowState = { event = playerFollowStateEvent, action = playerFollowStateAction }
playerHoldState = { event = playerHoldStateEvent, action = playerHoldStateAction }

-- Tabla con todos los estados.
playerStates = {
	{ name = "idle", state = playerIdleState },
	{ name = "follow", state = playerFollowState },
	{ name = "hold", state = playerHoldState },
}

-- Contiene la distancia a la que está la entidad que se está atacando
distance = 0

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function playerEvent(event, entity)
	print('playerEvent: ')
	
	if (event == "StateChange") then
		local state
		print(playerEventParam.state )
		if (playerEventParam.state == 'idle') then
			state = 1
			print('IDLE')
		elseif (playerEventParam.state == 'follow') then
			state = 2
			print('FOLLOW')
		elseif (playerEventParam.state == 'hold') then
			state = 3
			print('HOLD')
		end
		
		players[entity].state = state
	else
		local nextState = states[players[entity].state].state.event(event, entity)
		players[entity].state = nextState
	end
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerAIAction(entity)
	print('playerAIAction: ')
	local nextState = playerStates[players[entity].state].state.action(entity)
	players[entity].state = nextState
end