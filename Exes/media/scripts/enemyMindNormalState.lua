--------------------------------------------------
--				Estado normal					--
--------------------------------------------------

-- Recogida de eventos del estado normal.
function normalStateEvent(event)
-- El estado de normal es el estado 1.
	local nextState
	
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