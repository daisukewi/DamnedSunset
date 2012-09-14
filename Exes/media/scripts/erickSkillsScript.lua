-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Erick
function activateErickSkills(playerID)
	players[playerID].showGUISkills = showErickSkills

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

-- Función que mostrará las habilidades de Erick en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showErickSkills()
	cargarBoton(2, "granada", "erickGrenade")
	cargarBoton(3, "bolazul", "bulletTime")
	cargarBoton(4, "granada", "erickPowerShoot")
	cargarBoton(1, "bolazul", "erickFlameThrower")

	if persSelect ~= 2 then
		cambiarBotones(2)
	end
end

--------------------------------------------------
--			Habilidad granada de Erick			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function erickGrenade()
	god.startSkillFunction = startNorahGrenade
	skillParameters = {
		skill = 1,
	}
	godEvent("OnSkillClick")
end

function startErickGrenade()
	god.finishSkillFunction = explodeErickGrenade
	god.cancelSkillFunction = cancelErickGrenade
	god.clickTarget = nil

	startGrenade(god.playersSelected[1], 0, 0, 0)
end

function explodeErickGrenade()
	launchGrenade(god.playersSelected[1], 0, 0, 0)
end

function cancelErickGrenade()
	cancelGrenade(god.playersSelected[1], 0, 0, 0)
end

--------------------------------------------------
--		Habilidad bullet time de Erick			--
--------------------------------------------------
-- La habilidad de bullet time es de tipo INMEDIATO

function bulletTime()
	activateBulletTime(god.playersSelected[1])
	print("bulletTime")
end

--------------------------------------------------
--	  Habilidad disparos potentes de Erick		--
--------------------------------------------------
-- La habilidad disparos potentes es la número 3
-- La habilidad disparos potentes es de tipo NO INMEDIATO

function erickPowerShoot()
	god.startSkillFunction = startErickPowerShoot
	skillParameters = {
		skill = 3,
	}
	godEvent("OnSkillClick")
end

function startErickPowerShoot()
	god.finishSkillFunction = explodeErickPowerShoot
	god.cancelSkillFunction = cancelErickPowerShoot
	god.clickTarget = nil

	startPowerShoot(god.playersSelected[1], 0, 0, 0)
end

function explodeErickPowerShoot()
	launchPowerShoot(god.playersSelected[1], skillParameters.point_x, skillParameters.point_y, skillParameters.point_z)
end

function cancelErickPowerShoot()
	cancelPowerShoot(god.playersSelected[1], 0, 0, 0)
end

--------------------------------------------------
--	      Habilidad lanzallamas de Erick		--
--------------------------------------------------
-- La habilidad lanzallamas es la número 2
-- La habilidad lanzallamas es de tipo NO INMEDIATO

function erickFlameThrower()
	god.startSkillFunction = startErickFlameThrower
	skillParameters = {
		skill = 2,
	}
	print("erickFlameThrower")
	godEvent("OnSkillClick")
end

function startErickFlameThrower()
	god.finishSkillFunction = burnErickFlameThrower
	god.cancelSkillFunction = cancelErickFlameThrower
	god.clickTarget = nil

	startFlameThrower(god.playersSelected[1])
end

function burnErickFlameThrower()
	launchFlameThrower(god.playersSelected[1], skillParameters.point_x, skillParameters.point_y, skillParameters.point_z)
end

function cancelErickFlameThrower()
	cancelFlameThrower(god.playersSelected[1])
end
