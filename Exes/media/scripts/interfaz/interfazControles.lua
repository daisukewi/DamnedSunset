function fsadfsadf()
	print("fsadfsadf")
end

function funcionConstruir()
	print("funcionConstruir")
	cargarBoton(1,"torreta","inicializarBotonesDia")
	cargarBoton(2,"torreta","inicializarBotonesDia")
	cargarBoton(3,"torreta","inicializarBotonesDia")
	cargarBoton(4,"volver","inicializarBotonesDia")
end

function inicializarBotonesDia()
	print("inicializarBotonesDia")
	cargarBoton(1,"martillo","funcionConstruir")
	cargarBoton(2,"granada","funcionConstruir")
	cargarBoton(3,"bolazul","funcionConstruir")
	cargarBoton(4,"jeringa","funcionConstruir")
end


--Las funciones de los botones redirigen a la funcion que asignemos a dicho boton
--No asignamos directamente las funciones al evento del boton, porque da problemas al cambiar el mismo evento que se esta produciendo
function clickBoton1()
	_G[funcionBoton1]()
end
function clickBoton2()
	_G[funcionBoton2]()
end
function clickBoton3()
	_G[funcionBoton3]()
end
function clickBoton4()
	_G[funcionBoton4]()
end

--Funcion que cargar en un boton, una imagen y una funcion
function cargarBoton(numBoton,imageName,funcion)
	--Guardamos en la variable local "boton" el boton que vamos a modificar
	local boton
	if numBoton == 1 then
		boton = botonControles1
		print("asignada funcion1 a: ")
		print(funcion)
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
end

--Inicializacion de la interfaz de los controles
function inicializarInterfazControles()
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