--------------------------------------------------
--			Estado de actuación de noche		--
--------------------------------------------------

-- Recogida de eventos del estado de noche.
function nightStateEvent(event)
-- El estado de noche es el estado 1.
	local nextState
	
	if (event == "GeneratorUnderAttack") then
		-- Obtengo la tabla de spawners para la entidad que me ha enviado el evento.
		tSpawners = enemyBuildings[enemyMindEventParam.entity].spawners
		
		-- Por cada spawner en la lista de spawners, mando spawnear dos enemigos.
		for spawnIndex, t in pairs(tSpawners) do
			spawnID = specialSpawners[t.ID].entityID
			
			local mensaje = LUA_MSpawnEnemy()
			mensaje:setNumEnemies(2)
			mensaje:setEntityTo(spawnID)
			mensaje:send()
		end
	end
	
	nextState = 1
	
	return nextState
end

-- Acción del estado de noche.
function nightStateAction()
-- El estado de noche es el estado 1.
	local nextState
	
	-- Si estoy por la noche sigo con el comportamiento normal de la supermente.
	if (day == false) then
		for spawnID, t in pairs(spawners) do
			-- Sumo el deltaTime a cada spawner dividido entre 1000 para sumar segundos.
			t.spawnTime = t.spawnTime + (enemyMind.deltaTime / 1000)
			
			-- Compruebo la tabla de spawners para ver si hay que spawnear o no.
			if (t.spawnTime >= stages[currentStage].spawnTime[spawnID]) then 
				-- Spawneo los enemigos en el spawner correspondiente.
				local spawnEnemies = stages[currentStage].spawnEnemies[spawnID]
				local entity = t.entityID
				
				local mensaje = LUA_MSpawnEnemy()
				mensaje:setNumEnemies(spawnEnemies)
				mensaje:setEntityTo(entity)
				mensaje:send()
				
				-- Anoto los enemigos que tengo que mandar a atacar.
				t.attackEnemies = t.attackEnemies + spawnEnemies
				
				-- Reinicio el tiempo del spawner
				t.spawnTime = 0
			end
			
			-- Compruebo si tengo que mandar enemigos a atacar.
			if (t.attackEnemies > 0) then
				for enemy, tEnemy in pairs(t.enemies) do
					if ((enemies[tEnemy.ID].state == 1) and (t.attackEnemies > 0)) then
						-- Modifico el comportamiento del enemigo para que no vuelva al punto de spawn en caso de quedarse en idle.
						enemies[tEnemy.ID].backToInitPoint = false
						
						-- Establezco el punto de ataque, envío el evento al enemigo y resto el conteo de enemigos.
						enemyEventParam = {
							x = playerBase.position.x,
							y = playerBase.position.y,
							z = playerBase.position.z
						}
						enemyEvent("EnemyMindMove", tEnemy.ID)
						t.attackEnemies = t.attackEnemies - 1
					end
				end
			end
		end
		
		nextState = 1
	else
		-- Si es de día cambio al estado de comportamiento del día.
		nextState = 2
	end
	
	return nextState
end