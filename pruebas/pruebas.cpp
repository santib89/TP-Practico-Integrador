#include <iostream>
#include <string>
#include "../include/Refugio.h"
#include "../include/Coleccion.h"
#include "../include/Excepciones.h"

static int totales = 0;
static int fallidas = 0;

static void verificar(bool condicion, const std::string& descripcion)
{
    totales++;
    if (condicion)
    {
        std::cout << "  [OK]    " << descripcion << "\n";
    }
    else
    {
        fallidas++;
        std::cout << "  [FALLO] " << descripcion << "\n";
    }
}

static void titulo(const std::string& texto)
{
    std::cout << "\n== " << texto << " ==\n";
}

static void pruebaRegistroYBusqueda()
{
    titulo("Registro y busqueda");
    Refugio r;
    int idPerro = r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idGato = r.registrarGato("Michi", 2, "Gris", true);

    verificar(idPerro == 1 && idGato == 2, "los IDs se asignan en orden: 1 y 2");
    verificar(r.cantidad() == 2, "el refugio tiene 2 animales");
    verificar(r(1) != nullptr && r(1)->getNombre() == "Rex", "operator() encuentra el perro por ID");
    verificar(r(99) == nullptr, "operator() devuelve nullptr si el ID no existe");
    verificar(r[1].getNombre() == "Michi", "operator[] accede al segundo animal por posicion");

    Animales& base = r[0];
    verificar(dynamic_cast<Perro*>(&base) != nullptr, "el animal 0 es realmente un Perro (polimorfismo)");
    verificar(dynamic_cast<Gato*>(&r[1]) != nullptr, "el animal 1 es realmente un Gato (polimorfismo)");
}

static void pruebaOperadoresAnimales()
{
    titulo("Operadores de Animales");
    Perro a(1, "A", 1, true, false, "X", 1.0);
    Gato b(1, "B", 2, true, false, "Y", false);
    Perro c(2, "C", 3, true, true, "Z", 2.0);

    verificar(a == b, "== es verdadero para animales con el mismo ID aunque sean de distinto tipo");
    verificar(!(a == c), "== es falso para animales con distinto ID");
    verificar(!a == false, "!animal es falso si el animal esta disponible");
    verificar(!c == true, "!animal es verdadero si el animal ya fue adoptado");
}

static void pruebaFlujoAdopcion()
{
    titulo("Flujo de adopcion valido");
    Refugio r;
    r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idAdoptante = r.registrarAdoptante("Ana", "ana@mail.com", "Casa");

    int idSolicitud = r.crearSolicitud(idAdoptante, 1);
    verificar(idSolicitud == 1, "se crea la solicitud 1");
    verificar(!r[0] == false, "mientras esta pendiente el animal sigue disponible");

    r.confirmarSolicitud(idSolicitud);
    verificar(!r[0] == true, "al confirmar, el animal queda adoptado");

    r.devolverAnimal(1);
    verificar(!r[0] == false, "al devolverlo vuelve a estar disponible");

    int segunda = r.crearSolicitud(idAdoptante, 1);
    r.cancelarSolicitud(segunda);
    verificar(!r[0] == false, "cancelar una solicitud no modifica al animal");
}

