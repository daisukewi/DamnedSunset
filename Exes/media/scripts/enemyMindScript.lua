--------------------------------------------------
--				Estado normal						--
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
		if (t.spawnTime >= stages[enemyMind.stage].spawnTime[spawnID]) then 
			-- Spawneo los enemigos en el spawner correspondiente.
			local spawnEnemies = stages[enemyMind.stage].spawnEnemies[spawnID]
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
						x = 200,
						y = 5,
						z = -200
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

--------------------------------------------------
--				Máquina de estados				--
--------------------------------------------------

-- Definición de los distintos estados y sus acciones.
normalState = { event = normalStateEvent, action = normalStateAction }

-- Tabla con todos los estados.
enemyMindStates = {
	{ name = "normal", state = normalState },
}

-- Función que recogerá los eventos a los cuales reaccionará la máquina de estados de la supermente.
function enemyMindEvent(event)
	local nextState = enemyMindStates[enemyMind.state].state.event(event)
	enemyMind.state = nextState
end

-- Función que se llamará en cada tick para ejecutar las acciones que haga falta en el estado actual de la supermente
function enemyMindAIAction()
	local nextState = enemyMindStates[enemyMind.state].state.action()
	enemyMind.state = nextState
end