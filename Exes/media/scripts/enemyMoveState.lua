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

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnPlayerLost") then
		-- Te�ricamente este caso no se deber�a dar nunca. A�n as� pongo la comprobaci�n.
		enemies[entity].playersSeen[enemyEventParam.target] = false

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnBuildingSeen") then
		enemies[entity].buildingsSeen[enemyEventParam.target] = true
		decideAttack(entity)

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnBuildingLost") then
		-- Te�ricamente este caso no se deber�a dar nunca. A�n as� pongo la comprobaci�n.
		enemies[entity].buildingsSeen[enemyEventParam.target] = false
		decideAttack(entity)

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "IASleep") then
		enemies[entity].previousState = 3

		stopGoTo(entity)

		nextState = 5
	elseif (event == "AttackOtherEnemies") then
		enemies[entity].previousState = 3
		nextState = 6
	elseif (event == "AttackJack") then
		enemies[entity].previousState = 3
		nextState = 7
	else
		-- Como no me interesa ning�n evento me quedo en el estado actual.
		nextState = 3
	end

	return nextState
end

-- Acci�n del estado moviendo.
function moveStateAction(entity)
-- El estado de moviendo es el estado 3.
	local nextState

	-- Si mi vida es menor que el umbral empiezo a huir.
	-- Hago esta comprobaci�n antes que nada porque quiero que el estado de huir sea el mas prioritario de todos.
	if (enemies[entity].life <= enemies[entity].runLifeThreshold) then
		-- Env�o el mensaje de movimiento a mi punto de origen (me vuelvo a mi casa a refugiarme)
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
		-- Si todav�a no he llegado a mi destino me quedo en el estado actual.
		nextState = 3
	end

	return nextState
end
