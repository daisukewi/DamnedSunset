function helloWorld()
	print("Hello world desde script inmediato de lua")
end

function proc1()
	print("Ejecución de un procedimiento desde lua sin parámetros y sin valor devuelto")
end

function proc2(param)
	print("Ejecución de un procedimiento desde lua con un parámetro y sin valor devuelto. Parámetro: " .. param)
end

print("Hello world desde lua en prueba 1")

numero = 10
cadena = "Esto es una cadena desde lua"
tabla = { numero = 70, booleano = true, cadena = "Cadena desde una tabla en lua"}