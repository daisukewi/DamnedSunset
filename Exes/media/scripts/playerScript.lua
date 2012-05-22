--------------------------------------------------
--				Utilidades						--
--------------------------------------------------

function decideAttackPlayer(attacker)
	local life = 10000
	enemies[attacker].target = nil
	for playerID, seen in pairs(enemies[attacker].playersSeen) do
		if ((seen) and (players[playerID].life >= 1) and (players[playerID].life < life)) then
			life = players[playerID].life
			enemies[attacker].target = playerID
		end
	end
	
	if (enemies[attacker].target ~= nil) then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemies[attacker].target)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	else
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	end
end

--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function idleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	if (event == "OnFollow") then
		
		nextState = 2
	elseif (event == "OnHold") then

		nextState = 3
	end
	
	return nextState
end

-- Acción del estado idle.
function idleStateAction(entity)
	
	return 1
end

--------------------------------------------------
--				Estado atacando					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function followStateEvent(event, entity)

	
	return nextState
end

-- Acción del estado atacando.
function followStateAction(entity)

	
	return nextState
end

--------------------------------------------------
--				Estado moviendo					--
--------------------------------------------------

-- Recogida de eventos del estado moviendo.
function holdStateEvent(event, entity)

	return nextState
end

-- Acción del estado moviendo.
function holdStateAction(entity)

	
	return nextState
end

--------------------------------------------------
--				Estado huyendo					--
--------------------------------------------------

-- Recogida de eventos del estado huyendo.
function returnStateEvent(event, entity)

	
	return nextState
end

-- Acción del estado huyendo.
function returnStateAction(entity)

	return nextState
end

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
idleState = { event = idleStateEvent, action = idleStateAction }
followState = { event = followStateEvent, action = followStateAction }
holdState = { event = holdStateEvent, action = holdStateAction }
returnState = { event = returnStateEvent, action = returnStateAction }

-- Tabla con todos los estados.
states = {
	{ name = "idle", state = idleState },
	{ name = "follow", state = followState },
	{ name = "hold", state = holdState },
	{ name = "return", state = returnState }
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados.
function playerEvent(event, entity)
	local nextState = states[players[entity].state].state.event(event, entity)
	players[entity].state = nextState
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual.
function playerAIAction(entity)
	local nextState = states[players[entity].state].state.action(entity)
	players[entity].state = nextState
end