#include "../include/Animales.h"
#include <iostream>
Animales::Animales(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion){
    ID= unID;
    nombre=unNombre;
    edad=unEdad;
    salud=unSalud;
    adopcion=unAdopcion;
}
Animales::Animales() {
    ID = 0;
    nombre = "";
    edad = 0;
    salud = true;
    adopcion = false;
}
Animales::Animales(const Animales& otro) {
    ID = otro.ID;
    nombre = otro.nombre;
    edad = otro.edad;
    salud = otro.salud;
    adopcion = otro.adopcion;
}

Animales::~Animales() { }


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

void Animales::mostrarInfo() const
{
    std::cout << "ID: " << ID
              << " | Nombre: " << nombre
              << " | Edad: " << edad
              << " | Salud: " << (salud ? "Sano" : "Enfermo")
              << " | Estado: " << (adopcion ? "Adoptado" : "Disponible");
}