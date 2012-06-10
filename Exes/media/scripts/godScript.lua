--Creando tabla de datos de God
God = {
	Selected = -1,
	SecondSelected = -1,
	ThirdSelected = -1
}

GodSelected = -1

-- Procesa la selección múltiple. Los tres parámetros corresponden a los 3 personajes. en caso de que valgan -1, ese persnaje no ha sido seleccionado
function processMultipleSelection(target1, target2, target3)

	-- Si hay un personaje seleccionado
	if (God.Selected ~= -1) then
	
		-- Si se ha vuelto a selecionnar uno de los personajes seleccionados.
		if (target1 == God.Selected) then
			God.SecondSelected = target2
			God.ThirdSelected = target3
		elseif (target2 == God.Selected) then
			God.SecondSelected = target1
			God.ThirdSelected = target3
		elseif (target3 == God.Selected) then
			God.SecondSelected = target1
			God.ThirdSelected = target2
		else
			-- Si no se ha vuelto a seleccionar ninguno de los ya seleccionados
			-- Hacer lo mismo que si no se encuentra ningún personaje seleccionado
			if (target1 ~= -1) then
				selectNewTarget(target1)
				God.SecondSelected = target2
				God.ThirdSelected = target3
			else
				if (target2 ~= -1) then
					selectNewTarget(target2)
					God.SecondSelected = target1
					God.ThirdSelected = target3
				else
					if (target3 ~= -1) then
						selectNewTarget(target3)
						God.SecondSelected = target1
						God.ThirdSelected = target2
					end
				end
			end
		end
		
	-- Si no hay un personaje seleccionado		
	else
		if (target1 ~= -1) then
			selectNewTarget(target1)
			God.SecondSelected = target2
			God.ThirdSelected = target3
		else
			if (target2 ~= -1) then
				selectNewTarget(target2)
				God.SecondSelected = target1
				God.ThirdSelected = target3
			else
				if (target3 ~= -1) then
					selectNewTarget(target3)
					God.SecondSelected = target1
					God.ThirdSelected = target2
				end
			end
		end
	end
	
	setBillboards()
end

function processSelection(target, point_x, point_y, point_z)
	deleteBillboards()
	God.SecondSelected = -1
	God.ThirdSelected = -1
	selectNewTarget(target)
	
end

function processAction(target, point_x, point_y, point_z)
	if point_y ~= -1 then
		if God.Selected ~= -1 and isPlayer(God.Selected) then
			if target ~= -1 and isEnemy(target) then
				sendAttack(target)
			else
				sendMovement(point_x, point_y, point_z)
			end
		end
	end
end

function selectNewTarget(target)
	--Unselect current target
	if God.Selected ~= -1 then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(God.Selected)
		mensaje:setSelectedEntity(0)
		mensaje:send()
	end

	--Select new target
	God.Selected = target

	--Send selected to new target
	if target ~= -1 and isPlayer(target) then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(target)
		mensaje:setSelectedEntity(target)
		mensaje:send()

		local mensaje = LUA_MUbicarCamara()
		mensaje:setTarget(target)
		mensaje:send()

		loadPlayerGUI(target)
	end
	
	GodSelected = God.Selected

end

function unselectCurrentTarget()
	if God.Selected ~= -1 then
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(God.Selected)
		mensaje:setSelectedEntity(0)
		mensaje:send()
	end
end

function loadPlayerGUI (player)
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)

	name = getName(player)
	if name == "Jack" then
		cargarBoton(2, "granada", "habilidadGranada")
		if persSelect ~= 1 then
			cambiarBotones(1)
		end
	elseif name == "Erick" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(3, "bolazul", "habilidadRalentizarTiempo")
		if persSelect ~= 2 then
			cambiarBotones(2)
		end
	elseif name == "Amor" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(4, "jeringa", "habilidadCurar")
		if persSelect ~= 3 then
			cambiarBotones(3)
		end
	end
end

function sendMovement(point_x, point_y, point_z)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(point_x)
	mensaje:setDestPointY(point_y)
	mensaje:setDestPointZ(point_z)
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
end

function sendAttack (target)
	local mensaje = LUA_MAttackDistance()
	mensaje:setEntity(target)
	mensaje:setAttack(true)
	mensaje:setEntityTo(God.Selected)
	mensaje:send()
end

function setBillboards()
	
	if (God.SecondSelected ~= -1) then
		local mensaje1 = LUA_MEntitySelected()
		mensaje1:setEntityTo(God.SecondSelected)
		mensaje1:setSelectedType("SECONDARY")
		mensaje1:setSelectedEntity(God.SecondSelected)
		mensaje1:send()
	
	end
	
	if (God.ThirdSelected ~= -1 ) then
		local mensaje3 = LUA_MEntitySelected()
		mensaje3:setEntityTo(God.ThirdSelected)
		mensaje3:setSelectedType("SECONDARY")
		mensaje3:setSelectedEntity(God.ThirdSelected)
		mensaje3:send()
	end
end

function deleteBillboards()
	if (God.SecondSelected ~= -1) then
		local mensaje1 = LUA_MEntitySelected()
		mensaje1:setEntityTo(God.SecondSelected)
		mensaje1:setSelectedEntity(0)
		mensaje1:send()
	
	end
	
	if (God.ThirdSelected ~= -1 ) then
		local mensaje3 = LUA_MEntitySelected()
		mensaje3:setEntityTo(God.ThirdSelected)
		mensaje3:setSelectedEntity(0)
		mensaje3:send()
	end
end

function processKeyboardEvent(key)
	if (key == "TAB") then
		alternatePlayer()
		setBillboards()
	end
end

-- Función que se encarga de alternar de jugador cuando se pulsa el tabulador
function alternatePlayer()
	if (God.Selected ~= -1) then
		if (God.SecondSelected ~= -1) and (God.ThirdSelected ~= -1) then
			aux = God.Selected
			selectNewTarget( God.SecondSelected)
			God.SecondSelected = God.ThirdSelected
			God.ThirdSelected = aux
		elseif (God.SecondSelected == -1) and (God.ThirdSelected ~= -1) then
			God.SecondSelected = God.Selected
			selectNewTarget( God.ThirdSelected)
			God.ThirdSelected = -1
		elseif (God.SecondSelected ~= -1) and (God.ThirdSelected == -1) then
			aux = God.Selected
			selectNewTarget( God.SecondSelected )
			God.SecondSelected = aux
		end
		
	end
	
	
end