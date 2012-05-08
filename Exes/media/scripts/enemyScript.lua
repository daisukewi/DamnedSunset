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
		
		-- Como he visto al jugador paso al estado de atacando.
		nextState = 2
	else
		-- No me ha interesado ningún evento, me quedo en el estado de idle.
		nextState = 1
	end
	
	return nextState;
end

-- Acción del estado idle.
function idleStateAction(entity)
-- El estado de idle es el estado 1.
	local nextState;
	
	-- Compruebo si me tengo que mover a mi punto inicial y si estoy en él. En caso de no ser así me muevo hasta allí.
	if (enemies[entity].backToInitPoint) then
		print(enemies[entity].initPoint.x .. " " .. enemies[entity].posX .. " " .. enemies[entity].initPoint.z .. " " .. enemies[entity].posZ)
		if ((enemies[entity].initPoint.x ~= enemies[entity].posX) or (enemies[entity].initPoint.z ~= enemies[entity].posZ)) then
			print("Volviendo DE VERDAD")
			local mensaje = LUA_MAStarRoute()
			mensaje:setDestPointX(enemies[entity].initPoint.x)
			mensaje:setDestPointY(enemies[entity].initPoint.y)
			mensaje:setDestPointZ(enemies[entity].initPoint.z)
			mensaje:setEntityTo(entity)
			mensaje:send()
			
			-- Como me estoy moviendo paso al estado de moviendome.
			nextState = 3
		else
			-- Si ya estoy en el punto que quiero no cambio de estado.
			nextState = 1
		end
	else
		-- Si no me tengo que mover no cambio de estado
		nextState = 1
	end
	
	return nextState;
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
		
		-- Como he perdido de vista al jugador paso al estado de idle.
		nextState = 1
	else
		-- Como no me interesa ningún evento me quedo en el estado actual.
		nextState = 2
	end
	
	return nextState;
end

-- Acción del estado atacando.
function attackStateAction(entity)
-- El estado de atacando es el estado 2.
	return 2
end

-- Recogida de eventos del estado moviendo.
function moveStateEvent(event, entity)
-- El estado de moviendo es el estado 3.
	local nextState;

	if (event == "OnPlayerSeen") then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemyEventParam.target)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		-- Como he visto al enemigo mientras me movía paso al estado de atacando.
		nextState = 2
	else
		-- Como no me interesa ningún evento me quedo en el estado actual.
		nextState = 3
	end
	
	return nextState;
end

-- Acción del estado moviendo.
function moveStateAction(entity)
-- El estado de moviendo es el estado 3.
	local nextState;
	
	if ((enemies[entity].initPoint.x == enemies[entity].posX) and (enemies[entity].initPoint.z == enemies[entity].posZ)) then
		-- Como ya he llegado a mi destino paso al estado de idle.
		nextState = 1
	else
		-- Si todavía no he llegado a mi destino me quedo en el estado actual.
		nextState = 3
	end
	
	return nextState;
end

-- Definición de los distintos estados y sus acciones.
idleState = { event = idleStateEvent, action = idleStateAction }
attackState = { event = attackStateEvent, action = attackStateAction }
moveState = { event = moveStateEvent, action = moveStateAction }

-- Tabla con todos los estados.
states = {
	{ name = "idle", state = idleState },
	{ name = "attack", state = attackState },
	{ name = "move", state = moveState }
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