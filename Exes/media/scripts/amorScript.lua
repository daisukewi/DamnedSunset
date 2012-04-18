function healHability()
	print("Inicialización de la función de la corutina.")
	valor = coroutine.yield(52);
	print("Valor recibido después del resume: " .. valor)
	print("Valor escrito por C++ en el contexto de lua: " .. numero)
end