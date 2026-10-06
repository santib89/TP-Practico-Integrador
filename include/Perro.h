#pragma once
#include "Animales.h"
#include <string>
class Perro: public Animales
{
private: 
std:: string raza;
double tamano;

public: 
// Constructores
Perro();
Perro(int unID, std:: string unNombre, int unEdad, bool unSalud, bool unAdopcion, std:: string unRaza, double unTamano);
Perro(const Perro& otro);

// Getters
std:: string getRaza() const;
double getTamano() const;

// Setters
void setRaza(std:: string unRaza); 
void setTamano(double unTamano);

void mostrarInfo() const override;
Animales* clonar() const override;
};
