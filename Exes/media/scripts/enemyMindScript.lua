function launchIA()
	for i = 1, 3 do
		entity = spawners[1].entityID
		print("Entidad a la que se envía el mensaje " .. entity)
		local mensaje = LUA_MSpawnEnemy()
		mensaje:setEntityTo(entity)
		mensaje:send()
	end
end