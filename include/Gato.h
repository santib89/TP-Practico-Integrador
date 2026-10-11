#pragma once
#include "Animal.h"
#include <string>
class Gato: public Animal
{
private:
    std::string color;
    bool esInterior;

public:
    Gato();
    Gato(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion, std::string unColor, bool unEsInterior);
    Gato(const Gato& otro);

    std::string getColor() const;
    bool getEsInterior() const;

    void setColor(std::string unColor);
    void setEsInterior(bool unEsInterior);

    void mostrarInfo() const override;
    Animal* clonar() const override;
};
