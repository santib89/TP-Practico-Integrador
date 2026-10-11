#include "../include/Adoptante.h"

Adoptante::Adoptante(){
    ID = 0;
    nombre = "";
    contacto = "";
    vivienda = "";
}
Adoptante::Adoptante(int unID, std::string unNombre, std::string unContacto, std::string unVivienda){
    ID = unID;
    nombre = unNombre;
    contacto = unContacto;
    vivienda = unVivienda;
}
Adoptante::Adoptante(const Adoptante& otro){
    ID = otro.ID;
    nombre = otro.nombre;
    contacto = otro.contacto;
    vivienda = otro.vivienda;
}

int Adoptante::getID() const {
    return ID;
}
std::string Adoptante::getNombre() const {
    return nombre;
}
std::string Adoptante::getContacto() const {
    return contacto;
}
std::string Adoptante::getVivienda() const {
    return vivienda;
}

void Adoptante::setID(int unID){
    ID = unID;
}
void Adoptante::setNombre(std::string unNombre){
    nombre = unNombre;
}
void Adoptante::setContacto(std::string unContacto){
    contacto = unContacto;
}
void Adoptante::setVivienda(std::string unVivienda){
    vivienda = unVivienda;
}

Adoptante& Adoptante::operator=(const Adoptante& otro){
    if (this != &otro){
        ID = otro.ID;
        nombre = otro.nombre;
        contacto = otro.contacto;
        vivienda = otro.vivienda;
    }
    return *this;
}
