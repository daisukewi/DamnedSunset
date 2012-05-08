function launchIA()
	for i = 1, 1 do
		entity = spawners[1].entityID
		local mensaje = LUA_MSpawnEnemy()
		mensaje:setEntityTo(entity)
		mensaje:send()
	end
end