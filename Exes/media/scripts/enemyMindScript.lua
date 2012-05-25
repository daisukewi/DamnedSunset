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
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
normalState = { event = normalStateEvent, action = normalStateAction }

-- Tabla con todos los estados.
enemyMindStates = {
	{ name = "normal", state = normalState },
}

-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados de la supermente.
function enemyMindEvent(event)
	local nextState = enemyMindStates[enemyMind.state].state.event(event)
	enemyMind.state = nextState
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual de la supermente
function enemyMindAIAction()
	local nextState = enemyMindStates[enemyMind.state].state.action()
	enemyMind.state = nextState
end