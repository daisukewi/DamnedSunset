--------------------------------------------------
--				Estado idle						--
--------------------------------------------------

-- Recogida de eventos del estado idle de god.
function godIdleStateEvent(event)
-- El estado de idle es el estado 1.
	local nextState
	
	-- Evento de click de selecci�n.
	if (event == "OnSelectionClick") then
		-- Solo proceso la selecci�n si el objetivo es distinto del que tengo seleccionado ahora mismo.
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
	-- Evento de construcci�n de edificio
	elseif (event == "OnStartBuild") then
		-- Empiezo a construir el edificio.
		startBuild(buildParameters.building)
	
		-- Paso al estado de construyendo para gestionar la construcci�n del edificio.
		nextState = 4
	else
		nextState = 1
	end
	
	return nextState
end

-- Acci�n del estado idle de god.
function godIdleStateAction()
-- El estado de idle es el estado 1.
	local nextState = 1
	
	return nextState
end