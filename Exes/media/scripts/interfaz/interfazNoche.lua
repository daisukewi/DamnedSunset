function interfazTick(text)
	fpsWindow:setText(text)
	minutos = minutos + 1

	if minutos <= 9 and minutos >= 0 then
		winMgr:getWindow("Interfaz/ToSunsetText"):setText(horas .. " : 0" .. minutos)
	else
		winMgr:getWindow("Interfaz/ToSunsetText"):setText(horas .. " : " .. minutos)
	end

	if minutos == 59 then
		horas = horas + 1
		minutos = -1
		if horas == 24 then
			horas = 00
		end
	end

end

function inicializarInterfazNoche()
	if (interfazNoche) then
		print("WARNING - inicializarInterfazNoche - Interfaz ya inicializada")
	else
		-- Cargamos la interfaz
		winMgr:loadWindowLayout("Interfaz.layout")
		interfazNoche = winMgr:getWindow("Interfaz")

		--Añadimos la interfaz a la interfaz principal
		interfazPrincipal:addChildWindow(interfazNoche)

		-- Asociamos los botones del menú con las funciones que se deben ejecutar.
		winMgr:getWindow("Interfaz/bPersonaje1"):subscribeEvent("Clicked", "sendClickMessage1")
		winMgr:getWindow("Interfaz/bPersonaje2"):subscribeEvent("Clicked", "sendClickMessage2")
		winMgr:getWindow("Interfaz/bPersonaje3"):subscribeEvent("Clicked", "sendClickMessage3")

		-- Cargamos la ventana de texto
		winMgr:loadWindowLayout("VentanaText.layout")
		textWindow = winMgr:getWindow("VentanaText/Ventana")

		sacarVentana("Mision 1: Tenemos que encontrar la forma de salir de aqui.")
		actualizarHorasAmanecer(1000)
	end
end


function activarInterfazNoche()
	if (interfazNoche) then
		-- Activamos la ventana de interfaz
		interfazNoche:setVisible(true)
		interfazNoche:activate()
	end
end

function desactivarInterfazNoche()
	if (interfazNoche) then
		interfazNoche:deactivate()
		interfazNoche:setVisible(false)
	end
end

function actualizarBarraVida(numPersonaje, porcentajeVida)
	urlVida = "Interfaz/iVida" .. numPersonaje
	interfazNoche:getChild(urlVida):setWidth(CEGUI.UDim(porcentajeVida*0.1,0))
end

function sendClickMessage1()
	processSelection(getEntityID("Jack"),0,0,0)
end

function sendClickMessage2()
	processSelection(getEntityID("Erick"),0,0,0)
end

function sendClickMessage3()
	processSelection(getEntityID("Amor"),0,0,0)
end

