function healHability()
	print("Inicialización de la función de la corutina.")
	funcion()
	a = 3
	print("Valor escrito por C++ en el contexto de lua: " .. numero)
end

function funcion()
	print("Inicio de la funcion.")
	valor = coroutine.yield(52);
	print("Valor recibido después del resume: " .. valor)
end