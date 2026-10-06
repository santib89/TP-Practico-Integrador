#include "../include/Refugio.h"

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
