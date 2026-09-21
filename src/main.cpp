#include <iostream>
#include <string>
#include "../include/Adoptante.h"
#include "../include/Animales.h"
#include "../include/Gato.h"
#include "../include/Perro.h"
#include "../include/Refugio.h"
#include "../include/Solicitud.h"
//Clase Animales

//Clase Perro derivada de animales

//Clase Gato derivada de animales
//Clase Adoptantes

//Clase Solicitud

//Clase Refugio


//Obtener valor de option
int getOption(){
    int option;
    std :: cout << "Opcion:";
    std:: cin >> option;
    return option;
}

//MENU

void menu(){
//Variables
int option;
do //Bucle de repeticion para el menu
{

//OPCIONES
std:: cout << "==========Opciones==========\n";
std :: cout << "1.Para Registrar un Perro\n";
std :: cout << "2.Para Registrar un Gato\n";
std :: cout << "3.Listar todos los animales\n";
std :: cout << "4.Listar los animales disponibles\n";
std :: cout << "5.Registrar un adoptante\n";
std :: cout << "6.Buscar un animal por ID\n";
std :: cout << "7.Crear una solicitud de adopción\n";
std :: cout << "8.Confirmar una solicitud\n";
std :: cout << "9.Cancelar una solicitud\n";
std :: cout << "10.Devolver un animal al estado disponible\n";
std :: cout << "11.Ver solicitudes e historial de adopciones\n";
std :: cout << "0.Para Salir\n";
//RECIBIR OPTION
option = getOption();

//RESPUESTAS
    switch (option)
    {
    case 0:
        std:: cout <<"Saliendo...\n";
        break;
    case 1:
        /* code */
        break;
    
    default:
    std:: cout <<"Digito Invalido\n";
        break;
    }
} while (option != 0);

}

//Funcion Principal
int main() 
{
menu();
    return 0;
}
