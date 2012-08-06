--------------------------------------------------
--				Estado pausado					--
--------------------------------------------------

-- Recogida de eventos del estado pausado.
function pauseStateEvent(event, entity)
	local nextState
	nextState = 5
	
	if (event == "IAAwake") then
		nextState = enemies[entity].previousState
	end
	
	return nextState
end

-- Acción del estado pausado.
function pauseStateAction(entity)
	local nextState
	nextState = 5
	
	return nextState
end