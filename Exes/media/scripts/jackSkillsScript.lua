-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Jack
function activateJackSkills(playerID)
	players[playerID].showGUISkills = showJackSkills

	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = {
		[1] = 5,
		[2] = 5,
		[3] = 5,
	}

	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
	}
end

-- Función que mostrará las habilidades de Jack en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showJackSkills()
	cargarBoton(2, "granada", "jackGrenade")
	cargarBoton(3, "bolazul", "jackEmpuje")
	cargarBoton(4, "granada", "jackReduceDamage")
	cargarBoton(1, "bolazul", "jackBurla")

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
	--skillParameters = {
	--	skill = 2,
	--}
	--godEvent("OnSkillClick")

	empujarCircle(god.playersSelected[1])
	print("jackEmpuje")
end

--------------------------------------------------
--			Habilidad reducir daño				--
--------------------------------------------------

function jackReduceDamage()

	activateReduceDamage(god.playersSelected[1])
	print("jackReduceDamage")
end

--------------------------------------------------
--			Habilidad burla de Jack	            --
--------------------------------------------------
-- La habilidad del círculo empuje es de tipo INMEDIATO

function jackBurla()
	atacarJack(god.playersSelected[1])
	print("atacarJack")
end
