#include "../include/Solicitud.h"

// Constructores
// Por defecto: solicitud vacia, en estado Pendiente
Solicitud::Solicitud(){
    ID = 0;
    idAdoptante = 0;
    idAnimal = 0;
    estado = EstadoSolicitud::Pendiente;
}

// Parametrizado: toda solicitud nueva arranca en estado Pendiente
Solicitud::Solicitud(int unID, int unIdAdoptante, int unIdAnimal){
    ID = unID;
    idAdoptante = unIdAdoptante;
    idAnimal = unIdAnimal;
    estado = EstadoSolicitud::Pendiente;
}

// De copia: copia cada atributo, incluido el estado actual
Solicitud::Solicitud(const Solicitud& otro){
    ID = otro.ID;
    idAdoptante = otro.idAdoptante;
    idAnimal = otro.idAnimal;
    estado = otro.estado;
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

std::string Solicitud::getEstadoTexto() const {
    switch (estado){
        case EstadoSolicitud::Pendiente:
            return "Pendiente";
        case EstadoSolicitud::Confirmada:
            return "Confirmada";
        default:
            return "Cancelada";
    }
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

Solicitud& Solicitud::operator=(const Solicitud& otro){
    if (this != &otro){
        ID = otro.ID;
        idAdoptante = otro.idAdoptante;
        idAnimal = otro.idAnimal;
        estado = otro.estado;
    }
    return *this;
}
