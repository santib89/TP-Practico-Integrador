#pragma once
#include "Animal.h"
#include <string>
class Perro: public Animal
{
private:
    std::string raza;
    double tamano;

public:
    Perro();
    Perro(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unRaza, double unTamano);
    Perro(const Perro& otro);

    std::string getRaza() const;
    double getTamano() const;

    void setRaza(std::string unRaza);
    void setTamano(double unTamano);

    void mostrarInfo() const override;
    Animal* clonar() const override;
};
