--------------------------------------------------------
--	Estado de un enemigo cuando está atacando a Jack  --
--------------------------------------------------------

-- Recogida de eventos del estado attackingJack.
function attackingJackStateEvent(event, entity)
	local nextState
	nextState = 7

	if (event == "OnPlayerSeen") then
		enemies[entity].playersSeen[enemyEventParam.target] = true
	elseif (event == "OnPlayerLost") then
		enemies[entity].playersSeen[enemyEventParam.target] = false
	elseif (event == "OnBuildingSeen") then
		enemies[entity].buildingsSeen[enemyEventParam.target] = true
	elseif (event == "OnBuildingLost") then
		enemies[entity].buildingsSeen[enemyEventParam.target] = false
	elseif (event == "IASleep") then
		enemies[entity].previousState = 7

		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()

		nextState = 5
	elseif (event == "AttackOtherEnemies") then
		enemies[entity].previousState = 7

		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()

		nextState = 6
	end

	return nextState
end

-- Acción del estado attackingJack.
function attackingJackStateAction(entity)
	if (not enemies[entity].stopEffect) then
		enemies[entity].stopEffect = Archetype.Jack.timeBurla
	end

	enemies[entity].stopEffect = enemies[entity].stopEffect - enemies[entity].deltaTime

	local nextState
	nextState = 7

	if (enemies[entity].stopEffect < 0) then
		enemies[entity].stopEffect = nil

		--Decimos que pare de atacar
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(entity)
		mensaje:send()
		print("Dejo de atacar a Jack")

		nextState = enemies[entity].previousState
	end

	return nextState
end
