Algoritmo ProcesoAdopcion
	Definir existeAdoptante, existeAnimal, animalAdoptado, decision Como Entero
	Escribir "Existe el adoptante? (1=si, 0=no)"
	Leer existeAdoptante
	Escribir "Existe el animal? (1=si, 0=no)"
	Leer existeAnimal
	Escribir "El animal ya esta adoptado? (1=si, 0=no)"
	Leer animalAdoptado
	Si existeAdoptante = 0 Entonces
		Escribir "Error: adoptante no encontrado"
	SiNo
		Si existeAnimal = 0 Entonces
			Escribir "Error: animal no encontrado"
		SiNo
			Si animalAdoptado = 1 Entonces
				Escribir "Error: animal no disponible"
			SiNo
				Escribir "Solicitud creada en estado Pendiente"
				Escribir "Confirmar (1) o cancelar (2)?"
				Leer decision
				Si decision = 1 Entonces
					Escribir "Solicitud Confirmada: el animal queda adoptado"
				SiNo
					Escribir "Solicitud Cancelada: el animal sigue disponible"
				FinSi
			FinSi
		FinSi
	FinSi
FinAlgoritmo