function cambiarBotones(pers)

	print("Botonesssss")

	if pers == 1 then

		winMgr:getWindow("Interfaz/bPersonaje" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.15,0},{0.09,0},{0.23,0}}")
		interfazNoche:getChild("Interfaz/iVida" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.11,0},{0.09,0},{0.13,0}}")
		interfazNoche:getChild("Interfaz/iEnergia" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.13,0},{0.09,0},{0.15,0}}")
		interfazNoche:getChild("Interfaz/BotonIA1" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.15,0},{0.11,0},{0.17,0}}")
		interfazNoche:getChild("Interfaz/BotonIA2" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.17,0},{0.11,0},{0.2,0}}")
		interfazNoche:getChild("Interfaz/BotonIA3" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.2,0},{0.11,0},{0.23,0}}")

		winMgr:getWindow("Interfaz/bPersonaje2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.26,0},{0.06,0},{0.31,0}}")
		interfazNoche:getChild("Interfaz/iVida2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.24,0},{0.06,0},{0.25,0}}")
		interfazNoche:getChild("Interfaz/iEnergia2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.25,0},{0.06,0},{0.26,0}}")
		interfazNoche:getChild("Interfaz/BotonIA12"):setProperty("UnifiedAreaRect","{{0.06,0},{0.26,0},{0.07,0},{0.28,0}}")
		interfazNoche:getChild("Interfaz/BotonIA22"):setProperty("UnifiedAreaRect","{{0.06,0},{0.28,0},{0.07,0},{0.3,0}}")
		interfazNoche:getChild("Interfaz/BotonIA32"):setProperty("UnifiedAreaRect","{{0.06,0},{0.3,0},{0.07,0},{0.31,0}}")

		winMgr:getWindow("Interfaz/bPersonaje3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.34,0},{0.06,0},{0.39,0}}")
		interfazNoche:getChild("Interfaz/iVida3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.32,0},{0.06,0},{0.33,0}}")
		interfazNoche:getChild("Interfaz/iEnergia3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.33,0},{0.06,0},{0.34,0}}")
		interfazNoche:getChild("Interfaz/BotonIA13"):setProperty("UnifiedAreaRect","{{0.06,0},{0.34,0},{0.07,0},{0.35,0}}")
		interfazNoche:getChild("Interfaz/BotonIA23"):setProperty("UnifiedAreaRect","{{0.06,0},{0.35,0},{0.07,0},{0.37,0}}")
		interfazNoche:getChild("Interfaz/BotonIA33"):setProperty("UnifiedAreaRect","{{0.06,0},{0.37,0},{0.07,0},{0.39,0}}")

	elseif pers == 2 then

		winMgr:getWindow("Interfaz/bPersonaje1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.13,0},{0.06,0},{0.18,0}}")
		interfazNoche:getChild("Interfaz/iVida1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.11,0},{0.06,0},{0.12,0}}")
		interfazNoche:getChild("Interfaz/iEnergia1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.12,0},{0.06,0},{0.13,0}}")
		interfazNoche:getChild("Interfaz/BotonIA11"):setProperty("UnifiedAreaRect","{{0.06,0},{0.13,0},{0.07,0},{0.15,0}}")
		interfazNoche:getChild("Interfaz/BotonIA21"):setProperty("UnifiedAreaRect","{{0.06,0},{0.15,0},{0.07,0},{0.16,0}}")
		interfazNoche:getChild("Interfaz/BotonIA31"):setProperty("UnifiedAreaRect","{{0.06,0},{0.16,0},{0.07,0},{0.18,0}}")

		winMgr:getWindow("Interfaz/bPersonaje" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.23,0},{0.09,0},{0.31,0}}")
		interfazNoche:getChild("Interfaz/iVida" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.19,0},{0.09,0},{0.21,0}}")
		interfazNoche:getChild("Interfaz/iEnergia" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.21,0},{0.09,0},{0.23,0}}")
		interfazNoche:getChild("Interfaz/BotonIA1" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.23,0},{0.11,0},{0.25,0}}")
		interfazNoche:getChild("Interfaz/BotonIA2" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.25,0},{0.11,0},{0.28,0}}")
		interfazNoche:getChild("Interfaz/BotonIA3" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.28,0},{0.11,0},{0.31,0}}")

		winMgr:getWindow("Interfaz/bPersonaje3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.34,0},{0.06,0},{0.39,0}}")
		interfazNoche:getChild("Interfaz/iVida3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.32,0},{0.06,0},{0.33,0}}")
		interfazNoche:getChild("Interfaz/iEnergia3"):setProperty("UnifiedAreaRect","{{0.01,0},{0.33,0},{0.06,0},{0.34,0}}")
		interfazNoche:getChild("Interfaz/BotonIA13"):setProperty("UnifiedAreaRect","{{0.06,0},{0.34,0},{0.07,0},{0.35,0}}")
		interfazNoche:getChild("Interfaz/BotonIA23"):setProperty("UnifiedAreaRect","{{0.06,0},{0.35,0},{0.07,0},{0.37,0}}")
		interfazNoche:getChild("Interfaz/BotonIA33"):setProperty("UnifiedAreaRect","{{0.06,0},{0.37,0},{0.07,0},{0.39,0}}")

	elseif pers == 3 then

		winMgr:getWindow("Interfaz/bPersonaje1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.13,0},{0.06,0},{0.18,0}}")
		interfazNoche:getChild("Interfaz/iVida1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.11,0},{0.06,0},{0.12,0}}")
		interfazNoche:getChild("Interfaz/iEnergia1"):setProperty("UnifiedAreaRect","{{0.01,0},{0.12,0},{0.06,0},{0.13,0}}")
		interfazNoche:getChild("Interfaz/BotonIA11"):setProperty("UnifiedAreaRect","{{0.06,0},{0.13,0},{0.07,0},{0.15,0}}")
		interfazNoche:getChild("Interfaz/BotonIA21"):setProperty("UnifiedAreaRect","{{0.06,0},{0.15,0},{0.07,0},{0.16,0}}")
		interfazNoche:getChild("Interfaz/BotonIA31"):setProperty("UnifiedAreaRect","{{0.06,0},{0.16,0},{0.07,0},{0.18,0}}")

		winMgr:getWindow("Interfaz/bPersonaje2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.21,0},{0.06,0},{0.26,0}}")
		interfazNoche:getChild("Interfaz/iVida2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.19,0},{0.06,0},{0.2,0}}")
		interfazNoche:getChild("Interfaz/iEnergia2"):setProperty("UnifiedAreaRect","{{0.01,0},{0.2,0},{0.06,0},{0.21,0}}")
		interfazNoche:getChild("Interfaz/BotonIA12"):setProperty("UnifiedAreaRect","{{0.06,0},{0.21,0},{0.07,0},{0.23,0}}")
		interfazNoche:getChild("Interfaz/BotonIA22"):setProperty("UnifiedAreaRect","{{0.06,0},{0.23,0},{0.07,0},{0.25,0}}")
		interfazNoche:getChild("Interfaz/BotonIA32"):setProperty("UnifiedAreaRect","{{0.06,0},{0.25,0},{0.07,0},{0.26,0}}")

		winMgr:getWindow("Interfaz/bPersonaje" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.31,0},{0.09,0},{0.39,0}}")
		interfazNoche:getChild("Interfaz/iVida" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.27,0},{0.09,0},{0.29,0}}")
		interfazNoche:getChild("Interfaz/iEnergia" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.29,0},{0.09,0},{0.31,0}}")
		interfazNoche:getChild("Interfaz/BotonIA1" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.31,0},{0.11,0},{0.33,0}}")
		interfazNoche:getChild("Interfaz/BotonIA2" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.33,0},{0.11,0},{0.36,0}}")
		interfazNoche:getChild("Interfaz/BotonIA3" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.36,0},{0.11,0},{0.39,0}}")

	end

	persSelect = pers
end

function sacarVentana(text)
	print("Sacar ventana " .. text)

	-- Activamos la ventana del texto
	interfazNoche:addChildWindow(textWindow)
	textWindow:setVisible(true)
	textWindow:activate()
	winMgr:getWindow("VentanaText/Ventana/Text"):setText(text)
	winMgr:getWindow("VentanaText/Ventana/Start"):subscribeEvent("Clicked", "closeVentana")
end

function closeVentana()
	textWindow:deactivate()
	textWindow:setVisible(false)
end

function activarBotonIA(ia)
	for i = 1, 3, 1 do
		CEGUI.WindowManager:getSingleton():getWindow("Interfaz/BotonIA" .. i .. persSelect):setVisible(false)
    end
	CEGUI.WindowManager:getSingleton():getWindow("Interfaz/BotonIA" .. ia .. persSelect):setVisible(true)
end
