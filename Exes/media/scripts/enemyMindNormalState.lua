--------------------------------------------------
--				Estado normal					--
--------------------------------------------------

-- Recogida de eventos del estado normal.
function normalStateEvent(event)
-- El estado de normal es el estado 1.
	local nextState
	
	if (event == "GeneratorUnderAttack") then
		sacarVentana("Soy la supermente y me ha llegado el evento de que están atacando un generador.")
		-- Obtengo la tabla de spawners para la entidad que me ha enviado el evento.
		tSpawners = enemyBuildings[enemyMindEventParam.entity].spawners
		
		-- Por cada spawner en la lista de spawners, mando spawnear dos enemigos.
		for spawnIndex, t in pairs(tSpawners) do
			spawnID = spawners[t.ID].entityID
			
			local mensaje = LUA_MSpawnEnemy()
			mensaje:setNumEnemies(2)
			mensaje:setEntityTo(spawnID)
			mensaje:send()
		end
	end
	
	nextState = 1
	
	return nextState
end

-- Acción del estado normal.
function normalStateAction()
-- El estado de normal es el estado 1.
	local nextState
	
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
						x = 0,
						y = 5,
						z = 0
					}
					enemyEvent("EnemyMindMove", tEnemy.ID)
					t.attackEnemies = t.attackEnemies - 1
				end
			end
		end
	end
	
	nextState = 1
	
	return nextState
end