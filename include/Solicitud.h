#pragma once
enum class EstadoSolicitud { Pendiente, Confirmada, Cancelada };
class Solicitud
{
private:
int ID;
int idAdoptante;
int idAnimal;
EstadoSolicitud estado;

public:
    // Getters
    int getID() const;
    int getIdAdoptante() const;
    int getIdAnimal() const;
    EstadoSolicitud getEstado() const;

    // Setters
    void setID(int unID);
    void setIdAdoptante(int unIdAdoptante);
    void setIdAnimal(int unIdAnimal);
    void setEstado(EstadoSolicitud unEstado);

    // Constructor 
    Solicitud(int unID, int unIdAdoptante, int unIdAnimal);
};