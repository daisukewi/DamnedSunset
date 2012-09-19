-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Norah
function activateNorahSkills(playerID)
	players[playerID].showGUISkills = showNorahSkills

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
		[2] = 5,
		[3] = 0,
	}
end

-- Función que mostrará las habilidades de Norah en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showNorahSkills()
	cargarBoton(1, "confuse", "norahEnemigosContraEnemigos")
	cargarBoton(2, "norahGrenade", "norahGrenade")
	cargarBoton(3, "healZone", "norahHealZone")
	cargarBoton(4, "heal", "norahHeal")

	if persSelect ~= 3 then
		cambiarBotones(3)
	end
end

--------------------------------------------------
--			Habilidad enemigos contra enemigos de Norah			--
--------------------------------------------------
-- La habilidad de nemigos contra enemigos es de tipo NO INMEDIATO
function norahEnemigosContraEnemigos()
	--Aunque no es de tipo inmediato, de momento hago como si lo fuese y afecta a los de alrededor de ella
	enemigosContraEnemigos(god.playersSelected[1])
end

--------------------------------------------------
--			Habilidad granada de Norah			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function norahGrenade()
	god.startSkillFunction = startNorahGrenade
	skillParameters = {
		skill = 1,
	}
	godEvent("OnSkillClick")
end

function startNorahGrenade()
	god.finishSkillFunction = explodeNorahGrenade
	god.cancelSkillFunction = cancelNorahGrenade
	god.clickTarget = nil

	startGrenade(god.playersSelected[1], 0, 0, 0)
end

function explodeNorahGrenade()
	launchGrenade(god.playersSelected[1], skillParameters.point_x, skillParameters.point_y, skillParameters.point_z)
end

function cancelNorahGrenade()
	cancelGrenade(god.playersSelected[1], 0, 0, 0)
end

--------------------------------------------------
--			Habilidad curar de Norah			--
--------------------------------------------------
-- La habilidad curar es de tipo NO INMEDIATO

function norahHeal()
	god.startSkillFunction = startNorahHeal
	skillParameters = {
		skill = 3,
	}
	godEvent("OnSkillClick")
end

function startNorahHeal()
	god.finishSkillFunction = executeNorahHeal
	god.cancelSkillFunction = cancelNorahHeal
	god.clickTarget = nil
end

function executeNorahHeal()
	startCure(god.playersSelected[1], skillParameters.target)
end

function cancelNorahHeal()
	cancelCure(god.playersSelected[1])
end

--------------------------------------------------
--			Habilidad zon de curación de Norah	--
--------------------------------------------------
-- La habilidad curar es de tipo INMEDIATO

function norahHealZone()

	activateHealZone(god.playersSelected[1])
end
