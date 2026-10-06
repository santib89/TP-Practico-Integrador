#pragma once
#include "Animales.h"
#include "Perro.h"
#include "Gato.h"
#include "Adoptante.h"
#include "Solicitud.h"

class Refugio
{
private:
    Animales** animales;
    int cantidadAnimales;
    int capacidadAnimales;
    int proximoIdAnimal;

    void agrandarArreglo();
    void guardarAnimal(Animales* nuevo);

    Adoptante* adoptantes;
    int cantidadAdoptantes;
    int capacidadAdoptantes;
    int proximoIdAdoptante;

    void agrandarAdoptantes();

    Solicitud* solicitudes;
    int cantidadSolicitudes;
    int capacidadSolicitudes;
    int proximoIdSolicitud;

    void agrandarSolicitudes();
    Solicitud* buscarSolicitud(int unID) const;

public:
    Refugio();
    Refugio(const Refugio& otro);
    ~Refugio();

    int registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano);
    int registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior);

    Animales* buscarAnimal(int unID) const;
    void listarAnimales() const;
    void listarDisponibles() const;

    int registrarAdoptante(std::string unNombre, std::string unContacto, std::string unVivienda);
    Adoptante* buscarAdoptante(int unID) const;

    int crearSolicitud(int unIdAdoptante, int unIdAnimal);
    int confirmarSolicitud(int unID);
    int cancelarSolicitud(int unID);
    int devolverAnimal(int unIdAnimal);
    void listarSolicitudes() const;

};