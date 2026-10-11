#pragma once
#include <string>
enum class EstadoSolicitud { Pendiente, Confirmada, Cancelada };
class SolicitudAdopcion
{
private:
    int ID;
    int idAdoptante;
    int idAnimal;
    EstadoSolicitud estado;

public:
    SolicitudAdopcion();
    SolicitudAdopcion(int unID, int unIdAdoptante, int unIdAnimal);
    SolicitudAdopcion(const SolicitudAdopcion& otro);

    SolicitudAdopcion& operator=(const SolicitudAdopcion& otro);

    int getID() const;
    int getIdAdoptante() const;
    int getIdAnimal() const;
    EstadoSolicitud getEstado() const;
    std::string getEstadoTexto() const;

    void setID(int unID);
    void setIdAdoptante(int unIdAdoptante);
    void setIdAnimal(int unIdAnimal);
    void setEstado(EstadoSolicitud unEstado);
};
