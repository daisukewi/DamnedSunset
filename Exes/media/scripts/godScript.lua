--Creando tabla de datos de God
God = {
	Selected = -1
}

function processSelection(target, point_x, point_y, point_z)
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
	elseif name == "Erick" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(3, "bolazul", "habilidadRalentizarTiempo")
	elseif name == "Amor" then
		cargarBoton(2, "granada", "habilidadGranada")
		cargarBoton(4, "jeringa", "habilidadCurar")
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