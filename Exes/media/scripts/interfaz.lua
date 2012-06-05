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

function init()
	winMgr:loadWindowLayout("Interfaz.layout")
	interfazW = winMgr:getWindow("Interfaz")

	-- Cargamos la ventana que muestra los FPS
	winMgr:loadWindowLayout("Time.layout")
	fpsWindow = winMgr:getWindow("Time")

	-- Asociamos los botones del menú con las funciones que se deben ejecutar.
	winMgr:getWindow("Interfaz/bPersonaje1"):subscribeEvent("Clicked", "sendClickMessage1")
	winMgr:getWindow("Interfaz/bPersonaje2"):subscribeEvent("Clicked", "sendClickMessage2")
	winMgr:getWindow("Interfaz/bPersonaje3"):subscribeEvent("Clicked", "sendClickMessage3")

	-- Cargamos la ventana de texto
	winMgr:loadWindowLayout("VentanaText.layout")
	textWindow = winMgr:getWindow("VentanaText/Ventana")

	interfazC:addChildWindow(interfazW)
	interfazW:setVisible(false)

	sacarVentana("Mision 1: Encontrar una forma de salir.")
end

function activate()
	-- Activamos la ventana de interfaz
	--CEGUI.System:getSingleton():setGUISheet(interfazW)
	interfazW:setVisible(true)
	interfazW:activate()

	-- Activamos la ventana que muestra los FPS
	interfazW:addChildWindow(fpsWindow)
	fpsWindow:setVisible(true)
	fpsWindow:activate()

	--sacarVentana(os.clock())
end

function deactivate()
	fpsWindow:deactivate()
	fpsWindow:setVisible(false)

	interfazW:deactivate()
	interfazW:setVisible(false)
end

function actualizarBarraVida(numPersonaje, porcentajeVida)
	urlVida = "Interfaz/iVida" .. numPersonaje
	interfazW:getChild(urlVida):setWidth(CEGUI.UDim(porcentajeVida*0.1,0))
end

function sendClickMessage1()
	selectNewTarget(getEntityID("Jack"))
	if persSelect ~= 1 then
		cambiarBotones(1)
	end
end

function sendClickMessage2()
	selectNewTarget(getEntityID("Erick"))
	if persSelect ~= 2 then
		cambiarBotones(2)
	end
end

function sendClickMessage3()
	selectNewTarget(getEntityID("Amor"))
	if persSelect ~= 3 then
		cambiarBotones(3)
	end
end

function cambiarBotones(pers)
	n = 6 - persSelect - pers
	winMgr:getWindow("Interfaz/bPersonaje" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.15,0},{0.09,0},{0.23,0}}")
	interfazW:getChild("Interfaz/iVida" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.11,0},{0.09,0},{0.13,0}}")
	interfazW:getChild("Interfaz/iEnergia" .. pers):setProperty("UnifiedAreaRect","{{0.01,0},{0.13,0},{0.09,0},{0.15,0}}")
	winMgr:getWindow("Interfaz/bPersonaje" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.26,0},{0.06,0},{0.31,0}}")
	interfazW:getChild("Interfaz/iVida" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.24,0},{0.06,0},{0.25,0}}")
	interfazW:getChild("Interfaz/iEnergia" .. n):setProperty("UnifiedAreaRect","{{0.01,0},{0.25,0},{0.06,0},{0.26,0}}")
	winMgr:getWindow("Interfaz/bPersonaje" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.34,0},{0.06,0},{0.39,0}}")
	interfazW:getChild("Interfaz/iVida" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.32,0},{0.06,0},{0.33,0}}")
	interfazW:getChild("Interfaz/iEnergia" .. persSelect):setProperty("UnifiedAreaRect","{{0.01,0},{0.33,0},{0.06,0},{0.34,0}}")
	persSelect = pers
end

function sacarVentana(text)
	-- Activamos la ventana del texto
	interfazW:addChildWindow(textWindow)
	textWindow:setVisible(true)
	textWindow:activate()
	winMgr:getWindow("VentanaText/Ventana/Text"):setText(text)
	winMgr:getWindow("VentanaText/Ventana/Start"):subscribeEvent("Clicked", "closeVentana")
end

function closeVentana()
	textWindow:deactivate()
	textWindow:setVisible(false)
end

winMgr = CEGUI.WindowManager:getSingleton()
persSelect = 1
interfazW = 0
fpsWindow = 0
textWindow = 0
horas = 21
minutos = 00
