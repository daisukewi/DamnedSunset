function interfazTick(text)
	fpsWindow:setText(text)
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

	interfazC:addChildWindow(interfazW)
	interfazW:setVisible(false)
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

	sacarVentana("Dream Theater")
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
	seleccionarPersonaje1()
end

function sendClickMessage2()
	seleccionarPersonaje2()
end

function sendClickMessage3()
	seleccionarPersonaje3()
end

function sacarVentana(text)
	-- Cargamos la ventana
	winMgr:loadWindowLayout("VentanaText.layout")
	textWindow = winMgr:getWindow("VentanaText/Ventana")
	-- Activamos la ventana del texto
	interfazW:addChildWindow(textWindow)
	textWindow:setVisible(true)
	textWindow:activate()
	textWindow:setText(text)
	winMgr:getWindow("VentanaText/Ventana/Start"):subscribeEvent("Clicked", "closeVentana")
end

function closeVentana()
	textWindow:deactivate()
	textWindow:setVisible(false)
end

winMgr = CEGUI.WindowManager:getSingleton()
interfazW = 0
fpsWindow = 0
textWindow = 0
