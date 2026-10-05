#include "../include/Solicitud.h"

// Constructor
Solicitud::Solicitud(int unID, int unIdAdoptante, int unIdAnimal){
    ID = unID;
    idAdoptante = unIdAdoptante;
    idAnimal = unIdAnimal;
    estado = EstadoSolicitud::Pendiente;
}

// Getters
int Solicitud::getID() const {
    return ID;
}
int Solicitud::getIdAdoptante() const {
    return idAdoptante;
}
int Solicitud::getIdAnimal() const {
    return idAnimal;
}
EstadoSolicitud Solicitud::getEstado() const {
    return estado;
}

// Setters
void Solicitud::setID(int unID){
    ID = unID;
}
void Solicitud::setIdAdoptante(int unIdAdoptante){
    idAdoptante = unIdAdoptante;
}
void Solicitud::setIdAnimal(int unIdAnimal){
    idAnimal = unIdAnimal;
}
void Solicitud::setEstado(EstadoSolicitud unEstado){
    estado = unEstado;
}
