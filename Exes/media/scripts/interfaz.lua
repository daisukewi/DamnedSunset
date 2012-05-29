function interfazTick(text)
	fpsWindow:setText(text)
end

function init()
	winMgr:loadWindowLayout("Interfaz.layout")
	interfazW = winMgr:getWindow("Interfaz")
	ocultarBotones()
	-- Cargamos la ventana que muestra los FPS
	winMgr:loadWindowLayout("Time.layout")
	fpsWindow = winMgr:getWindow("Time")

	-- Asociamos los botones del menú con las funciones que se deben ejecutar.
	winMgr:getWindow("Interfaz/bPersonaje1"):subscribeEvent("Clicked", "sendClickMessage1")
	winMgr:getWindow("Interfaz/bPersonaje2"):subscribeEvent("Clicked", "sendClickMessage2")
	winMgr:getWindow("Interfaz/bPersonaje3"):subscribeEvent("Clicked", "sendClickMessage3")

	--	CEGUI.WindowManager:getSingleton():getWindow("Interfaz/Menu/b1"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(GUI.CInterfazController.clickB1, self))
	--	CEGUI.WindowManager:getSingleton():getWindow("Interfaz/Menu/b2"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(GUI.CInterfazController.clickB2, self))
	--	CEGUI.WindowManager:getSingleton():getWindow("Interfaz/Menu/b3"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(GUI.CInterfazController.clickB3, self))
	--	CEGUI.WindowManager:getSingleton():getWindow("Interfaz/Menu/b4"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(GUI.CInterfazController.clickB4, self))
end

function activate()
	-- Activamos la ventana de interfaz
	CEGUI.System:getSingleton():setGUISheet(interfazW)
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

function ocultarBotones()
	interfazW:getChild("Interfaz/Menu"):getChild("Interfaz/Menu/b1"):setVisible(false)
	interfazW:getChild("Interfaz/Menu"):getChild("Interfaz/Menu/b2"):setVisible(false)
	interfazW:getChild("Interfaz/Menu"):getChild("Interfaz/Menu/b3"):setVisible(false)
	interfazW:getChild("Interfaz/Menu"):getChild("Interfaz/Menu/b4"):setVisible(false)
end

function actualizarBarraVida(numPersonaje, porcentajeVida)
	urlVida = "Interfaz/iVida" .. numPersonaje
	interfazW:getChild(urlVida):setWidth(CEGUI.UDim(porcentajeVida*0.1,0))
end

function cargarBoton(numBoton, nombreBoton)
	nombreHijo = "Interfaz/Menu/b" .. numBoton
	imagen1 = "set:InterfazUtils image:" .. nombreBoton
	imagen2 = "set:InterfazUtils image:" .. nombreBoton .. "2"
	imagen3 = "set:InterfazUtils image:" .. nombreBoton .. "3"
	interfazW:getChild("Interfaz/Menu"):getChild(nombreHijo):setProperty("NormalImage",imagen1)
	interfazW:getChild("Interfaz/Menu"):getChild(nombreHijo):setProperty("HoverImage",imagen2)
	interfazW:getChild("Interfaz/Menu"):getChild(nombreHijo):setProperty("PushedImage",imagen3)
	interfazW:getChild("Interfaz/Menu"):getChild(nombreHijo):setVisible(true)
end

function sendClickMessage1()
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Jack")
	mensaje:setInterface(true)
	mensaje:send()
	print("sendClickMessage1")
end

function sendClickMessage2()
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Erick")
	mensaje:setInterface(true)
	mensaje:send()
	print("sendClickMessage2")
end

function sendClickMessage3()
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity("Amor")
	mensaje:setInterface(true)
	mensaje:send()
	print("sendClickMessage3")
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
