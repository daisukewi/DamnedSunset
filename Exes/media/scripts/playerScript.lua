--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function playerIdleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	return 1
end

-- Acci�n del estado idle.
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

-- Acci�n del estado atacando.
function playerFollowStateAction(entity)
	
	local nextState
	
	return nextState
end

--------------------------------------------------
--				Estado moviendo					--
--------------------------------------------------

-- Recogida de eventos del mantener posici�n.
function playerHoldStateEvent(event, entity)
	local nextState
	--print('PLAYERHOLDSTATEEVENT')
	if (event == "OnFollow") then
		
		nextState = 2
	elseif (event == "OnEnemySeen") then
	
		if (players[entity].attackEnemy == playerEventParam.target) then
		
		else
			players[entity].attackEnemy = playerEventParam.target
			
			
			
			local mensaje = LUA_MAttackDistance()
			mensaje:setContinue(true)
			mensaje:setAttack(true)
			mensaje:setEntityTo(entity)
			mensaje:setEntity(playerEventParam.target)
			mensaje:send()
		
		
			print('MENSAJE ENVIADO')
		end
		
		nextState = 3

	else
		nextState = 3
	end
	
	return nextState
end

-- Acci�n del estado mantener posici�n.
function playerHoldStateAction(entity)
	local nextState
	nextState = 3
	
	return nextState
end

--------------------------------------------------
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
playerIdleState = { event = playerIdleStateEvent, action = playerIdleStateAction }
playerFollowState = { event = playerFollowStateEvent, action = playerFollowStateAction }
playerHoldState = { event = playerHoldStateEvent, action = playerHoldStateAction }

-- Tabla con todos los estados.
playerStates = {
	{ name = "idle", state = playerIdleState },
	{ name = "follow", state = playerFollowState },
	{ name = "hold", state = playerHoldState },
}

-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados.
function playerEvent(event, entity)
	--print('playerEvent: ')
	
	if (event == "StateChange") then
		local state
		--print(playerEventParam.state )
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
		local nextState = playerStates[players[entity].state].state.event(event, entity)
		players[entity].state = nextState
	end
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerAIAction(entity)
	local nextState = playerStates[players[entity].state].state.action(entity)
	players[entity].state = nextState
end