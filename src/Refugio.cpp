#include "../include/Refugio.h"
#include <iostream>

Refugio::Refugio()
    : animales(new Animales*[10]),
      cantidadAnimales(0),
      capacidadAnimales(10),
      proximoIdAnimal(1),
      proximoIdAdoptante(1),
      proximoIdSolicitud(1)
{
}

// Copia profunda: cada animal se clona (con su tipo real, Perro o Gato)
Refugio::Refugio(const Refugio& otro)
    : animales(new Animales*[otro.capacidadAnimales]),
      cantidadAnimales(otro.cantidadAnimales),
      capacidadAnimales(otro.capacidadAnimales),
      proximoIdAnimal(otro.proximoIdAnimal),
      adoptantes(otro.adoptantes),
      proximoIdAdoptante(otro.proximoIdAdoptante),
      solicitudes(otro.solicitudes),
      proximoIdSolicitud(otro.proximoIdSolicitud)
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        animales[i] = otro.animales[i]->clonar();
    }
}

Refugio& Refugio::operator=(const Refugio& otro)
{
    if (this != &otro)
    {
        Animales** nuevo = new Animales*[otro.capacidadAnimales];
        for (int i = 0; i < otro.cantidadAnimales; i++)
        {
            nuevo[i] = otro.animales[i]->clonar();
        }

        for (int i = 0; i < cantidadAnimales; i++)
        {
            delete animales[i];
        }
        delete[] animales;

        animales = nuevo;
        cantidadAnimales = otro.cantidadAnimales;
        capacidadAnimales = otro.capacidadAnimales;
        proximoIdAnimal = otro.proximoIdAnimal;

        adoptantes = otro.adoptantes;
        proximoIdAdoptante = otro.proximoIdAdoptante;
        solicitudes = otro.solicitudes;
        proximoIdSolicitud = otro.proximoIdSolicitud;
    }
    return *this;
}

Refugio::~Refugio()
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        delete animales[i];
    }
    delete[] animales;
}

void Refugio::agrandarArreglo()
{
    int nuevaCapacidad = capacidadAnimales * 2;
    Animales** nuevo = new Animales*[nuevaCapacidad];

    for (int i = 0; i < cantidadAnimales; i++)
    {
        nuevo[i] = animales[i];
    }

    delete[] animales;
    animales = nuevo;
    capacidadAnimales = nuevaCapacidad;
}

void Refugio::agregarAnimal(Animales* nuevo)
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        if (*animales[i] == *nuevo)
        {
            throw IdRepetidoException(nuevo->getID());
        }
    }

    if (cantidadAnimales == capacidadAnimales)
    {
        agrandarArreglo();
    }

    animales[cantidadAnimales] = nuevo;
    cantidadAnimales++;

    if (nuevo->getID() >= proximoIdAnimal)
    {
        proximoIdAnimal = nuevo->getID() + 1;
    }
}

int Refugio::registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano)
{
    int id = proximoIdAnimal;
    Animales* nuevo = new Perro(id, unNombre, unEdad, true, false, unRaza, unTamano);
    try
    {
        agregarAnimal(nuevo);
    }
    catch (...)
    {
        delete nuevo;
        throw;
    }
    return id;
}

int Refugio::registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior)
{
    int id = proximoIdAnimal;
    Animales* nuevo = new Gato(id, unNombre, unEdad, true, false, unColor, unEsInterior);
    try
    {
        agregarAnimal(nuevo);
    }
    catch (...)
    {
        delete nuevo;
        throw;
    }
    return id;
}

int Refugio::cantidad() const
{
    return cantidadAnimales;
}

Animales* Refugio::buscarAnimal(int unID) const
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        Animales* actual = *(animales + i);
        if (actual->getID() == unID)
        {
            return actual;
        }
    }
    return nullptr;
}

Animales& Refugio::operator[](int posicion) const
{
    if (posicion < 0 || posicion >= cantidadAnimales)
    {
        throw IndiceInvalidoException(posicion, cantidadAnimales);
    }
    return *animales[posicion];
}

Animales* Refugio::operator()(int unID) const
{
    return buscarAnimal(unID);
}

void Refugio::listarAnimales() const
{
    if (cantidadAnimales == 0)
    {
        std::cout << "No hay animales registrados\n";
        return;
    }

    for (int i = 0; i < cantidadAnimales; i++)
    {
        (*this)[i].mostrarInfo();
    }
}

