--------------------------------------------------
--				Estado atacando					--
--------------------------------------------------

-- Recogida de eventos del estado atacando.
function attackStateEvent(event, entity)
-- El estado de atacando es el estado 2.
	local nextState
	
	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
		decideAttack(entity)
		
		-- Como he visto a otro jugador mientras estaba atacando me quedo en el estado actual.
		nextState = 2
	elseif (event == "OnPlayerLost") then
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
		enemies[entity].buildingsSeen[enemyEventParam.target] = false
		decideAttack(entity)
		
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnPlayerDeath") then
		decideAttack(entity)
		
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "OnBuildingDestroy") then
		print("Recibo que se ha destruido un edificio")
		enemies[entity].buildingsSeen[enemyEventParam.buildingDestroy] = false
		decideAttack(entity)
		
		-- Decido a que estado voy en base a si tengo objetivo o no.
		if (enemies[entity].target == nil) then
			nextState = 1
		else
			nextState = 2
		end
	elseif (event == "IASleep") then
		enemies[entity].previousState = 2
		
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(attacker)
		mensaje:send()
		
		nextState = 5
	elseif (event == "AttackOtherEnemies") then
		enemies[entity].previousState = 2
		nextState = 6
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