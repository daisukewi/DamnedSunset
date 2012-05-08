function onPlayerSeen(entity, playerSeen)
	player = ""
	for key, value in pairs(players) do
		if (value.ID == playerSeen) then
			player = key;
		end
	end
	print("Soy el enemigo " .. entity .. " y veo a " .. player)
	
	local mensaje = LUA_MAttackEntity()
	mensaje:setAttack(true)
	mensaje:setEntity(playerSeen)
	mensaje:setEntityTo(entity)
	mensaje:send()
end

function onPlayerLost(entity, playerLost)
	player = ""
	for key, value in pairs(players) do
		if (value.ID == playerLost) then
			player = key;
		end
	end
	print("Soy el enemigo " .. entity .. " y he dejado de ver a " .. player)
	
	local mensaje = LUA_MAttackEntity()
	mensaje:setAttack(false)
	mensaje:setEntity(playerLost)
	mensaje:setEntityTo(entity)
	mensaje:send()
end