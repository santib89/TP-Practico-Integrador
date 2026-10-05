#include "../include/Adoptante.h"

Adoptante::Adoptante(int unID, std::string unNombre, int unContacto, std::string unVivienda){
    ID = unID;
    nombre = unNombre;
    contacto = unContacto;
    vivienda = unVivienda;
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
