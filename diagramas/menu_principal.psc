Algoritmo MenuRefugio
	Definir opcion Como Entero
	Repetir
		Escribir "==========Opciones=========="
		Escribir "1. Registrar un perro"
		Escribir "2. Registrar un gato"
		Escribir "3. Listar todos los animales"
		Escribir "4. Listar los animales disponibles"
		Escribir "5. Registrar un adoptante"
		Escribir "6. Buscar un animal por ID"
		Escribir "7. Crear una solicitud de adopcion"
		Escribir "8. Confirmar una solicitud"
		Escribir "9. Cancelar una solicitud"
		Escribir "10. Devolver un animal"
		Escribir "11. Ver solicitudes e historial"
		Escribir "0. Salir"
		Leer opcion
		Segun opcion Hacer
			1:
				Escribir "Ingresar nombre, edad, raza y tamano"
				Escribir "Crear el perro con un ID nuevo"
				Escribir "Agregarlo al catalogo"
				Escribir "Mostrar el ID asignado"
			2:
				Escribir "Ingresar nombre, edad, color e interior o exterior"
				Escribir "Crear el gato con un ID nuevo"
				Escribir "Agregarlo al catalogo"
				Escribir "Mostrar el ID asignado"
			3:
				Escribir "Recorrer el catalogo"
				Escribir "Mostrar los datos de cada animal"
			4:
				Escribir "Recorrer el catalogo"
				Escribir "Mostrar solo los animales no adoptados"
			5:
				Escribir "Ingresar nombre, contacto y vivienda"
				Escribir "Crear el adoptante con un ID nuevo"
				Escribir "Mostrar el ID asignado"
			6:
				Escribir "Ingresar el ID del animal"
				Escribir "Buscarlo en el catalogo"
				Escribir "Mostrar sus datos o avisar que no existe"
			7:
				Escribir "Ingresar ID del adoptante y del animal"
				Escribir "Verificar que existan y que el animal este disponible"
				Escribir "Crear la solicitud en estado Pendiente"
			8:
				Escribir "Ingresar el ID de la solicitud"
				Escribir "Verificar que este Pendiente"
				Escribir "Pasarla a Confirmada y marcar el animal como adoptado"
			9:
				Escribir "Ingresar el ID de la solicitud"
				Escribir "Verificar que este Pendiente"
				Escribir "Pasarla a Cancelada"
			10:
				Escribir "Ingresar el ID del animal"
				Escribir "Verificar que este adoptado"
				Escribir "Marcarlo como disponible"
			11:
				Escribir "Recorrer las solicitudes"
				Escribir "Mostrar adoptante, animal y estado de cada una"
			0:
				Escribir "Saliendo..."
			De Otro Modo:
				Escribir "Digito invalido"
		FinSegun
	Hasta Que opcion = 0
FinAlgoritmo
