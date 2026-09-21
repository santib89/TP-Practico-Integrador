#pragma once
#include <string>
class Animales
{
private:
int ID;
std:: string nombre;
int edad;
bool salud;
bool adopcion;

public:
   int getID() const ;
   std:: string getNombre() const ;
   int getEdad() const ;
   bool getSalud() const ;
   bool getAdopcion() const ;

   //Constructor
Animales(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion);
};
