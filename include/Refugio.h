#pragma once
#include <string>
#include "Animales.h"
#include "Perro.h"
#include "Gato.h"
#include "Adoptante.h"
#include "Solicitud.h"
#include "Coleccion.h"
#include "Excepciones.h"

class Refugio
{
private:
    // El refugio es dueno de cada Animales apuntado: los crea con new y los libera en el destructor.
    Animales** animales;
    int cantidadAnimales;
    int capacidadAnimales;
    int proximoIdAnimal;

    Coleccion<Adoptante> adoptantes;
    int proximoIdAdoptante;

    Coleccion<Solicitud> solicitudes;
    int proximoIdSolicitud;

    void agrandarArreglo();
    Solicitud* buscarSolicitud(int unID);

public:
    // Regla de los Tres
    Refugio();
    Refugio(const Refugio& otro);
    Refugio& operator=(const Refugio& otro);
    ~Refugio();

    int registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano);
    int registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior);

    // Toma posesion del animal. Lanza IdRepetidoException (sin tomar posesion) si el ID ya existe.
    void agregarAnimal(Animales* nuevo);

    int cantidad() const;
    Animales* buscarAnimal(int unID) const;
    Animales& operator[](int posicion) const;   // por posicion; lanza IndiceInvalidoException
    Animales* operator()(int unID) const;       // por ID; nullptr si no existe
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
