#include <iostream>
#include <string>
#include "../include/Refugio.h"
#include "../include/Coleccion.h"
#include "../include/Excepciones.h"

int total = 0;
int fallos = 0;

void verificar(bool condicion, std::string texto)
{
    total++;
    if (condicion)
    {
        std::cout << "  OK     " << texto << "\n";
    }
    else
    {
        fallos++;
        std::cout << "  FALLO  " << texto << "\n";
    }
}

void pruebasValidas()
{
    std::cout << "\nCasos validos\n";
    Refugio r;
    int idPerro = r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idGato = r.registrarGato("Michi", 2, "Gris", true);

    verificar(idPerro == 1 && idGato == 2, "los IDs se asignan en orden");
    verificar(r.cantidad() == 2, "el refugio tiene 2 animales");
    verificar(r(1)->getNombre() == "Rex", "buscar por ID con ()");
    verificar(r(99) == nullptr, "buscar un ID que no existe devuelve nullptr");
    verificar(r[1].getNombre() == "Michi", "acceder por posicion con []");

    Perro a(1, "A", 1, true, false, "X", 1.0);
    Gato b(1, "B", 2, true, false, "Y", false);
    Perro c(2, "C", 3, true, true, "Z", 2.0);
    verificar(a == b, "== es verdadero si tienen el mismo ID, aunque sean de distinto tipo");
    verificar(!(a == c), "== es falso si tienen distinto ID");
    verificar(!a == false, "! es falso si el animal esta disponible");
    verificar(!c == true, "! es verdadero si el animal ya fue adoptado");
}

void pruebasAdopcion()
{
    std::cout << "\nProceso de adopcion\n";
    Refugio r;
    r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idAdoptante = r.registrarAdoptante("Ana", "3584001122", "Casa");

    int solicitud = r.crearSolicitud(idAdoptante, 1);
    verificar(!r[0] == false, "con la solicitud pendiente el animal sigue disponible");

    r.confirmarSolicitud(solicitud);
    verificar(!r[0] == true, "al confirmar, el animal queda adoptado");

    r.devolverAnimal(1);
    verificar(!r[0] == false, "al devolverlo vuelve a estar disponible");

    int otra = r.crearSolicitud(idAdoptante, 1);
    r.cancelarSolicitud(otra);
    verificar(!r[0] == false, "cancelar una solicitud no cambia al animal");
}

void pruebasErrores()
{
    std::cout << "\nCasos de error\n";
    Refugio r;
    r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idAdoptante = r.registrarAdoptante("Ana", "3584001122", "Casa");

    bool atrapada = false;
    Perro* repetido = new Perro(1, "Otro", 1, true, false, "X", 1.0);
    try
    {
        r.agregarAnimal(repetido);
    }
    catch (const IdRepetidoException& e)
    {
        atrapada = true;
    }
    delete repetido;
    verificar(atrapada && r.cantidad() == 1, "ID repetido lanza IdRepetidoException");

    atrapada = false;
    try
    {
        r[5];
    }
    catch (const IndiceInvalidoException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "indice fuera de rango lanza IndiceInvalidoException");

    atrapada = false;
    try
    {
        r[-1];
    }
    catch (const IndiceInvalidoException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "indice negativo lanza IndiceInvalidoException");

    int solicitud = r.crearSolicitud(idAdoptante, 1);
    r.confirmarSolicitud(solicitud);

    atrapada = false;
    try
    {
        r.crearSolicitud(idAdoptante, 1);
    }
    catch (const AnimalNoDisponibleException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "pedir un animal ya adoptado lanza AnimalNoDisponibleException");

    atrapada = false;
    try
    {
        r.crearSolicitud(99, 1);
    }
    catch (const NoEncontradoException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "adoptante que no existe lanza NoEncontradoException");

    atrapada = false;
    try
    {
        r.crearSolicitud(idAdoptante, 99);
    }
    catch (const NoEncontradoException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "animal que no existe lanza NoEncontradoException");

    atrapada = false;
    try
    {
        r.confirmarSolicitud(solicitud);
    }
    catch (const OperacionInvalidaException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "confirmar una solicitud ya confirmada lanza OperacionInvalidaException");

    r.devolverAnimal(1);
    atrapada = false;
    try
    {
        r.devolverAnimal(1);
    }
    catch (const OperacionInvalidaException& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "devolver un animal que no estaba adoptado lanza OperacionInvalidaException");

    atrapada = false;
    try
    {
        r.registrarPerro("Rex", 3, "Labrador", 20.5);
        r[10];
    }
    catch (const ErrorRefugio& e)
    {
        atrapada = true;
    }
    verificar(atrapada, "las excepciones tambien se pueden atrapar como ErrorRefugio");
}

