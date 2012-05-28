function interfazTick(text)
	fpsWindow:setText(text)
end

function init()
	CEGUI.WindowManager:getSingleton():loadWindowLayout("Interfaz.layout")
	interfazW = CEGUI.WindowManager:getSingleton():getWindow("Interfaz")
	ocultarBotones()
	-- Cargamos la ventana que muestra los FPS
	CEGUI.WindowManager:getSingleton():loadWindowLayout("Time.layout")
	fpsWindow = CEGUI.WindowManager:getSingleton():getWindow("Time")

	-- Asociamos los botones del menú con las funciones que se deben ejecutar.
	print("self1")
	--local name = "Jack"
	--CEGUI.WindowManager:getSingleton():getWindow("Interfaz/bPersonaje1").subscribeEvent(CEGUI.PushButton.EventClicked, self, "sendClickMessage")
	print("self2")
	--sendClickMessage("Jack")
	print("self3")
	--CEGUI.WindowManager:getSingleton():getWindow("Interfaz/bPersonaje2"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(true, self))
	print("self4")
	--sendClickMessage("Erick")
	--CEGUI.WindowManager:getSingleton():getWindow("Interfaz/bPersonaje3"):subscribeEvent(CEGUI.PushButton.EventClicked, CEGUI:SubscriberSlot(true, self))
	--sendClickMessage("Amor")

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

function sendClickMessage(name)
	-- Crear y enviar el mensaje de entity selected
	local mensaje = LUA_MEntitySelected()
	mensaje:setSelectedEntity(name)
	mensaje:setInterface(true)
	mensaje:send()
	print("sendClickMessage")
end

interfazW = 0
fpsWindow = 0
