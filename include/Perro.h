#pragma once
#include "Animales.h"
#include <string>
class Perro: public Animales
{
private: 
std:: string raza;
double tamano;

public: 
std:: string getRaza() const;
double getTamano() const;

//Setters
void setRaza(std:: string unRaza); 
void setTamano(double unTamano);

//Constructor
Perro(int unID, std:: string unNombre, int unEdad, bool unSalud, bool unAdopcion, std:: string Raza, double Tamano);
};
