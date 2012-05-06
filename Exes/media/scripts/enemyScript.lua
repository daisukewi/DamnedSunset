function onPlayerSeen(entity, playerSeen)
	player = ""
	for key, value in pairs(players) do
		if (value.ID == playerSeen) then
			player = key;
		end
	end
	print("Soy el enemigo " .. entity .. " y veo a " .. player)
end