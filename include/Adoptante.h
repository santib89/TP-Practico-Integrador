#pragma once
#include <string>
class Adoptante
{
private:
int ID;
std:: string nombre;
int contacto;
std:: string vivienda;

public:
    // Constructores
    Adoptante();
    Adoptante(int unID, std:: string unNombre, int unContacto, std:: string unVivienda);
    Adoptante(const Adoptante& otro);

    // Getters
    int getID() const;
    std:: string getNombre() const;
    int getContacto() const;
    std:: string getVivienda() const;

    // Setters
    void setID(int unID);
    void setNombre(std:: string unNombre);
    void setContacto(int unContacto);
    void setVivienda(std:: string unVivienda);
};
