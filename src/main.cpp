#include <iostream>
#include <string>
#include "../include/Adoptante.h"
#include "../include/Animales.h"
#include "../include/Gato.h"
#include "../include/Perro.h"
#include "../include/Refugio.h"
#include "../include/Solicitud.h"

template <typename T>
T leerValor(std::string mensaje, T minimo)
{
    T valor;
    while (true)
    {
        std::cout << mensaje;
        if (std::cin >> valor)
        {
            std::cin.ignore(1000, '\n');
            if (valor >= minimo)
            {
                return valor;
            }
        }
        else
        {
            if (std::cin.eof())
            {
                return minimo;
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "Valor invalido. ";
    }
}

std::string leerTexto(std::string mensaje)
{
    std::string texto;
    std::cout << mensaje;
    std::cin >> std::ws;
    std::getline(std::cin, texto);
    return texto;
}

bool leerSiNo(std::string mensaje)
{
    while (!std::cin.eof())
    {
        std::string respuesta = leerTexto(mensaje + " (s/n): ");
        if (respuesta == "s" || respuesta == "S")
        {
            return true;
        }
        if (respuesta == "n" || respuesta == "N")
        {
            return false;
        }
        std::cout << "Responda s o n. ";
    }
    return false;
}

int getOption(){
    return leerValor<int>("Opcion:", 0);
}

void opcionRegistrarPerro(Refugio& refugio)
{
    std::string nombre = leerTexto("Nombre: ");
    int edad = leerValor<int>("Edad: ", 0);
    std::string raza = leerTexto("Raza: ");
    double tamano = leerValor<double>("Tamano: ", 0.1);

    int id = refugio.registrarPerro(nombre, edad, raza, tamano);
    std::cout << "Perro registrado con ID " << id << "\n";
}

void opcionRegistrarGato(Refugio& refugio)
{
    std::string nombre = leerTexto("Nombre: ");
    int edad = leerValor<int>("Edad: ", 0);
    std::string color = leerTexto("Color de pelaje: ");
    bool esInterior = leerSiNo("Es de interior?");

    int id = refugio.registrarGato(nombre, edad, color, esInterior);
    std::cout << "Gato registrado con ID " << id << "\n";
}

void opcionRegistrarAdoptante(Refugio& refugio)
{
    std::string nombre = leerTexto("Nombre: ");
    std::string contacto = leerTexto("Contacto (telefono o email): ");
    std::string vivienda = leerTexto("Tipo de vivienda: ");

    int id = refugio.registrarAdoptante(nombre, contacto, vivienda);
    std::cout << "Adoptante registrado con ID " << id << "\n";
}

void opcionBuscarAnimal(const Refugio& refugio)
{
    int id = leerValor<int>("ID del animal: ", 1);
    Animales* animal = refugio.buscarAnimal(id);

    if (animal == nullptr)
    {
        std::cout << "No existe un animal con ese ID\n";
    }
    else
    {
        animal->mostrarInfo();
    }
}

void opcionCrearSolicitud(Refugio& refugio)
{
    int idAdoptante = leerValor<int>("ID del adoptante: ", 1);
    int idAnimal = leerValor<int>("ID del animal: ", 1);

    int resultado = refugio.crearSolicitud(idAdoptante, idAnimal);
    if (resultado > 0)
    {
        std::cout << "Solicitud creada con ID " << resultado << "\n";
    }
    else if (resultado == -1)
    {
        std::cout << "No existe un adoptante con ese ID\n";
    }
    else if (resultado == -2)
    {
        std::cout << "No existe un animal con ese ID\n";
    }
    else
    {
        std::cout << "El animal ya fue adoptado\n";
    }
}

void opcionConfirmarSolicitud(Refugio& refugio)
{
    int id = leerValor<int>("ID de la solicitud: ", 1);

    int resultado = refugio.confirmarSolicitud(id);
    if (resultado == 0)
    {
        std::cout << "Solicitud confirmada. El animal fue adoptado\n";
    }
    else if (resultado == -1)
    {
        std::cout << "No existe una solicitud con ese ID\n";
    }
    else if (resultado == -2)
    {
        std::cout << "La solicitud no esta pendiente\n";
    }
    else
    {
        std::cout << "El animal ya fue adoptado por otra solicitud\n";
    }
}

void opcionCancelarSolicitud(Refugio& refugio)
{
    int id = leerValor<int>("ID de la solicitud: ", 1);

    int resultado = refugio.cancelarSolicitud(id);
    if (resultado == 0)
    {
        std::cout << "Solicitud cancelada\n";
    }
    else if (resultado == -1)
    {
        std::cout << "No existe una solicitud con ese ID\n";
    }
    else
    {
        std::cout << "La solicitud no esta pendiente\n";
    }
}

void opcionDevolverAnimal(Refugio& refugio)
{
    int id = leerValor<int>("ID del animal: ", 1);

    int resultado = refugio.devolverAnimal(id);
    if (resultado == 0)
    {
        std::cout << "El animal volvio a estar disponible\n";
    }
    else if (resultado == -1)
    {
        std::cout << "No existe un animal con ese ID\n";
    }
    else
    {
        std::cout << "El animal no estaba adoptado\n";
    }
}

//MENU

void menu(){
//Variables
int option;
Refugio refugio;
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
        opcionRegistrarPerro(refugio);
        break;
    case 2:
        opcionRegistrarGato(refugio);
        break;
    case 3:
        refugio.listarAnimales();
        break;
    case 4:
        refugio.listarDisponibles();
        break;
    case 5:
        opcionRegistrarAdoptante(refugio);
        break;
    case 6:
        opcionBuscarAnimal(refugio);
        break;
    case 7:
        opcionCrearSolicitud(refugio);
        break;
    case 8:
        opcionConfirmarSolicitud(refugio);
        break;
    case 9:
        opcionCancelarSolicitud(refugio);
        break;
    case 10:
        opcionDevolverAnimal(refugio);
        break;
    case 11:
        refugio.listarSolicitudes();
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
