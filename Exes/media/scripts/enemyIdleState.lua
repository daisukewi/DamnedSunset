--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle.
function idleStateEvent(event, entity)
-- El estado de idle es el estado 1.
	local nextState

	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
		decideAttack(entity)

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnPlayerLost") then
		-- Teóricamente este caso no se debería dar nunca. Aún así pongo la comprobación.
		enemies[entity].playersSeen[enemyEventParam.target] = false
		decideAttack(entity)

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
		-- Teóricamente este caso no se debería dar nunca. Aún así pongo la comprobación.
		enemies[entity].buildingsSeen[enemyEventParam.target] = false
		decideAttack(entity)

		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
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
	elseif (event == "IASleep") then
		enemies[entity].previousState = 1

		nextState = 5
	elseif (event == "AttackOtherEnemies") then
		enemies[entity].previousState = 1
		nextState = 6
	elseif (event == "AttackJack") then
		enemies[entity].previousState = 1
		nextState = 7
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
	-- Si tengo un punto de destino establecido me muevo hacia él.
	elseif ((math.abs(enemies[entity].destPoint.x - enemies[entity].posX) > 10) or (math.abs(enemies[entity].destPoint.z - enemies[entity].posZ) > 10)) then
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
		-- Si no me tengo que mover no cambio de estado
		nextState = 1
	end

	return nextState
end
