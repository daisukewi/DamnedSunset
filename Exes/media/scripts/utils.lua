------------------------------------------------------
-- Función que calcula la distancia entre dos puntos. El resultado es la suma de la distancia en x y la distancia en z (unidades de ogre)
function calculateDistance(p1X, p1Z, p2X, p2Z)
	local distance = 0
	local difX = 0
	local difZ = 0
	difX = p1X - p2X
	difZ = p1Z - p2Z
	distance = (math.abs(difX) + math.abs(difZ))
	return distance
end

------------------------------------------------------
function goTo(entity, pointX, pointY, pointZ)
	local mensaje = LUA_MAStarRoute()
	mensaje:setEntityTo(entity)
	mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)
	mensaje:send()
end

function stopGoTo(entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setStart(false)
	mensaje:setEntityTo(entity)
	mensaje:send()
end
------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a que jugador atacar.
function decideAttackPlayer(attacker)
	local life = 10000
	enemies[attacker].target = nil
	for playerID, seen in pairs(enemies[attacker].playersSeen) do
		if ((seen) and (players[playerID].life >= 1) and (players[playerID].life < life)) then
			life = players[playerID].life
			enemies[attacker].target = playerID
		end
	end
	
	if (enemies[attacker].target ~= nil) then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemies[attacker].target)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	else
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	end
end

------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a qué edificio atacar.
function decideAttackBuilding(attacker)
	enemies[attacker].target = nil
	for buildingID, seen in pairs(enemies[attacker].buildingsSeen) do
		if (seen) then
			enemies[attacker].target = buildingID
		end
	end
	
	if (enemies[attacker].target ~= nil) then
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(true)
		mensaje:setEntity(enemies[attacker].target)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	else
		local mensaje = LUA_MAttackEntity()
		mensaje:setAttack(false)
		mensaje:setEntityTo(attacker)
		mensaje:send()
	end
end

------------------------------------------------------

-- Función utilizada por la IA de los enemigos para decidir en cada momento a qué atacar.
function decideAttack(attacker)
	-- Primero decido si voy a atacar a algún edificio.
	decideAttackBuilding(attacker)
	
	-- Si he decidido no atacar a ningún edificio, ataco a un jugador.
	if (enemies[attacker].target == nil) then
		decideAttackPlayer(attacker)
	end
end

------------------------------------------------------

-- Función que carga en la interfaz los botones que tiene que utilizar un personaje para realizar sus acciones o habilidades.
function loadPlayerGUI (player)
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)
	
	players[player].showGUISkills()
end

------------------------------------------------------

-- Función que selecciona un nuevo objetivo, actualiza la entidad Dios y manda al GUI mostrar las opciones correspondientes.
-- Devuelve si se ha seleccionado algo o no.
function selectNewTarget(target)

	local selected = false

	--Send selected to new target
	if ((target ~= -1) and (isPlayer(target))) then
		--Select new target
		table.insert(god.playersSelected, target)
	
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(target)
		mensaje:setSelectedEntity(target)
		mensaje:send()

		local mensaje = LUA_MUbicarCamara()
		mensaje:setTarget(target)
		mensaje:send()

		loadPlayerGUI(target)
		
		selected = true
	end
	
	return selected

end

------------------------------------------------------

-- Función que selecciona un objetivo secundario y actualiza la entidad Dios.
-- elve si se ha seleccionado algo o no.
function selectNewSecondTarget(target)

	local selected = false

	if ((target ~= -1) and (isPlayer(target))) then
		--Select new target
		table.insert(god.playersSelected, target)
	
		local selectSecondMensaje = LUA_MEntitySelected()
		selectSecondMensaje:setSelectedType("SECONDARY")
		selectSecondMensaje:setEntityTo(target)
		selectSecondMensaje:setSelectedEntity(target)
		selectSecondMensaje:send()
		
		selected = true
	end
	
	return selected
end

------------------------------------------------------

-- Función que deselecciona todos los jugadores seleccionados.
function unselectCurrentTargets()
	for i, playerID in pairs(god.playersSelected) do
		local mensaje = LUA_MEntitySelected()
		mensaje:setEntityTo(playerID)
		mensaje:setSelectedEntity(0)
		mensaje:send()
	end
	
	god.playersSelected = {}
end

------------------------------------------------------

-- Función que envía un mensaje de movimiento a una entidad concreta.
function sendMovement(point_x, point_y, point_z, entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(point_x)
	mensaje:setDestPointY(point_y)
	mensaje:setDestPointZ(point_z)
	mensaje:setEntityTo(entity)
	mensaje:send()
end

------------------------------------------------------

-- Función que envía un mensaje de ataque a una entidad concreta.
function sendAttack(target, entity)
	local mensaje = LUA_MAttackDistance()
	mensaje:setEntity(target)
	mensaje:setAttack(true)
	mensaje:setEntityTo(entity)
	mensaje:send()
end

------------------------------------------------------

-- Función que resta actualiza el cooldown de todas las habilidades de todos los personajes con el deltaTime
function updateSkillsCooldown(deltaTime)
	for ID, t in pairs(players) do
		for index, value in pairs(t.currentSkillsCooldown) do
			InterfazControles = winMgr:getWindow("InterfazControles/Menu/b" .. index)
			
			urlImageCoolDown = "InterfazControles/Menu/b" .. index .. "/b" .. index .. "cd"
			
			print("urlImageCoolDown: " .. urlImageCoolDown)
			
			if (players[ID].currentSkillsCooldown[index] > 0) then

				porcentaje = players[ID].currentSkillsCooldown[index]/players[ID].skillsCooldown[index]
				
				players[ID].currentSkillsCooldown[index] = players[ID].currentSkillsCooldown[index] - (deltaTime / 1000)
				
				if (ID == god.playersSelected[1]) then

					

					print("Porcentaje: ".. porcentaje)
					
					InterfazControles:getChild(urlImageCoolDown):setHeight(CEGUI.UDim(porcentaje,0))
				end
				
			else
				players[ID].currentSkillsCooldown[index] = 0
				
				if (ID == god.playersSelected[1]) then
					InterfazControles:getChild(urlImageCoolDown):setHeight(CEGUI.UDim(0,0))
				end
				
				
			end
		end
	end
end

------------------------------------------------------