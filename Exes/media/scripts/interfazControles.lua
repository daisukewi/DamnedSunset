function inicializarInterfazControles()
	-- Cargamos la interfaz
	CEGUI.WindowManager:getSingleton():loadWindowLayout("InterfazControles.layout")
	interfazC = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles")

	-- Activamos la ventana de interfaz
	CEGUI.System:getSingleton():setGUISheet(interfazC)
	interfazC:setVisible(true)
	interfazC:activate()
	
end