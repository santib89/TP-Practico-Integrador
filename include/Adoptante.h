#pragma once
#include <string>
class Adoptante
{
private:
    int ID;
    std::string nombre;
    std::string contacto;
    std::string vivienda;

public:
    Adoptante();
    Adoptante(int unID, std::string unNombre, std::string unContacto, std::string unVivienda);
    Adoptante(const Adoptante& otro);

    Adoptante& operator=(const Adoptante& otro);

    int getID() const;
    std::string getNombre() const;
    std::string getContacto() const;
    std::string getVivienda() const;

    void setID(int unID);
    void setNombre(std::string unNombre);
    void setContacto(std::string unContacto);
    void setVivienda(std::string unVivienda);
};
