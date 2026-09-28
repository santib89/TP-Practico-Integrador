#include "../include/Gato.h"

Gato::Gato(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unColor, bool unEsInterior)
    : Animales(unID, unNombre, unEdad, unSalud, unAdopcion)
{
    color = unColor;
    esInterior = unEsInterior;
}
// Getters

std:: string Gato ::getColor() const {
    return color;
}
bool Gato ::getEsInterior() const{
    return esInterior;
}

// Setters
void Gato::setColor(std::string unColor){
    color = unColor;
}

void Gato::setEsInterior(bool unEsInterior){
    esInterior = unEsInterior;
}
