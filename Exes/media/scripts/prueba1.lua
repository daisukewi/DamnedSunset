function helloWorld()
	print("Hello world desde script inmediato de lua")
end

function proc1()
	print("Ejecuci�n de un procedimiento desde lua sin par�metros y sin valor devuelto")
end

function proc2(param)
	print("Ejecuci�n de un procedimiento desde lua con un par�metro y sin valor devuelto. Par�metro: " .. param)
end

print("Hello world desde lua en prueba 1")

numero = 10
cadena = "Esto es una cadena desde lua"
tabla = { numero = 70, booleano = true, cadena = "Cadena desde una tabla en lua"}