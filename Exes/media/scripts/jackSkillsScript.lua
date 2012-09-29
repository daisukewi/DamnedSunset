-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Jack
function activateJackSkills(playerID)
	players[playerID].showGUISkills = showJackSkills

	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = {
		[1] = 30,
		[2] = 10,
		[3] = 10,
		[4] = 60,
	}

	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
	}
end

-- Función que mostrará las habilidades de Jack en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showJackSkills()
	cargarBoton(1, "jackGrenade", "jackGrenade")
	cargarBoton(2, "rabia", "jackEmpuje")
	cargarBoton(3, "burla", "jackBurla")
	cargarBoton(4, "energy", "jackReduceDamage")

	if persSelect ~= 1 or god.playersSelected[1] == getEntityID("Jack") then
		cambiarBotones(1)
	end
end

--------------------------------------------------
--			Habilidad granada de Jack			--
--------------------------------------------------
-- La habilidad de la granada es la número 1
-- La habilidad de la granada es de tipo NO INMEDIATO

function jackGrenade()
	god.startSkillFunction = startJackGrenade
	skillParameters = {
		skill = 1,
	}
	print("jackGrenade")
	godEvent("OnSkillClick")
end

function startJackGrenade()
	god.finishSkillFunction = explodeJackGrenade
	god.cancelSkillFunction = cancelJackGrenade
	god.clickTarget = nil

	startGrenade(god.playersSelected[1], 0, 0, 0)
end

function explodeJackGrenade()
	launchGrenade(god.playersSelected[1], skillParameters.point_x, skillParameters.point_y, skillParameters.point_z)
end

function cancelJackGrenade()
	cancelGrenade(god.playersSelected[1], 0, 0, 0)
end

--------------------------------------------------
--			Habilidad círculo empuje de Jack	--
--------------------------------------------------
-- La habilidad del círculo empuje es la número 2
-- La habilidad del círculo empuje es de tipo INMEDIATO

function jackEmpuje()
	-- Miro si la habilidad está en cooldown y si el personaje está muerto, si lo está no hago nada.
	if ((players[god.playersSelected[1]].currentSkillsCooldown[2] <= 0) and (players[god.playersSelected[1]].life > 0)) then
		empujarCircle(god.playersSelected[1])
		
		-- Activo el cooldown de la habilidad
		players[god.playersSelected[1]].currentSkillsCooldown[2] = players[god.playersSelected[1]].skillsCooldown[2]
	end
end

--------------------------------------------------
--			Habilidad burla de Jack	            --
--------------------------------------------------
-- La habilidad de burla es la número 3
-- La habilidad de burla es de tipo INMEDIATO

function jackBurla()
	-- Miro si la habilidad está en cooldown y si el personaje está muerto, si lo está no hago nada.
	if ((players[god.playersSelected[1]].currentSkillsCooldown[3] <= 0) and (players[god.playersSelected[1]].life > 0)) then
		atacarJack(god.playersSelected[1])
		
		-- Activo el cooldown de la habilidad
		players[god.playersSelected[1]].currentSkillsCooldown[3] = players[god.playersSelected[1]].skillsCooldown[3]
	end
end

--------------------------------------------------
--			Habilidad reducir daño				--
--------------------------------------------------
-- La habilidad de reducir daño es la número 4
-- La habilidad de reducir daño es de tipo INMEDIATO

function jackReduceDamage()
	-- Miro si la habilidad está en cooldown y si el personaje está muerto, si lo está no hago nada.
	if ((players[god.playersSelected[1]].currentSkillsCooldown[4] <= 0) and (players[god.playersSelected[1]].life > 0)) then
		activateReduceDamage(god.playersSelected[1])
		
		-- Activo el cooldown de la habilidad
		players[god.playersSelected[1]].currentSkillsCooldown[4] = players[god.playersSelected[1]].skillsCooldown[4]
	end
end
