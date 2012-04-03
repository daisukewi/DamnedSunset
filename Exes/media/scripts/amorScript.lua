function healHability()
	print("Inicialización de la función de la corutina.")
	valor = coroutine.yield(52);
	print("Valor recibido después del resume: " .. valor)
end