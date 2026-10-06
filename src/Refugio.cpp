#include "../include/Refugio.h"
#include <iostream>

Refugio::Refugio()
{
    capacidadAnimales = 10;
    cantidadAnimales = 0;
    proximoIdAnimal = 1;
    animales = new Animales*[capacidadAnimales];

    capacidadAdoptantes = 10;
    cantidadAdoptantes = 0;
    proximoIdAdoptante = 1;
    adoptantes = new Adoptante[capacidadAdoptantes];

    capacidadSolicitudes = 10;
    cantidadSolicitudes = 0;
    proximoIdSolicitud = 1;
    solicitudes = new Solicitud[capacidadSolicitudes];
}

Refugio::~Refugio()
{
    for (int i = 0; i < cantidadAnimales; i++)
    {
        delete animales[i];
    }
    delete[] animales;
    delete[] adoptantes;
    delete[] solicitudes;
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

void Refugio::guardarAnimal(Animales* nuevo)
{
    if (cantidadAnimales == capacidadAnimales)
    {
        agrandarArreglo();
    }

    animales[cantidadAnimales] = nuevo;
    cantidadAnimales++;
}

int Refugio::registrarPerro(std::string unNombre, int unEdad, std::string unRaza, double unTamano)
{
    int id = proximoIdAnimal++;
    guardarAnimal(new Perro(id, unNombre, unEdad, true, false, unRaza, unTamano));
    return id;
}

int Refugio::registrarGato(std::string unNombre, int unEdad, std::string unColor, bool unEsInterior)
{
    int id = proximoIdAnimal++;
    guardarAnimal(new Gato(id, unNombre, unEdad, true, false, unColor, unEsInterior));
    return id;
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

void Refugio::listarAnimales() const
{
    if (cantidadAnimales == 0)
    {
        std::cout << "No hay animales registrados\n";
        return;
    }

    for (int i = 0; i < cantidadAnimales; i++)
    {
        animales[i]->mostrarInfo();
    }
}

void Refugio::listarDisponibles() const
{
    bool hayDisponibles = false;

    for (int i = 0; i < cantidadAnimales; i++)
    {
        if (!animales[i]->getAdopcion())
        {
            animales[i]->mostrarInfo();
            hayDisponibles = true;
        }
    }

    if (!hayDisponibles)
    {
        std::cout << "No hay animales disponibles\n";
    }
}

void Refugio::agrandarAdoptantes()
{
    int nuevaCapacidad = capacidadAdoptantes * 2;
    Adoptante* nuevo = new Adoptante[nuevaCapacidad];

    for (int i = 0; i < cantidadAdoptantes; i++)
    {
        nuevo[i] = adoptantes[i];
    }

    delete[] adoptantes;
    adoptantes = nuevo;
    capacidadAdoptantes = nuevaCapacidad;
}

int Refugio::registrarAdoptante(std::string unNombre, std::string unContacto, std::string unVivienda)
{
    if (cantidadAdoptantes == capacidadAdoptantes)
    {
        agrandarAdoptantes();
    }

    int id = proximoIdAdoptante;
    adoptantes[cantidadAdoptantes] = Adoptante(id, unNombre, unContacto, unVivienda);
    cantidadAdoptantes++;
    proximoIdAdoptante++;

    return id;
}

Adoptante* Refugio::buscarAdoptante(int unID) const
{
    for (int i = 0; i < cantidadAdoptantes; i++)
    {
        if (adoptantes[i].getID() == unID)
        {
            return &adoptantes[i];
        }
    }
    return nullptr;
}

void Refugio::agrandarSolicitudes()
{
    int nuevaCapacidad = capacidadSolicitudes * 2;
    Solicitud* nuevo = new Solicitud[nuevaCapacidad];

    for (int i = 0; i < cantidadSolicitudes; i++)
    {
        nuevo[i] = solicitudes[i];
    }

    delete[] solicitudes;
    solicitudes = nuevo;
    capacidadSolicitudes = nuevaCapacidad;
}

Solicitud* Refugio::buscarSolicitud(int unID) const
{
    for (int i = 0; i < cantidadSolicitudes; i++)
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
        return -1;
    }

    Animales* animal = buscarAnimal(unIdAnimal);
    if (animal == nullptr)
    {
        return -2;
    }

    if (animal->getAdopcion())
    {
        return -3;
    }

    if (cantidadSolicitudes == capacidadSolicitudes)
    {
        agrandarSolicitudes();
    }

    int id = proximoIdSolicitud;
    solicitudes[cantidadSolicitudes] = Solicitud(id, unIdAdoptante, unIdAnimal);
    cantidadSolicitudes++;
    proximoIdSolicitud++;

    return id;
}

int Refugio::confirmarSolicitud(int unID)
{
    Solicitud* solicitud = buscarSolicitud(unID);
    if (solicitud == nullptr)
    {
        return -1;
    }

    if (solicitud->getEstado() != EstadoSolicitud::Pendiente)
    {
        return -2;
    }

    Animales* animal = buscarAnimal(solicitud->getIdAnimal());
    if (animal->getAdopcion())
    {
        return -3;
    }

    animal->setAdopcion(true);
    solicitud->setEstado(EstadoSolicitud::Confirmada);

    return 0;
}

int Refugio::cancelarSolicitud(int unID)
{
    Solicitud* solicitud = buscarSolicitud(unID);
    if (solicitud == nullptr)
    {
        return -1;
    }

    if (solicitud->getEstado() != EstadoSolicitud::Pendiente)
    {
        return -2;
    }

    solicitud->setEstado(EstadoSolicitud::Cancelada);

    return 0;
}

int Refugio::devolverAnimal(int unIdAnimal)
{
    Animales* animal = buscarAnimal(unIdAnimal);
    if (animal == nullptr)
    {
        return -1;
    }

    if (!animal->getAdopcion())
    {
        return -2;
    }

    animal->setAdopcion(false);

    return 0;
}

void Refugio::listarSolicitudes() const
{
    if (cantidadSolicitudes == 0)
    {
        std::cout << "No hay solicitudes registradas\n";
        return;
    }

    int confirmadas = 0;

    for (int i = 0; i < cantidadSolicitudes; i++)
    {
        if (solicitudes[i].getEstado() == EstadoSolicitud::Confirmada)
        {
            confirmadas++;
        }

        Adoptante* adoptante = buscarAdoptante(solicitudes[i].getIdAdoptante());
        Animales* animal = buscarAnimal(solicitudes[i].getIdAnimal());

        std::cout << "Solicitud ID: " << solicitudes[i].getID()
                  << " | Adoptante: " << adoptante->getID() << " (" << adoptante->getNombre() << ")"
                  << " | Animal: " << animal->getID() << " (" << animal->getNombre() << ")"
                  << " | Estado: " << solicitudes[i].getEstadoTexto() << "\n";
    }

    std::cout << "Adopciones confirmadas: " << confirmadas << "\n";
}
