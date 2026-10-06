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
   // Constructores
   Animales();
   Animales(int unID, std::string unNombre, int unEdad, bool unSalud, bool unAdopcion);
   Animales(const Animales& otro);

   // Destructores
   virtual ~Animales();

   int getID() const ;
   std:: string getNombre() const ;
   int getEdad() const ;
   bool getSalud() const ;
   bool getAdopcion() const ;

   void setID(int unID);
   void setNombre(std:: string unNombre);
   void setEdad(int unEdad);
   void setSalud(bool unSalud);
   void setAdopcion(bool unAdopcion);

   virtual void mostrarInfo() const = 0;
   virtual Animales* clonar() const = 0;

   // Dos animales son iguales si tienen el mismo ID
   bool operator==(const Animales& otro) const;
   // !animal es true cuando el animal NO esta disponible (ya fue adoptado)
   bool operator!() const;
   
   
};