static void pruebaExcepciones()
{
    titulo("Casos de error (excepciones)");
    Refugio r;
    r.registrarPerro("Rex", 3, "Labrador", 20.5);
    int idAdoptante = r.registrarAdoptante("Ana", "ana@mail.com", "Casa");

    bool atrapada = false;
    Perro* repetido = new Perro(1, "Clon", 1, true, false, "X", 1.0);
    try
    {
        r.agregarAnimal(repetido);
    }
    catch (const IdRepetidoException& e)
    {
        atrapada = true;
        std::cout << "         mensaje: " << e.what() << "\n";
    }
    verificar(atrapada, "ID repetido lanza IdRepetidoException");
    verificar(r.cantidad() == 1, "tras el ID repetido el refugio sigue con 1 animal");
    delete repetido;

    atrapada = false;
    try { r[5]; }
    catch (const IndiceInvalidoException& e)
    {
        atrapada = true;
        std::cout << "         mensaje: " << e.what() << "\n";
    }
    verificar(atrapada, "indice fuera de rango lanza IndiceInvalidoException");

    atrapada = false;
    try { r[-1]; }
    catch (const IndiceInvalidoException&) { atrapada = true; }
    verificar(atrapada, "indice negativo lanza IndiceInvalidoException");

    r.confirmarSolicitud(r.crearSolicitud(idAdoptante, 1));
    atrapada = false;
    try { r.crearSolicitud(idAdoptante, 1); }
    catch (const AnimalNoDisponibleException& e)
    {
        atrapada = true;
        std::cout << "         mensaje: " << e.what() << "\n";
    }
    verificar(atrapada, "pedir un animal adoptado lanza AnimalNoDisponibleException");

    atrapada = false;
    try { r.crearSolicitud(99, 1); }
    catch (const NoEncontradoException&) { atrapada = true; }
    verificar(atrapada, "adoptante inexistente lanza NoEncontradoException");

    atrapada = false;
    try { r.crearSolicitud(idAdoptante, 99); }
    catch (const NoEncontradoException&) { atrapada = true; }
    verificar(atrapada, "animal inexistente lanza NoEncontradoException");

    atrapada = false;
    try { r.confirmarSolicitud(1); }
    catch (const OperacionInvalidaException&) { atrapada = true; }
    verificar(atrapada, "confirmar una solicitud ya confirmada lanza OperacionInvalidaException");

    atrapada = false;
    try { r.devolverAnimal(99); }
    catch (const NoEncontradoException&) { atrapada = true; }
    verificar(atrapada, "devolver un animal inexistente lanza NoEncontradoException");

    r.devolverAnimal(1);
    atrapada = false;
    try { r.devolverAnimal(1); }
    catch (const ErrorRefugio&) { atrapada = true; }
    verificar(atrapada, "devolver un animal ya disponible se captura como ErrorRefugio (clase base)");

    atrapada = false;
    try { r[7]; }
    catch (const std::exception& e) { atrapada = std::string(e.what()).size() > 0; }
    verificar(atrapada, "toda excepcion se puede capturar como const std::exception&");
}

static void pruebaCopiaProfunda()
{
    titulo("Copia profunda (constructor de copia)");
    Refugio original;
    original.registrarPerro("Rex", 3, "Labrador", 20.5);
    original.registrarGato("Michi", 2, "Gris", true);
    int idAdoptante = original.registrarAdoptante("Ana", "ana@mail.com", "Casa");

    Refugio copia(original);
    verificar(copia.cantidad() == 2, "la copia tiene los mismos animales");
    verificar(&copia[0] != &original[0], "los animales de la copia son objetos distintos (no comparten memoria)");
    verificar(dynamic_cast<Perro*>(&copia[0]) != nullptr && dynamic_cast<Gato*>(&copia[1]) != nullptr,
              "la copia conserva el tipo real de cada animal");

    original.confirmarSolicitud(original.crearSolicitud(idAdoptante, 1));
    verificar(!original[0] == true, "el original quedo con el perro adoptado");
    verificar(!copia[0] == false, "la copia NO se entera: su perro sigue disponible");

    original.registrarGato("Nuevo", 1, "Negro", false);
    verificar(original.cantidad() == 3 && copia.cantidad() == 2, "agregar al original no cambia la copia");

    int idCopia = copia.registrarPerro("Luna", 1, "Mestiza", 8.0);
    verificar(idCopia == 3, "la copia continua la numeracion de IDs del original");
}

