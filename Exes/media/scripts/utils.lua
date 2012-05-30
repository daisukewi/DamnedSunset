------------------------------------------------------
function goTo(entity, pointX, pointY, pointZ)
	local mensaje = LUA_MAStarRoute()
	mensaje:setEntityTo(entity)
	--[[mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)]]
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