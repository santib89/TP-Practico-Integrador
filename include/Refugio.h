#pragma once
#include <string>
#include "Animal.h"
#include "Perro.h"
#include "Gato.h"
#include "Adoptante.h"
#include "SolicitudAdopcion.h"
#include "Coleccion.h"
#include "Excepciones.h"

class Refugio
{
private:
    Animal** animales;
    int cantidadAnimales;
    int capacidadAnimales;
    int proximoIdAnimal;

    Coleccion<Adoptante> adoptantes;
    int proximoIdAdoptante;

    Coleccion<SolicitudAdopcion> solicitudes;
    int proximoIdSolicitud;

    void agrandarArreglo();
    SolicitudAdopcion* buscarSolicitud(int unID);

public:
    Refugio();
    Refugio(const Refugio& otro);
    Refugio& operator=(const Refugio& otro);
    ~Refugio();

    int registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano);
    int registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior);

    void agregarAnimal(Animal* nuevo);

    int cantidad() const;
    Animal* buscarAnimal(int unID) const;
    Animal& operator[](int posicion) const;
    Animal* operator()(int unID) const;
    void listarAnimales() const;
    void listarDisponibles() const;

    int registrarAdoptante(std::string unNombre, std::string unContacto, std::string unVivienda);
    const Adoptante* buscarAdoptante(int unID) const;

    int crearSolicitud(int unIdAdoptante, int unIdAnimal);
    void confirmarSolicitud(int unID);
    void cancelarSolicitud(int unID);
    void devolverAnimal(int unIdAnimal);
    void listarSolicitudes() const;
};
