--------------------------------------------------
--				Utilidades						--
--------------------------------------------------

function decideAttackPlayer(attacker)
	local life = 10000
	enemies[attacker].target = nil
	for playerID, seen in pairs(enemies[attacker].playersSeen) do
		if ((seen) and (players[playerID].life < life) and (players[playerID].life > 0)) then
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

	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
		decideAttackPlayer(entity)
		
		-- Como he visto al jugador paso al estado de atacando.
		nextState = 2
	elseif (event == "OnPlayerLost") then
		-- Teóricamente este caso no se debería dar nunca. Aún así pongo la comprobación.
		enemies[entity].playersSeen[enemyEventParam.target] = false
		
		nextState = 1
	elseif (event == "EnemyMindMove") then
		-- Establezco el punto de destino.
		enemies[entity].destPoint = {
			x = enemyEventParam.x,
			y = enemyEventParam.y,
			z = enemyEventParam.z
		}
		
		-- Envío el mensaje de movimiento.
		local mensaje = LUA_MAStarRoute()
		mensaje:setDestPointX(enemies[entity].destPoint.x)
		mensaje:setDestPointY(enemies[entity].destPoint.y)
		mensaje:setDestPointZ(enemies[entity].destPoint.z)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		-- Como me estoy moviendo paso al estado de moviéndome.
		nextState = 3
	else
		-- No me ha interesado ningún evento, me quedo en el estado de idle.
		nextState = 1
	end
	
	return nextState
end

-- Acción del estado idle.
function idleStateAction(entity)
-- El estado de idle es el estado 1.
	local nextState
	
	-- Si mi vida es menor que el umbral empiezo a huir.
	-- Hago esta comprobación antes que nada porque quiero que el estado de huir sea el mas prioritario de todos.
	if (enemies[entity].life <= enemies[entity].runLifeThreshold) then
		-- Envío el mensaje de movimiento a mi punto de origen (me vuelvo a mi casa a refugiarme)
		local mensaje = LUA_MAStarRoute()
		mensaje:setDestPointX(enemies[entity].initPoint.x)
		mensaje:setDestPointY(enemies[entity].initPoint.y)
		mensaje:setDestPointZ(enemies[entity].initPoint.z)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		nextState = 4
	-- Compruebo si me tengo que mover a mi punto inicial y si estoy en él. En caso de no ser así me muevo hasta allí.
	elseif (enemies[entity].backToInitPoint) then
		if ((math.abs(enemies[entity].initPoint.x - enemies[entity].posX) > 10) or (math.abs(enemies[entity].initPoint.z - enemies[entity].posZ) > 10)) then
			-- Establezco el punto de destino.
			enemies[entity].destPoint = {
				x = enemies[entity].initPoint.x,
				y = enemies[entity].initPoint.y,
				z = enemies[entity].initPoint.z
			}
			
			-- Envío el mensaje de movimiento.
			local mensaje = LUA_MAStarRoute()
			mensaje:setDestPointX(enemies[entity].destPoint.x)
			mensaje:setDestPointY(enemies[entity].destPoint.y)
			mensaje:setDestPointZ(enemies[entity].destPoint.z)
			mensaje:setEntityTo(entity)
			mensaje:send()
			
			-- Como me estoy moviendo paso al estado de moviéndome.
			nextState = 3
		else
			-- Si ya estoy en el punto que quiero no cambio de estado.
			nextState = 1
		end
	else
		-- Si no me tengo que mover no cambio de estado
		nextState = 1
	end
	
	return nextState
end

--------------------------------------------------
--				Estado atacando					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function attackStateEvent(event, entity)
-- El estado de atacando es el estado 2.
	local nextState
	
	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
		decideAttackPlayer(entity)
		
		-- Como he visto a otro jugador mientras estaba atacando me quedo en el estado actual.
		nextState = 2
	elseif (event == "OnPlayerLost") then
		enemies[entity].playersSeen[enemyEventParam.target] = false
		decideAttackPlayer(entity)
		
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnPlayerDeath") then
		decideAttackPlayer(entity)
		
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	else
		-- Como no me interesa ningún evento me quedo en el estado actual.
		nextState = 2
	end
	
	return nextState
end

