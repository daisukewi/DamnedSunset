-- Asignaci�n de la funci�n que se llamar� cuando se quiera mostrar en el GUI
-- las habilidades de Norah
function activateNorahSkills(playerID)
	players[playerID].showGUISkills = showNorahSkills
	
	-- Configuraci�n de los cooldowns de las habilidades.
	-- Cada �ndice corresponde a una habilidad y el valor es el tiempo del cooldown en segundos.
	players[playerID].skillsCooldown = { 
	}
	
	-- Tabla auxiliar para llevar la cuenta del cooldown actual de cada habilidad.
	players[playerID].currentSkillsCooldown = {
	}
end

-- Funci�n que mostrar� las habilidades de Norah en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showNorahSkills()
	cargarBoton(2, "granada", "norahGrenade")
	cargarBoton(4, "jeringa", "norahHeal")
	
	if persSelect ~= 3 then
		cambiarBotones(3)
	end
end

--------------------------------------------------
--			Habilidad granada de Norah			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function norahGrenade()
end

function startNorahGrenade()
end

function explodeNorahGrenade()
end

function cancelNorahGrenade()
end

--------------------------------------------------
--			Habilidad curar de Norah			--
--------------------------------------------------
-- La habilidad curar es de tipo NO INMEDIATO

function norahHeal()
end

function startNorahHeal()
end

function executeNorahHeal()
end

function cancelNorahHeal()
end