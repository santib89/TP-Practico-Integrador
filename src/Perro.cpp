#include "../include/Perro.h"

// Constructores
Perro::Perro() {
    raza = "";
    tamano = 0.0;
}

Perro::Perro(int unID, std:: string unNombre, int unEdad, bool unSalud, bool unAdopcion, std:: string unRaza, double unTamano)
: Animales(unID, unNombre, unEdad, unSalud, unAdopcion)
 {
    raza = unRaza;
    tamano = unTamano;
 }

Perro::Perro(const Perro& otro) : Animales(otro) {
    raza = otro.raza;
    tamano = otro.tamano;
}

// Getters
std:: string Perro ::getRaza() const {
    return raza;
}
double Perro ::getTamano() const{
    return tamano;
}

// Setters
void Perro::setRaza(std::string unRaza) {
    raza = unRaza;
}

void Perro::setTamano(double unTamano){
   tamano = unTamano;
}
