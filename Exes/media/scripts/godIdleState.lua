--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle de god.
function godIdleStateEvent(event)
-- El estado de idle es el estado 1.
	local nextState
	
	-- Evento de click de selección.
	if (event == "OnSelectionClick") then
		-- Solo proceso la selección si el objetivo es distinto del que tengo seleccionado ahora mismo.
		if (god.selected ~= selectionParameters.target) then
			-- Primero deselecciono el objetivo actual.
			unselectCurrentTarget()
			if (selectNewTarget(selectionParameters.target)) then
				-- Si se ha podido seleccionar un objetivo nuevo paso al estado de seleccionado.
				nextState = 2
			else
				-- Si no se ha podido seleccionar nada me quedo en el estado actual.
				nextState = 1
			end
		else
			nextState = 1
		end
	else
		nextState = 1
	end
	
	return nextState
end

-- Acción del estado idle de god.
function godIdleStateAction()
-- El estado de idle es el estado 1.
	local nextState = 1
	
	return nextState
end