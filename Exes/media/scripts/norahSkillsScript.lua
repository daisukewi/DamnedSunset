-- Asignación de la función que se llamará cuando se quiera mostrar en el GUI
-- las habilidades de Norah
function activateNorahSkills(playerID)
	players[playerID].showGUISkills = showNorahSkills

	-- Configuración de los cooldowns de las habilidades.
	-- Cada índice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = {
		[1] = 20,
		[2] = 30,
		[3] = 30,
		[4] = 70,
	}

	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
	}
end

-- Función que mostrará las habilidades de Norah en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showNorahSkills()
	cargarBoton(1, "norahGrenade", "norahGrenade")
	cargarBoton(2, "confuse", "norahEnemigosContraEnemigos")
	cargarBoton(3, "heal", "norahHeal")
	cargarBoton(4, "healZone", "norahHealZone")

	if persSelect ~= 3 then
		cambiarBotones(3)
	end
end

--------------------------------------------------
--			Habilidad granada de Norah			--
--------------------------------------------------
-- La habilidad de la granada es la número 1
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
--		Habilidad confusión de Norah			--
--------------------------------------------------
-- La habilidad de confusión es la número 2
-- La habilidad de confusión es de tipo INMEDIATO

function norahEnemigosContraEnemigos()
	-- Miro si la habilidad está en cooldown y si el personaje está muerto, si lo está no hago nada.
	if ((players[god.playersSelected[1]].currentSkillsCooldown[2] <= 0) and (players[god.playersSelected[1]].life > 0)) then
		--Aunque no es de tipo inmediato, de momento hago como si lo fuese y afecta a los de alrededor de ella
		enemigosContraEnemigos(god.playersSelected[1])
		
		-- Activo el cooldown de la habilidad
		players[god.playersSelected[1]].currentSkillsCooldown[2] = players[god.playersSelected[1]].skillsCooldown[2]
	end
end

--------------------------------------------------
--			Habilidad curar de Norah			--
--------------------------------------------------
-- La habilidad de curar es la número 3
-- La habilidad de curar es de tipo NO INMEDIATO

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
--		Habilidad curación de masas de Norah	--
--------------------------------------------------
-- La habilidad de cuarción de masas es la número 4
-- La habilidad de curación de masas es de tipo INMEDIATO

function norahHealZone()
	-- Miro si la habilidad está en cooldown y si el personaje está muerto, si lo está no hago nada.
	if ((players[god.playersSelected[1]].currentSkillsCooldown[4] <= 0) and (players[god.playersSelected[1]].life > 0)) then
		-- HACK: pongo la cantidad de curación que hago con la curación de masas aquí directamente. Es una guarrada superlativa pero no hay tiempo para otra cosa.
		activateMassHeal(god.playersSelected[1], 500)
		
		-- Activo el cooldown de la habilidad
		players[god.playersSelected[1]].currentSkillsCooldown[4] = players[god.playersSelected[1]].skillsCooldown[4]
	end
end
