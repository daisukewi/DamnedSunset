function healHability()
	print("Inicializaci�n de la funci�n de la corutina.")
	valor = coroutine.yield(52);
	print("Valor recibido despu�s del resume: " .. valor)
end