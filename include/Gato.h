#pragma once
#include "Animales.h"
#include <string>
class Gato: public Animales
{
private: 
std:: string color;
bool esInterior;

public:
// Constructores
Gato();
Gato(int unID, std:: string unNombre, int unEdad, bool unSalud, bool unAdopcion, std:: string unColor, bool unEsInterior);
Gato(const Gato& otro);

// Getters
std:: string getColor() const;
bool getEsInterior() const;

// Setters
void setColor(std:: string unColor); 
void setEsInterior(bool unEsInterior);
};
