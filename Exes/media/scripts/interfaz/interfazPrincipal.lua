function inicializarInterfaz()
	if (winMgr) then
		print("WARNING - inicializarInterfaz - Interfaz ya inicializada")
	else
		winMgr = CEGUI.WindowManager:getSingleton()
		persSelect = 1
		fpsWindow = 0
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
		
		inicializarInterfazDia()
		
		
		-- Cargamos la ventana que muestra los FPS
		winMgr:loadWindowLayout("Time.layout")
		fpsWindow = winMgr:getWindow("Time")
		interfazPrincipal:addChildWindow(fpsWindow)
	end

end