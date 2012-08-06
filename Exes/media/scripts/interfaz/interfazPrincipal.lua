function inicializarInterfaz()

	persSelect = 1
	fpsWindow = 0
	textWindow = 0
	horas = 21
	minutos = 00
	
	if (winMgr) then
		print("WARNING - inicializarInterfaz - Interfaz ya inicializada")
	else
		winMgr = CEGUI.WindowManager:getSingleton()
	
		-- Cargamos la interfaz principal, de la cual se añadiran las demas
		winMgr:loadWindowLayout("InterfazPrincipal.layout")
		
		-- Cargamos la ventana que muestra los FPS
		winMgr:loadWindowLayout("Time.layout")
	end
	
	interfazPrincipal = winMgr:getWindow("InterfazPrincipal")
	
	-- Activamos la ventana de interfaz
	CEGUI.System:getSingleton():setGUISheet(interfazPrincipal)
	interfazPrincipal:setVisible(true)
	interfazPrincipal:activate()

	inicializarInterfazControles()

	inicializarInterfazNoche()
	
	inicializarInterfazDia()
	
	fpsWindow = winMgr:getWindow("Time")
	interfazPrincipal:addChildWindow(fpsWindow)
end