void pruebasCopiaProfunda()
{
    std::cout << "\nCopia profunda\n";
    Refugio original;
    original.registrarPerro("Rex", 3, "Labrador", 20.5);
    original.registrarGato("Michi", 2, "Gris", true);
    int idAdoptante = original.registrarAdoptante("Ana", "3584001122", "Casa");

    Refugio copia(original);
    verificar(copia.cantidad() == 2, "la copia tiene los mismos animales");
    verificar(&copia[0] != &original[0], "los animales de la copia estan en otra direccion de memoria");

    int solicitud = original.crearSolicitud(idAdoptante, 1);
    original.confirmarSolicitud(solicitud);
    verificar(!original[0] == true && !copia[0] == false, "adoptar en el original no cambia la copia");

    copia.registrarPerro("Toby", 1, "Mestizo", 8.0);
    verificar(original.cantidad() == 2 && copia.cantidad() == 3, "agregar a la copia no cambia el original");

    Refugio asignado;
    asignado.registrarGato("Luna", 4, "Negro", false);
    asignado = original;
    verificar(asignado.cantidad() == 2 && asignado[0].getNombre() == "Rex", "con = queda con los animales del original");
    verificar(&asignado[0] != &original[0], "con = tampoco se comparte la memoria");

    Refugio& mismo = asignado;
    asignado = mismo;
    verificar(asignado.cantidad() == 2, "asignar un refugio a si mismo no lo rompe");
}

void pruebasColeccion()
{
    std::cout << "\nColeccion generica\n";
    int antes = Coleccion<int>::cantidadInstancias();
    {
        Coleccion<int> numeros;
        Coleccion<std::string> palabras;
        for (int i = 0; i < 20; i++)
        {
            numeros.agregar(i);
        }
        palabras.agregar("hola");

        verificar(numeros.cantidad() == 20 && numeros[19] == 19, "Coleccion<int> crece mas alla de su capacidad inicial");
        verificar(palabras.cantidad() == 1 && palabras[0] == "hola", "Coleccion<string> guarda y devuelve datos");
        verificar(Coleccion<int>::cantidadInstancias() == antes + 1, "el contador estatico de int cuenta solo las de int");

        bool atrapada = false;
        try
        {
            numeros[20];
        }
        catch (const IndiceInvalidoException& e)
        {
            atrapada = true;
        }
        verificar(atrapada, "[] fuera de rango lanza IndiceInvalidoException");
    }
    verificar(Coleccion<int>::cantidadInstancias() == antes, "el contador vuelve al valor de antes al destruirlas");
}

void pruebaMemoria()
{
    std::cout << "\nLiberacion de memoria\n";
    int antes = Coleccion<Adoptante>::cantidadInstancias();
    for (int i = 0; i < 50; i++)
    {
        Refugio r;
        for (int j = 0; j < 50; j++)
        {
            r.registrarPerro("Rex", 3, "Labrador", 20.5);
            r.registrarGato("Michi", 2, "Gris", true);
        }
        Refugio copia(r);
        Refugio asignado;
        asignado = copia;
    }
    verificar(Coleccion<Adoptante>::cantidadInstancias() == antes, "se crean, copian y destruyen refugios y no quedan colecciones vivas");
}

int main()
{
    pruebasValidas();
    pruebasAdopcion();
    pruebasErrores();
    pruebasCopiaProfunda();
    pruebasColeccion();
    pruebaMemoria();

    std::cout << "\nResultado: " << (total - fallos) << " de " << total << " pruebas correctas\n";
    return 0;
}
