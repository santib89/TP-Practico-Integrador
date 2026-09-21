#include "../include/Animales.h"
int Animales::getID() const {
    return ID;
}
std:: string Animales ::getNombre() const {
    return nombre;
}
int Animales ::getEdad() const {
    return edad;
}
bool Animales ::getSalud() const {
    return salud;
}
bool Animales ::getAdopcion() const {
    return adopcion;
}
Animales::Animales(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion){
    ID= unID;
    nombre=unNombre;
    edad=unEdad;
    salud=unSalud;
    adopcion=unAdopcion;
}