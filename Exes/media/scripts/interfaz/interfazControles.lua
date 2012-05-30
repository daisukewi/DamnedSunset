--Las funciones de los botones redirigen a la funcion que asignemos a dicho boton
--No asignamos directamente las funciones al evento del boton, porque da problemas al cambiar el mismo evento que se esta produciendo
function clickBoton1()
	if funcionBoton1 ~= "" then
		_G[funcionBoton1]()
	end
end
function clickBoton2()
	if funcionBoton2 ~= "" then
		_G[funcionBoton2]()
	end
end
function clickBoton3()
	if funcionBoton3 ~= "" then
		_G[funcionBoton3]()
	end
end
function clickBoton4()
	if funcionBoton4 ~= "" then
		_G[funcionBoton4]()
	end
end

--Funcion que cargar en un boton, una imagen y una funcion
function cargarBoton(numBoton,imageName,funcion)
	--Guardamos en la variable local "boton" el boton que vamos a modificar
	local boton
	if numBoton == 1 then
		boton = botonControles1
		funcionBoton1 = funcion
    elseif numBoton == 2 then
		boton = botonControles2
		funcionBoton2 = funcion
    elseif numBoton == 3 then
		boton = botonControles3
		funcionBoton3 = funcion
	elseif numBoton == 4 then
		boton = botonControles4
		funcionBoton4 = funcion
    end
	
	--Cargamos las imagenes al boton
	local imageNameComun = "set:InterfazUtils image:"
	local imageNameFinal = imageNameComun .. imageName

	boton:setProperty("NormalImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 2
	boton:setProperty("HoverImage",imageNameFinal)
	imageNameFinal = imageNameComun .. imageName .. 3
	boton:setProperty("PushedImage",imageNameFinal)
	boton:setVisible(true)
end

function ocultarBoton(numBoton)
	if numBoton == 1 then
		botonControles1:setVisible(false)
    elseif numBoton == 2 then
		botonControles2:setVisible(false)
    elseif numBoton == 3 then
		botonControles3:setVisible(false)
	elseif numBoton == 4 then
		botonControles4:setVisible(false)
    end
end

--Inicializacion de la interfaz de los controles
function inicializarInterfazControles()
	print("inicializarInterfazControles")

	-- Cargamos la interfaz
	CEGUI.WindowManager:getSingleton():loadWindowLayout("InterfazControles.layout")
	interfazC = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles")

	-- Activamos la ventana de interfaz
	CEGUI.System:getSingleton():setGUISheet(interfazC)
	interfazC:setVisible(true)
	interfazC:activate()
	
	--Guargamod los botones en variables para poder acceder facilmente a ellos
	botonControles1 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b1")
	botonControles2 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b2")
	botonControles3 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b3")
	botonControles4 = CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/Menu/b4")
	
	--Subscribimos los botones a sus funciones
	botonControles1:subscribeEvent("Clicked", clickBoton1)
	botonControles2:subscribeEvent("Clicked", clickBoton2)
	botonControles3:subscribeEvent("Clicked", clickBoton3)
	botonControles4:subscribeEvent("Clicked", clickBoton4)
	
	--Inicializamos los botones del dia
	inicializarBotonesDia()
end