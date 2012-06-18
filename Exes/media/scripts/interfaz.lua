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

function actualizarHorasAmanecer(timeAmanecer)
	minutosAmanecer = timeAmanecer
	local horas = math.floor(minutosAmanecer/60)
	local minutos = minutosAmanecer - horas * 60
	local textoIntermedio
	if (minutos >= 10) then
		textoIntermedio = ":"
	else
		textoIntermedio = ":0"
	end
	winMgr:getWindow("Interfaz/Recursos"):setText(horas .. textoIntermedio .. minutos)
end

function actualizarSolenium(cantidadSolenium)
	solenium = cantidadSolenium
end

function inicializarInterfaz()
	if (winMgr) then
		print("WARNING - inicializarInterfaz - Interfaz ya inicializada")
	else
		winMgr = CEGUI.WindowManager:getSingleton()
		persSelect = 1
		fpsWindow = 0
		textWindow = 0
		textWindow = 0
		horas = 21
		minutos = 00

		-- Cargamos la interfaz principal, de la cual se añadiran las demas
		winMgr:loadWindowLayout("InterfazPrincipal.layout")
		
		interfazPrincipal = CEGUI.WindowManager:getSingleton():getWindow("InterfazPrincipal")
		
		-- Activamos la ventana de interfaz
		CEGUI.System:getSingleton():setGUISheet(interfazPrincipal)
		interfazPrincipal:setVisible(true)
		interfazPrincipal:activate()

		inicializarInterfazControles()

		inicializarInterfazNoche()
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

		-- Cargamos la ventana que muestra los FPS
		winMgr:loadWindowLayout("Time.layout")
		fpsWindow = winMgr:getWindow("Time")
		interfazNoche:addChildWindow(fpsWindow)

		-- Asociamos los botones del menú con las funciones que se deben ejecutar.
		winMgr:getWindow("Interfaz/bPersonaje1"):subscribeEvent("Clicked", "sendClickMessage1")
		winMgr:getWindow("Interfaz/bPersonaje2"):subscribeEvent("Clicked", "sendClickMessage2")
		winMgr:getWindow("Interfaz/bPersonaje3"):subscribeEvent("Clicked", "sendClickMessage3")

		-- Cargamos la ventana de texto
		winMgr:loadWindowLayout("VentanaText.layout")
		textWindow = winMgr:getWindow("VentanaText/Ventana")

		sacarVentana("Mision 1: Encontrar una forma de salir.")
		actualizarHorasAmanecer(1000)
	end
end


function activarInterfazNoche()
	if (interfazNoche) then
		-- Activamos la ventana de interfaz
		interfazNoche:setVisible(true)
		interfazNoche:activate()

		-- Activamos la ventana que muestra los FPS
		fpsWindow:setVisible(true)
		fpsWindow:activate()
	end
end

function desactivarInterfazNoche()
	if (interfazNoche) then
		fpsWindow:deactivate()
		fpsWindow:setVisible(false)

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
	n = 6 - persSelect - pers

	winMgr:getWindow("Interfaz/bPersonaje" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.15,0},{0.09,0},{0.23,0}}")
	interfazNoche:getChild("Interfaz/iVida" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.11,0},{0.09,0},{0.13,0}}")
	interfazNoche:getChild("Interfaz/iEnergia" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.13,0},{0.09,0},{0.15,0}}")
	interfazNoche:getChild("Interfaz/BotonIA1" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.15,0},{0.11,0},{0.17,0}}")
	interfazNoche:getChild("Interfaz/BotonIA2" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.17,0},{0.11,0},{0.2,0}}")
	interfazNoche:getChild("Interfaz/BotonIA3" .. pers):setProperty("UnifiedAreaRect","{{0.09,0},{0.2,0},{0.11,0},{0.23,0}}")

	winMgr:getWindow("Interfaz/bPersonaje" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.26,0},{0.06,0},{0.31,0}}")
	interfazNoche:getChild("Interfaz/iVida" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.24,0},{0.06,0},{0.25,0}}")
	interfazNoche:getChild("Interfaz/iEnergia" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.25,0},{0.06,0},{0.26,0}}")
	interfazNoche:getChild("Interfaz/BotonIA1" .. n):setProperty("UnifiedAreaRect","{{0.06,0},{0.26,0},{0.07,0},{0.28,0}}")
	interfazNoche:getChild("Interfaz/BotonIA2" .. n):setProperty("UnifiedAreaRect","{{0.06,0},{0.28,0},{0.07,0},{0.3,0}}")
	interfazNoche:getChild("Interfaz/BotonIA3" .. n):setProperty("UnifiedAreaRect","{{0.06,0},{0.3,0},{0.07,0},{0.31,0}}")

	winMgr:getWindow("Interfaz/bPersonaje" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.34,0},{0.06,0},{0.39,0}}")
	interfazNoche:getChild("Interfaz/iVida" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.32,0},{0.06,0},{0.33,0}}")
	interfazNoche:getChild("Interfaz/iEnergia" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.33,0},{0.06,0},{0.34,0}}")
	interfazNoche:getChild("Interfaz/BotonIA1" .. persSelect):setProperty("UnifiedAreaRect","{{0.06,0},{0.34,0},{0.07,0},{0.35,0}}")
	interfazNoche:getChild("Interfaz/BotonIA2" .. persSelect):setProperty("UnifiedAreaRect","{{0.06,0},{0.35,0},{0.07,0},{0.37,0}}")
	interfazNoche:getChild("Interfaz/BotonIA3" .. persSelect):setProperty("UnifiedAreaRect","{{0.06,0},{0.37,0},{0.07,0},{0.39,0}}")

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
