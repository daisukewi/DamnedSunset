------------------------------------------------------
-- Función que calcula la distancia entre dos puntos. El resultado es la suma de la distancia en x y la distancia en z (unidades de ogre)
function calculateDistance(p1X, p1Z, p2X, p2Z)
	local distance = 0
	local difX = 0
	local difZ = 0
	difX = p1X - p2X
	difZ = p1Z - p2Z
	distance = (math.abs(difX) + math.abs(difZ))
	return distance
end

------------------------------------------------------
function goTo(entity, pointX, pointY, pointZ)
	local mensaje = LUA_MAStarRoute()
	mensaje:setEntityTo(entity)
	mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)
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

-- Función utilizada por la IA de los enemigos para decidir en cada momento a qué atacar.
function decideAttack(attacker)
	-- Primero decido si voy a atacar a algún edificio.
	decideAttackBuilding(attacker)
	
	-- Si he decidido no atacar a ningún edificio, ataco a un jugador.
	if (enemies[attacker].target == nil) then
		decideAttackPlayer(attacker)
	end
end

------------------------------------------------------