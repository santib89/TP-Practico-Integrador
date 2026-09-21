#include <iostream>
#include <string>
#include "Adoptante.h"
#include "Animales.h"
#include "Gato.h"
#include "Perro.h"
#include "Refugio.h"
#include "Solicitud.h"
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
std :: cout << "0.Para Salir\n";

//RECIBIR OPTION
option = getOption();

//RESPUESTAS
    switch (option)
    {
    case 1:
        /* code */
        break;
    
    default:
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
