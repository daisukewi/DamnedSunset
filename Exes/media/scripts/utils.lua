------------------------------------------------------
function goTo(entity, pointX, pointY, pointZ)
	local mensaje = LUA_MAStarRoute()
	mensaje:setEntityTo(entity)
	--[[mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)]]
	mensaje:send()
end

function stopGoTo(entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setStart(false)
	mensaje:setEntityTo(entity)
	mensaje:send()
end
------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a que jugador atacar.
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

------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a qué edificio atacar.
function decideAttackBuilding(attacker)
	enemies[attacker].target = nil
	for buildingID, seen in pairs(enemies[attacker].buildingsSeen) do
		if (seen) then
			enemies[attacker].target = buildingID
		end
	end
	
	if (enemies[attacker].target ~= nil) then
		print("Decido atacar a un edificio. Edificio: " .. enemies[attacker].target)
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemies[attacker].target)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	else
		print("Decido NO atacar a un edificio.")
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	end
end

------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a qué atacar.
function decideAttack(attacker)
	-- Primero decido si voy a atacar a algún jugador.
	decideAttackPlayer(attacker)
	
	-- Si he decidido no atacar a ningún jugador, ataco a un edificio.
	if (enemies[attacker].target == nil) then
		decideAttackBuilding(attacker)
	end
end

------------------------------------------------------