void Refugio::listarDisponibles() const
{
    bool hayDisponibles = false;

    for (int i = 0; i < cantidadAnimales; i++)
    {
        // !animal es true cuando el animal NO esta disponible
        if (!(*this)[i])
        {
            continue;
        }
        (*this)[i].mostrarInfo();
        hayDisponibles = true;
    }

    if (!hayDisponibles)
    {
        std::cout << "No hay animales disponibles\n";
    }
}

int Refugio::registrarAdoptante(std::string unNombre, std::string unContacto, std::string unVivienda)
{
    int id = proximoIdAdoptante;
    adoptantes.agregar(Adoptante(id, unNombre, unContacto, unVivienda));
    proximoIdAdoptante++;
    return id;
}

const Adoptante* Refugio::buscarAdoptante(int unID) const
{
    for (int i = 0; i < adoptantes.cantidad(); i++)
    {
        if (adoptantes[i].getID() == unID)
        {
            return &adoptantes[i];
        }
    }
    return nullptr;
}

Solicitud* Refugio::buscarSolicitud(int unID)
{
    for (int i = 0; i < solicitudes.cantidad(); i++)
    {
        if (solicitudes[i].getID() == unID)
        {
            return &solicitudes[i];
        }
    }
    return nullptr;
}

int Refugio::crearSolicitud(int unIdAdoptante, int unIdAnimal)
{
    if (buscarAdoptante(unIdAdoptante) == nullptr)
    {
        throw NoEncontradoException("un adoptante", unIdAdoptante);
    }

    Animales* animal = (*this)(unIdAnimal);
    if (animal == nullptr)
    {
        throw NoEncontradoException("un animal", unIdAnimal);
    }

    if (!*animal)
    {
        throw AnimalNoDisponibleException(unIdAnimal);
    }

    int id = proximoIdSolicitud;
    solicitudes.agregar(Solicitud(id, unIdAdoptante, unIdAnimal));
    proximoIdSolicitud++;
    return id;
}

void Refugio::confirmarSolicitud(int unID)
{
    Solicitud* solicitud = buscarSolicitud(unID);
    if (solicitud == nullptr)
    {
        throw NoEncontradoException("una solicitud", unID);
    }

    if (solicitud->getEstado() != EstadoSolicitud::Pendiente)
    {
        throw OperacionInvalidaException("La solicitud no esta pendiente");
    }

    Animales* animal = buscarAnimal(solicitud->getIdAnimal());
    if (!*animal)
    {
        throw AnimalNoDisponibleException(animal->getID());
    }

    animal->setAdopcion(true);
    solicitud->setEstado(EstadoSolicitud::Confirmada);
}

void Refugio::cancelarSolicitud(int unID)
{
    Solicitud* solicitud = buscarSolicitud(unID);
    if (solicitud == nullptr)
    {
        throw NoEncontradoException("una solicitud", unID);
    }

    if (solicitud->getEstado() != EstadoSolicitud::Pendiente)
    {
        throw OperacionInvalidaException("La solicitud no esta pendiente");
    }

    solicitud->setEstado(EstadoSolicitud::Cancelada);
}

void Refugio::devolverAnimal(int unIdAnimal)
{
    Animales* animal = (*this)(unIdAnimal);
    if (animal == nullptr)
    {
        throw NoEncontradoException("un animal", unIdAnimal);
    }

    if (!animal->getAdopcion())
    {
        throw OperacionInvalidaException("El animal no estaba adoptado");
    }

    animal->setAdopcion(false);
}

void Refugio::listarSolicitudes() const
{
    if (solicitudes.cantidad() == 0)
    {
        std::cout << "No hay solicitudes registradas\n";
        return;
    }

    int confirmadas = 0;

    for (int i = 0; i < solicitudes.cantidad(); i++)
    {
        if (solicitudes[i].getEstado() == EstadoSolicitud::Confirmada)
        {
            confirmadas++;
        }

        const Adoptante* adoptante = buscarAdoptante(solicitudes[i].getIdAdoptante());
        const Animales* animal = buscarAnimal(solicitudes[i].getIdAnimal());

        std::cout << "Solicitud ID: " << solicitudes[i].getID()
                  << " | Adoptante: " << adoptante->getID() << " (" << adoptante->getNombre() << ")"
                  << " | Animal: " << animal->getID() << " (" << animal->getNombre() << ")"
                  << " | Estado: " << solicitudes[i].getEstadoTexto() << "\n";
    }

    std::cout << "Adopciones confirmadas: " << confirmadas << "\n";
}
