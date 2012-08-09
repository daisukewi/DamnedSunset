--------------------------------------------------
--				Estado de building				--
--------------------------------------------------

-- Recogida de eventos del estado building de god.
function godBuildingStateEvent(event)
-- El estado de building es el estado 4.
	local nextState
	
	-- Evento de click de selección.
	if (event == "OnSelectionClick") then
		-- Si recibo un evento de selección (click izquierdo) mando construir el edificio actual.
		emplaceBuild()
		
		-- Paso al estado idle.
		nextState = 1
	-- Evento de click de acción.
	elseif (event == "OnActionClick") then
		-- Si recibo un evento de acción (click derecho) cancelo la construcción del edificio actual.
		cancelBuild()
		
		-- Paso al estado de idle.
		nextState = 1
	-- Evento de construcción de edificio
	elseif (event == "OnStartBuild") then
		-- Si recibo otro evento de empezar a construir cancelo el edificio actual y empiezo a construir el nuevo.
		cancelBuild()
		startBuild(buildParameters.building)
		
		-- Me quedo en el estado actual.
		nextState = 4
	else
		nextState = 4
	end
	
	return nextState
end

-- Acción del estado build de god.
function godBuildingStateAction()
-- El estado de build es el estado 4.
	local nextState = 4
	
	return nextState
end