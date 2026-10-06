#pragma once
#include <string>
enum class EstadoSolicitud { Pendiente, Confirmada, Cancelada };
class Solicitud
{
private:
int ID;
int idAdoptante;
int idAnimal;
EstadoSolicitud estado;

public:
    // Constructores
    Solicitud();
    Solicitud(int unID, int unIdAdoptante, int unIdAnimal);
    Solicitud(const Solicitud& otro);

    Solicitud& operator=(const Solicitud& otro);

    // Getters
    int getID() const;
    int getIdAdoptante() const;
    int getIdAnimal() const;
    EstadoSolicitud getEstado() const;
    std::string getEstadoTexto() const;

    // Setters
    void setID(int unID);
    void setIdAdoptante(int unIdAdoptante);
    void setIdAnimal(int unIdAnimal);
    void setEstado(EstadoSolicitud unEstado);
};
