--[[function launchIA()
	for i = 1, 2 do
		entity = spawners[1].entityID
		local mensaje = LUA_MSpawnEnemy()
		mensaje:setEntityTo(entity)
		mensaje:send()
	end
end]]

--------------------------------------------------
--				Estado normal						--
--------------------------------------------------

-- Recogida de eventos del estado normal.
function normalStateEvent(event)
-- El estado de normal es el estado 1.
	local nextState
	
	return nextState
end

-- Acci�n del estado normal.
function normalStateAction()
-- El estado de normal es el estado 1.
	local nextState
	
	print("Recibido el tick de la IA de la supermente. Delta time: " .. enemyMind.deltaTime)
	nextState = 1
	
	return nextState
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