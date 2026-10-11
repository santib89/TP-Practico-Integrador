#include "../include/Perro.h"
#include <iostream>

Perro::Perro() {
    raza = "";
    tamano = 0.0;
}

Perro::Perro(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unRaza, double unTamano)
: Animal(unID, unNombre, unEdad, unSalud, unAdopcion)
 {
    raza = unRaza;
    tamano = unTamano;
 }

Perro::Perro(const Perro& otro) : Animal(otro) {
    raza = otro.raza;
    tamano = otro.tamano;
}

std::string Perro::getRaza() const {
    return raza;
}
double Perro::getTamano() const{
    return tamano;
}

void Perro::setRaza(std::string unRaza) {
    raza = unRaza;
}

void Perro::setTamano(double unTamano){
   tamano = unTamano;
}

void Perro::mostrarInfo() const
{
    Animal::mostrarInfo();
    std::cout << " | Tipo: Perro"
              << " | Raza: " << raza
              << " | Tamaño: " << tamano << "\n";
}

Animal* Perro::clonar() const
{
    return new Perro(*this);
}
