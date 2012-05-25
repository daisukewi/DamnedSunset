------------------------------------------------------
function goTo(pointX, pointY, pointZ, entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)
	mensaje:setEntityTo(entity)
	mensaje:send()
end

------------------------------------------------------
function FSM(t)
  local a = {}
  for _,v in ipairs(t) do
    local old, event, new, action = v[1], v[2], v[3], v[4]
    if a[old] == nil then a[old] = {} end
    a[old][event] = {new = new, action = action}
  end
  return a
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