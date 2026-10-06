#include "../include/Refugio.h"
#include <iostream>

Refugio::Refugio()
{
    capacidadAnimales = 10;
    cantidadAnimales = 0;
    proximoIdAnimal = 1;
    animales = new Animales*[capacidadAnimales];
}

Refugio::~Refugio()
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        delete animales[i];
    }
    delete[] animales;
}

void Refugio::agrandarArreglo()
{
    int nuevaCapacidad = capacidadAnimales * 2;
    Animales** nuevo = new Animales*[nuevaCapacidad];

    for (int i = 0; i < cantidadAnimales; i++)
    {
        nuevo[i] = animales[i];
    }

    delete[] animales;
    animales = nuevo;
    capacidadAnimales = nuevaCapacidad;
}

int Refugio::registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano)
{
    if (cantidadAnimales == capacidadAnimales)
    {
        agrandarArreglo();
    }

    int id = proximoIdAnimal;
    animales[cantidadAnimales] = new Perro(id, unNombre, unEdad, true, false, unRaza, unTamano);
    cantidadAnimales++;
    proximoIdAnimal++;

    return id;
}
int Refugio::registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior)
{
    if (cantidadAnimales == capacidadAnimales)
    {
        agrandarArreglo();
    }

    int id = proximoIdAnimal;
    animales[cantidadAnimales] = new Gato(id, unNombre, unEdad, true, false, unColor, unEsInterior);
    cantidadAnimales++;
    proximoIdAnimal++;

    return id;
}

Animales* Refugio::buscarAnimal(int unID) const
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        Animales* actual = *(animales + i);
        if (actual->getID() == unID)
        {
            return actual;
        }
    }
    return nullptr;
}

void Refugio::listarAnimales() const
{
    if (cantidadAnimales == 0)
    {
        std::cout << "No hay animales registrados\n";
        return;
    }

    for (int i = 0; i < cantidadAnimales; i++)
    {
        animales[i]->mostrarInfo();
    }
}

void Refugio::listarDisponibles() const
{
    bool hayDisponibles = false;

    for (int i = 0; i < cantidadAnimales; i++)
    {
        if (!animales[i]->getAdopcion())
        {
            animales[i]->mostrarInfo();
            hayDisponibles = true;
        }
    }

    if (!hayDisponibles)
    {
        std::cout << "No hay animales disponibles\n";
    }
}