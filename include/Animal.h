#pragma once
#include <string>
class Animal
{
private:
    int ID;
    std::string nombre;
    int edad;
    bool salud;
    bool adopcion;

public:
    Animal();
    Animal(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion);
    Animal(const Animal& otro);

    virtual ~Animal();

    int getID() const;
    std::string getNombre() const;
    int getEdad() const;
    bool getSalud() const;
    bool getAdopcion() const;

    void setID(int unID);
    void setNombre(std::string unNombre);
    void setEdad(int unEdad);
    void setSalud(bool unSalud);
    void setAdopcion(bool unAdopcion);

    virtual void mostrarInfo() const = 0;
    virtual Animal* clonar() const = 0;

    bool operator==(const Animal& otro) const;
    bool operator!() const;
};
