#include "../include/SolicitudAdopcion.h"

SolicitudAdopcion::SolicitudAdopcion(){
    ID = 0;
    idAdoptante = 0;
    idAnimal = 0;
    estado = EstadoSolicitud::Pendiente;
}

SolicitudAdopcion::SolicitudAdopcion(int unID, int unIdAdoptante, int unIdAnimal){
    ID = unID;
    idAdoptante = unIdAdoptante;
    idAnimal = unIdAnimal;
    estado = EstadoSolicitud::Pendiente;
}

SolicitudAdopcion::SolicitudAdopcion(const SolicitudAdopcion& otro){
    ID = otro.ID;
    idAdoptante = otro.idAdoptante;
    idAnimal = otro.idAnimal;
    estado = otro.estado;
}

int SolicitudAdopcion::getID() const {
    return ID;
}
int SolicitudAdopcion::getIdAdoptante() const {
    return idAdoptante;
}
int SolicitudAdopcion::getIdAnimal() const {
    return idAnimal;
}
EstadoSolicitud SolicitudAdopcion::getEstado() const {
    return estado;
}

std::string SolicitudAdopcion::getEstadoTexto() const {
    switch (estado){
        case EstadoSolicitud::Pendiente:
            return "Pendiente";
        case EstadoSolicitud::Confirmada:
            return "Confirmada";
        default:
            return "Cancelada";
    }
}

void SolicitudAdopcion::setID(int unID){
    ID = unID;
}
void SolicitudAdopcion::setIdAdoptante(int unIdAdoptante){
    idAdoptante = unIdAdoptante;
}
void SolicitudAdopcion::setIdAnimal(int unIdAnimal){
    idAnimal = unIdAnimal;
}
void SolicitudAdopcion::setEstado(EstadoSolicitud unEstado){
    estado = unEstado;
}

SolicitudAdopcion& SolicitudAdopcion::operator=(const SolicitudAdopcion& otro){
    if (this != &otro){
        ID = otro.ID;
        idAdoptante = otro.idAdoptante;
        idAnimal = otro.idAnimal;
        estado = otro.estado;
    }
    return *this;
}
