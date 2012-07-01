--------------------------------------------------
--			Estado de actuación de día			--
--------------------------------------------------

-- Recogida de eventos del estado de día.
function dayStateEvent(event)
-- El estado de día es el estado 2.
	local nextState
	
	-- Por ahora no me interesa ningún evento mientras estoy en el estado de día.
	nextState = 2
	
	return nextState
end

-- Acción del estado de día.
function dayStateAction()
-- El estado de día es el estado 2.
	local nextState
	
	-- Si estoy en el día me mantengo en el estado actual sin hacer nada.
	if (day == true) then
		nextState = 2
	else
		-- Si es de noche cambio al estado de noche.
		nextState = 1
	end
	
	return nextState
end