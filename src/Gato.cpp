#include "../include/Gato.h"

// Constructores
// Por defecto: la parte Animales se construye sola con Animales()
Gato::Gato() {
    color = "";
    esInterior = true;
}

Gato::Gato(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unColor, bool unEsInterior)
    : Animales(unID, unNombre, unEdad, unSalud, unAdopcion)
{
    color = unColor;
    esInterior = unEsInterior;
}

// De copia: se le pasa "otro" a Animales para copiar tambien la parte heredada
Gato::Gato(const Gato& otro) : Animales(otro) {
    color = otro.color;
    esInterior = otro.esInterior;
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
