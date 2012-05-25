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