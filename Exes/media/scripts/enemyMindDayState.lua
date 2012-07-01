--------------------------------------------------
--			Estado de actuaci�n de d�a			--
--------------------------------------------------

-- Recogida de eventos del estado de d�a.
function dayStateEvent(event)
-- El estado de d�a es el estado 2.
	local nextState
	
	-- Por ahora no me interesa ning�n evento mientras estoy en el estado de d�a.
	nextState = 2
	
	return nextState
end

-- Acci�n del estado de d�a.
function dayStateAction()
-- El estado de d�a es el estado 2.
	local nextState
	
	-- Si estoy en el d�a me mantengo en el estado actual sin hacer nada.
	if (day == true) then
		nextState = 2
	else
		-- Si es de noche cambio al estado de noche.
		nextState = 1
	end
	
	return nextState
end