#include "../include/Animal.h"
#include <iostream>
Animal::Animal(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion){
    ID= unID;
    nombre=unNombre;
    edad=unEdad;
    salud=unSalud;
    adopcion=unAdopcion;
}
Animal::Animal() {
    ID = 0;
    nombre = "";
    edad = 0;
    salud = true;
    adopcion = false;
}
Animal::Animal(const Animal& otro) {
    ID = otro.ID;
    nombre = otro.nombre;
    edad = otro.edad;
    salud = otro.salud;
    adopcion = otro.adopcion;
}

Animal::~Animal() { }

int Animal::getID() const {
    return ID;
}
std::string Animal::getNombre() const {
    return nombre;
}
int Animal::getEdad() const {
    return edad;
}
bool Animal::getSalud() const {
    return salud;
}
bool Animal::getAdopcion() const {
    return adopcion;
}

void Animal::setID(int unID){
    ID = unID;
}
void Animal::setNombre(std::string unNombre){
    nombre = unNombre;
}
void Animal::setEdad(int unEdad){
    edad = unEdad;
}
void Animal::setSalud(bool unSalud){
    salud = unSalud;
}
void Animal::setAdopcion(bool unAdopcion){
    adopcion = unAdopcion;
}

void Animal::mostrarInfo() const
{
    std::cout << "ID: " << ID
              << " | Nombre: " << nombre
              << " | Edad: " << edad
              << " | Salud: " << (salud ? "Sano" : "Enfermo")
              << " | Estado: " << (adopcion ? "Adoptado" : "Disponible");
}

bool Animal::operator==(const Animal& otro) const
{
    return ID == otro.ID;
}

bool Animal::operator!() const
{
    return adopcion;
}
