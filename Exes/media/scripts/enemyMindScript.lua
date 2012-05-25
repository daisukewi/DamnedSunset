--------------------------------------------------
--				Cosas de debug					--
--------------------------------------------------

function spawnEnemy()
	local mensaje = LUA_MSpawnEnemy()
	mensaje:setNumEnemies(1)
	mensaje:setEntityTo(spawners[1].entityID)
	mensaje:send()
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