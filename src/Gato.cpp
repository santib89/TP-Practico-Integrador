#include "../include/Gato.h"
#include <iostream>

Gato::Gato() {
    color = "";
    esInterior = true;
}

Gato::Gato(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unColor, bool unEsInterior)
    : Animal(unID, unNombre, unEdad, unSalud, unAdopcion)
{
    color = unColor;
    esInterior = unEsInterior;
}

Gato::Gato(const Gato& otro) : Animal(otro) {
    color = otro.color;
    esInterior = otro.esInterior;
}

std::string Gato::getColor() const {
    return color;
}
bool Gato::getEsInterior() const{
    return esInterior;
}

void Gato::setColor(std::string unColor){
    color = unColor;
}

void Gato::setEsInterior(bool unEsInterior){
    esInterior = unEsInterior;
}

void Gato::mostrarInfo() const
{
    Animal::mostrarInfo();
    std::cout << " | Tipo: Gato"
              << " | Color: " << color
              << " | Interior: " << (esInterior ? "Si" : "No") << "\n";
}

Animal* Gato::clonar() const
{
    return new Gato(*this);
}