-- Acción del estado atacando.
function attackStateAction(entity)
-- El estado de atacando es el estado 2.
	local nextState
	
	-- Si mi vida es menor que el umbral empiezo a huir.
	-- Hago esta comprobación antes que nada porque quiero que el estado de huir sea el mas prioritario de todos.
	if (enemies[entity].life <= enemies[entity].runLifeThreshold) then
		-- Envío el mensaje para que deje de atacar
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()
	
		-- Envío el mensaje de movimiento a mi punto de origen (me vuelvo a mi casa a refugiarme)
		local mensaje = LUA_MAStarRoute()
		mensaje:setDestPointX(enemies[entity].initPoint.x)
		mensaje:setDestPointY(enemies[entity].initPoint.y)
		mensaje:setDestPointZ(enemies[entity].initPoint.z)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		nextState = 4
	else
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	end
	
	return nextState
end

--------------------------------------------------
--				Estado moviendo					--
--------------------------------------------------

-- Recogida de eventos del estado moviendo.
function moveStateEvent(event, entity)
-- El estado de moviendo es el estado 3.
	local nextState

	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
		decideAttackPlayer(entity)
		
		-- Como he visto al enemigo mientras me movía paso al estado de atacando.
		nextState = 2
	elseif (event == "OnPlayerLost") then
		-- Teóricamente este caso no se debería dar nunca. Aún así pongo la comprobación.
		enemies[entity].playersSeen[enemyEventParam.target] = false
		
		nextState = 3
	else
		-- Como no me interesa ningún evento me quedo en el estado actual.
		nextState = 3
	end
	
	return nextState
end

-- Acción del estado moviendo.
function moveStateAction(entity)
-- El estado de moviendo es el estado 3.
	local nextState
	
	-- Si mi vida es menor que el umbral empiezo a huir.
	-- Hago esta comprobación antes que nada porque quiero que el estado de huir sea el mas prioritario de todos.
	if (enemies[entity].life <= enemies[entity].runLifeThreshold) then
		-- Envío el mensaje de movimiento a mi punto de origen (me vuelvo a mi casa a refugiarme)
		local mensaje = LUA_MAStarRoute()
		mensaje:setDestPointX(enemies[entity].initPoint.x)
		mensaje:setDestPointY(enemies[entity].initPoint.y)
		mensaje:setDestPointZ(enemies[entity].initPoint.z)
		mensaje:setEntityTo(entity)
		mensaje:send()
		
		nextState = 4
	elseif ((math.abs(enemies[entity].destPoint.x - enemies[entity].posX) < 10) and (math.abs(enemies[entity].destPoint.z - enemies[entity].posZ) < 10)) then
		-- Como ya he llegado a mi destino paso al estado de idle.
		nextState = 1
	else
		-- Si todavía no he llegado a mi destino me quedo en el estado actual.
		nextState = 3
	end
	
	return nextState
end

--------------------------------------------------
--				Estado huyendo					--
--------------------------------------------------

-- Recogida de eventos del estado huyendo.
function runStateEvent(event, entity)
-- El estado de huyendo es el estado 4.
	local nextState

	-- En principio no hay ningún evento que me haga salir de este estado pero pongo
	-- las comprobaciones para no perder la congruencia de los datos por si salgo por
	-- otros motivos.
	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
	elseif (event == "OnPlayerLost") then
		enemies[entity].playersSeen[enemyEventParam.target] = false
	end
	
	nextState = 4
	
	return nextState
end

-- Acción del estado huyendo.
function runStateAction(entity)
-- El estado de huyendo es el estado 4.
	local nextState
	
	if (enemies[entity].life > enemies[entity].runLifeThreshold) then
		-- Si en algún momento mi vida es mayor que el umbral vuelvo al estado de idle.
		nextState = 1
	else
		-- En cualquier otro caso sigo huyendo, por lo que me quedo en el estado actual.
		nextState = 4
	end
	
	return nextState
end

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
idleState = { event = idleStateEvent, action = idleStateAction }
attackState = { event = attackStateEvent, action = attackStateAction }
moveState = { event = moveStateEvent, action = moveStateAction }
runState = { event = runStateEvent, action = runStateAction }

-- Tabla con todos los estados.
states = {
	{ name = "idle", state = idleState },
	{ name = "attack", state = attackState },
	{ name = "move", state = moveState },
	{ name = "run", state = runState }
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