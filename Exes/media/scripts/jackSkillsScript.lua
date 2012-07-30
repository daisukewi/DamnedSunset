-- Asignaci�n de la funci�n que se llamar� cuando se quiera mostrar en el GUI
-- las habilidades de Jack
function activateJackSkills(playerID)
	players[playerID].showGUISkills = showJackSkills
end

-- Funci�n que mostrar� las habilidades de Jack en el GUI con sus correspondientes
-- llamadas a las funciones correspondientes.
function showJackSkills()
	cargarBoton(2, "granada", "jackGrenade")
	
	if persSelect ~= 1 then
		cambiarBotones(1)
	end
end

--------------------------------------------------
--			Habilidad granada de Jack			--
--------------------------------------------------
-- La habilidad de la granada es de tipo NO INMEDIATO

function jackGrenade()
	god.startSkillFunction = startJackGrenade
	god.finishSkillFunction = explodeJackGrenade
	god.cancelSkillFunction = cancelJackGrenade
	god.clickTarget = nil
	godEvent("OnSkillClick")
end

function startJackGrenade()
	startGrenade(god.selected)
end

function explodeJackGrenade()
	launchGrenade(god.selected)
end

function cancelJackGrenade()
	cancelGrenade(god.selected)
end