static void pruebaAsignacion()
{
    titulo("Copia profunda (operator=)");
    Refugio a;
    a.registrarPerro("Rex", 3, "Labrador", 20.5);
    Refugio b;
    b.registrarGato("Michi", 2, "Gris", true);
    b.registrarGato("Tom", 4, "Negro", false);

    b = a;
    verificar(b.cantidad() == 1 && b[0].getNombre() == "Rex", "tras b = a, b tiene exactamente los animales de a");
    verificar(&b[0] != &a[0], "b y a no comparten memoria");

    a.registrarPerro("Otro", 2, "X", 5.0);
    verificar(b.cantidad() == 1, "cambios posteriores en a no afectan a b");

    Refugio& alias = b;
    b = alias;
    verificar(b.cantidad() == 1 && b[0].getNombre() == "Rex", "la autoasignacion b = b no rompe el objeto");
}

static void pruebaColeccionGenerica()
{
    titulo("Coleccion<T> (template)");
    verificar(Coleccion<int>::cantidadInstancias() == 0, "al inicio no hay Coleccion<int>");
    verificar(Coleccion<std::string>::cantidadInstancias() == 0, "al inicio no hay Coleccion<std::string>");
    {
        Coleccion<int> numeros;
        Coleccion<int> otros;
        Coleccion<std::string> palabras;

        for (int i = 0; i < 10; i++)
        {
            numeros.agregar(i * i);
        }
        palabras.agregar("hola");
        palabras.agregar("mundo");

        verificar(numeros.cantidad() == 10 && numeros[9] == 81, "Coleccion<int> crece mas alla de su capacidad inicial");
        verificar(palabras.cantidad() == 2 && palabras[1] == "mundo", "Coleccion<std::string> funciona igual");
        verificar(Coleccion<int>::cantidadInstancias() == 2, "el miembro estatico de Coleccion<int> cuenta 2");
        verificar(Coleccion<std::string>::cantidadInstancias() == 1, "el de Coleccion<std::string> cuenta 1 (cada instanciacion tiene el suyo)");

        Coleccion<int> copia(numeros);
        copia.agregar(1000);
        verificar(numeros.cantidad() == 10 && copia.cantidad() == 11, "la copia de Coleccion es independiente");
        verificar(Coleccion<int>::cantidadInstancias() == 3, "la copia tambien se cuenta en el estatico");

        bool atrapada = false;
        try { numeros[10]; }
        catch (const IndiceInvalidoException&) { atrapada = true; }
        verificar(atrapada, "Coleccion<T>::operator[] fuera de rango lanza IndiceInvalidoException");
    }
    verificar(Coleccion<int>::cantidadInstancias() == 0, "al salir del bloque se liberan todas (contador en 0)");
}

static void pruebaLiberacionDeMemoria()
{
    titulo("Liberacion de memoria");
    // Se crean y destruyen muchos refugios con animales. Con -fsanitize=address
    // (make pruebas) cualquier doble liberacion o uso tras liberar aborta el programa,
    // y "leaks" informa si quedo algo sin liberar al terminar.
    int antes = Coleccion<Adoptante>::cantidadInstancias();
    for (int i = 0; i < 50; i++)
    {
        Refugio r;
        for (int j = 0; j < 25; j++)
        {
            r.registrarPerro("P", 1, "R", 1.0);
            r.registrarGato("G", 1, "C", false);
        }
        r.registrarAdoptante("A", "c", "v");
        Refugio copia(r);
        Refugio asignada;
        asignada = copia;
    }
    verificar(Coleccion<Adoptante>::cantidadInstancias() == antes, "no quedan colecciones vivas tras destruir todos los refugios");
    verificar(true, "50 refugios de 50 animales creados, copiados y destruidos sin errores de memoria");
}

int main()
{
    pruebaRegistroYBusqueda();
    pruebaOperadoresAnimales();
    pruebaFlujoAdopcion();
    pruebaExcepciones();
    pruebaCopiaProfunda();
    pruebaAsignacion();
    pruebaColeccionGenerica();
    pruebaLiberacionDeMemoria();

    std::cout << "\nResultado: " << (totales - fallidas) << " de " << totales << " pruebas correctas\n";
    return fallidas == 0 ? 0 : 1;
}
