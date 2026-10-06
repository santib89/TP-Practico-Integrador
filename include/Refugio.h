#pragma once
#include "Animales.h"
#include "Perro.h"
#include "Gato.h"

class Refugio
{
private:
    Animales** animales;
    int cantidadAnimales;
    int capacidadAnimales;
    int proximoIdAnimal;

    void agrandarArreglo();

public:
    Refugio();
    Refugio(const Refugio& otro);
    ~Refugio();

    int registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano);
    int registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior);

};