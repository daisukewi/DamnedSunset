-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Erick
function activateErickSkills(playerID)
	players[playerID].showGUISkills = showErickSkills

	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = {
		[3] = 5,
	}

	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[3] = 0,
	}
end

-- Función que mostrará las habilidades de Erick en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showErickSkills()
	cargarBoton(2, "granada", "erickGrenade")
	cargarBoton(3, "bolazul", "bulletTime")
	cargarBoton(4, "granada", "erickPowerShoot")

	if persSelect ~= 2 then
		cambiarBotones(2)
	end
end

--------------------------------------------------
--			Habilidad granada de Erick			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function erickGrenade()
end

function startErickGrenade()
end

function explodeErickGrenade()
end

function cancelErickGrenade()
end

--------------------------------------------------
--		Habilidad bullet time de Erick			--
--------------------------------------------------
-- La habilidad de bullet time es de tipo INMEDIATO

function bulletTime()
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
	print("erickPowerShoot")
	godEvent("OnSkillClick")
end

function startErickPowerShoot()
	god.finishSkillFunction = explodeErickPowerShoot
	god.cancelSkillFunction = cancelErickPowerShoot
	god.clickTarget = nil

	startPowerShoot(god.playersSelected[1])
	print("startErickPowerShoot")
end

function explodeErickPowerShoot()
	launchPowerShoot(god.playersSelected[1])
	--print("god.selected")
	--print(god.selected)
end

function cancelErickPowerShoot()
	cancelPowerShoot(god.playersSelected[1])
end
