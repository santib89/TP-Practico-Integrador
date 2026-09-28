#include "../include/Perro.h"

Perro::Perro(int unID, std:: string unNombre, int unEdad, bool unSalud, bool unAdopcion, std:: string unRaza, double unTamano)
: Animales(unID, unNombre, unEdad, unSalud, unAdopcion)
 {
    raza = unRaza;
    tamano = unTamano;
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