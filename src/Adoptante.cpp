#include "../include/Adoptante.h"

// Constructores
// Por defecto: un adoptante "vacio"
Adoptante::Adoptante(){
    ID = 0;
    nombre = "";
    contacto = 0;
    vivienda = "";
}

Adoptante::Adoptante(int unID, std::string unNombre, int unContacto, std::string unVivienda){
    ID = unID;
    nombre = unNombre;
    contacto = unContacto;
    vivienda = unVivienda;
}

// De copia: copia cada atributo del adoptante original
Adoptante::Adoptante(const Adoptante& otro){
    ID = otro.ID;
    nombre = otro.nombre;
    contacto = otro.contacto;
    vivienda = otro.vivienda;
}

// Getters
int Adoptante::getID() const {
    return ID;
}
std::string Adoptante::getNombre() const {
    return nombre;
}
int Adoptante::getContacto() const {
    return contacto;
}
std::string Adoptante::getVivienda() const {
    return vivienda;
}

// Setters
void Adoptante::setID(int unID){
    ID = unID;
}
void Adoptante::setNombre(std::string unNombre){
    nombre = unNombre;
}
void Adoptante::setContacto(int unContacto){
    contacto = unContacto;
}
void Adoptante::setVivienda(std::string unVivienda){
    vivienda = unVivienda;
}
