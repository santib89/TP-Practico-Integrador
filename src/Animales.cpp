#include "../include/Animales.h"
Animales::Animales(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion){
    ID= unID;
    nombre=unNombre;
    edad=unEdad;
    salud=unSalud;
    adopcion=unAdopcion;
}
// Getters
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

//Setters
void Animales::setID(int unID){
    ID = unID;
}
void Animales::setNombre(std:: string unNombre){
    nombre = unNombre;
}
void Animales::setEdad(int unEdad){
    edad = unEdad;
}
void Animales::setSalud(bool unSalud){
    salud = unSalud;
}
void Animales::setAdopcion(bool unAdopcion){
    adopcion = unAdopcion;
}