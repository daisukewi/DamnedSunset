function healHability()
	print("Inicializaci�n de la funci�n de la corutina.")
	funcion()
	a = 3
	print("Valor escrito por C++ en el contexto de lua: " .. numero)
end

function funcion()
	print("Inicio de la funcion.")
	valor = coroutine.yield(52);
	print("Valor recibido despu�s del resume: " .. valor)
end