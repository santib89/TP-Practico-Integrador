# Sistema de Gestión de un Refugio de Animales

Trabajo Práctico Integrador de Programación Orientada a Objetos 2026, hecho en C++.

Integrantes: Santiago Becerra y Juan Leon Flesca.

## De qué trata

Es un programa de consola que maneja un refugio de animales. Se pueden registrar perros y gatos, registrar adoptantes y hacer el proceso de adopción mediante solicitudes, que pueden estar pendientes, confirmadas o canceladas. Los datos quedan en memoria mientras el programa está abierto; no se guardan en ningún archivo.

## Por qué conviene usar objetos

El problema ya viene pensado en entidades: animales, adoptantes, solicitudes y el refugio que los administra. Cada una tiene sus datos y las cosas que puede hacer, así que lo más natural fue hacer una clase por cada una.

Perro y Gato son animales que comparten datos (ID, nombre, edad, salud, si fue adoptado) y agregan cosas propias, por eso usamos herencia. Gracias al polimorfismo el refugio puede listar todos los animales sin fijarse si cada uno es perro o gato. Y con el encapsulamiento los datos solo se cambian a través de métodos, por ejemplo para que un animal ya adoptado no pueda volver a pedirse.

## Archivos

```
include/              los .h
  Animal.h            clase abstracta base
  Perro.h, Gato.h     clases hijas de Animal
  Adoptante.h
  SolicitudAdopcion.h tiene también el enum EstadoSolicitud
  Refugio.h           la clase principal
  Coleccion.h         clase genérica (template)
  Excepciones.h       las excepciones propias
src/                  los .cpp y main.cpp (el menú)
pruebas/pruebas.cpp   pruebas automáticas
diagramas/            pseudocódigo y diagramas de flujo
Makefile
```

## Cómo compilar y ejecutar

Hace falta `g++` (o `clang++`) con C++17 y `make`.

```bash
make          # compila y crea el ejecutable "refugio"
./refugio     # lo ejecuta (también sirve make run)
make clean    # borra lo generado
```

Sin `make`: `g++ -std=c++17 -Iinclude src/*.cpp -o refugio`

### Menú

```
1. Registrar un perro                7. Crear una solicitud de adopción
2. Registrar un gato                 8. Confirmar una solicitud
3. Listar todos los animales         9. Cancelar una solicitud
4. Listar los animales disponibles   10. Devolver un animal al estado disponible
5. Registrar un adoptante            11. Ver solicitudes e historial de adopciones
6. Buscar un animal por ID           0. Salir
```

Una sesión típica: registrar un animal (1 o 2), registrar un adoptante (5), crear la solicitud con los IDs de los dos (7) y confirmarla (8) o cancelarla (9). Al confirmarla el animal queda como adoptado, y con la opción 10 vuelve a estar disponible. Los IDs se asignan solos, empezando en 1, y el programa avisa cuál le tocó a cada uno. Si se ingresa un dato inválido el programa lo vuelve a pedir, y si hay un error (por ejemplo un ID que no existe) muestra el mensaje y sigue en el menú.

## Cómo está armado

### Las clases

- **Animal**: es abstracta, así que no se pueden crear objetos de esta clase. Guarda ID, nombre, edad, salud y estado de adopción. Tiene `mostrarInfo()` y `clonar()` como funciones virtuales puras, y destructor virtual.
- **Perro y Gato**: heredan de Animal. Perro agrega raza y tamaño; Gato agrega color y si es de interior (un solo `bool`, porque interior y exterior se excluyen). Los dos implementan `mostrarInfo()` y `clonar()`.
- **Adoptante**: ID, nombre, contacto y tipo de vivienda.
- **SolicitudAdopcion**: une un adoptante con un animal usando sus IDs y guarda el estado (Pendiente, Confirmada o Cancelada).
- **Refugio**: es la clase central. El menú de `main.cpp` solo pide datos y le pasa el trabajo a un método de Refugio. Contiene los animales, los adoptantes y las solicitudes, y los libera cuando se destruye.
- **Coleccion\<T\>**: un arreglo dinámico genérico con `agregar()`, `cantidad()` y `[]`. Refugio la usa con dos tipos: `Coleccion<Adoptante>` y `Coleccion<SolicitudAdopcion>`.

### Decisiones que tomamos

- Los animales están todos en un mismo arreglo de punteros `Animal**`. Así se pueden listar llamando a `mostrarInfo()` sin saber qué tipo es cada uno.
- La solicitud guarda los IDs y no punteros. Así, si se copia un refugio, las solicitudes no quedan apuntando al refugio original.
- Cada tipo (animal, adoptante, solicitud) tiene su propio contador de IDs.
- Los errores se manejan con excepciones, no con códigos de retorno. Refugio las lanza y el menú las atrapa.

### Operadores sobrecargados

- `==` en Animal: dos animales son iguales si tienen el mismo ID.
- `!` en Animal: `!animal` da verdadero si el animal ya no está disponible (fue adoptado).
- `[]` en Refugio: devuelve el animal que está en una posición.
- `()` en Refugio: busca un animal por ID y devuelve `nullptr` si no existe.
- `=` en Refugio, Adoptante, SolicitudAdopcion y Coleccion.

### Miembro estático en la clase genérica

`Coleccion<T>` tiene un `static int instanciasVivas` que cuenta cuántas colecciones existen. Cada tipo con el que se usa el template (`Coleccion<int>`, `Coleccion<Adoptante>`, etc.) es una clase distinta y tiene su propio contador. Por eso crear una `Coleccion<int>` no cambia el contador de una `Coleccion<std::string>`. El constructor lo suma, el destructor lo resta, y vuelve a 0 cuando se destruyen todas.

### Excepciones

Todas heredan de `ErrorRefugio`, que hereda de `std::exception`.

- `IdRepetidoException`: se agrega un animal con un ID que ya existe.
- `IndiceInvalidoException`: se usa `[]` con una posición fuera de rango (en Refugio y en Coleccion).
- `AnimalNoDisponibleException`: se pide un animal que ya fue adoptado.
- `NoEncontradoException`: no existe el adoptante, el animal o la solicitud.
- `OperacionInvalidaException`: se confirma o cancela una solicitud que no estaba pendiente, o se devuelve un animal que no estaba adoptado.

En el menú se atrapan con varios `catch` por referencia constante, de la más específica a la más general, y el último es `const std::exception&`.

### Función genérica

`leerValor<T>()`, en `main.cpp`, lee un número por consola, comprueba que no sea menor que un mínimo y lo pide de nuevo hasta que sea válido. La usamos con `int` (edades, IDs, opciones) y con `double` (el tamaño del perro).

## Memoria dinámica: quién crea y quién libera

- Cada Perro o Gato se crea con `new` en `registrarPerro` o `registrarGato`, y lo libera el destructor de Refugio. Como el destructor de Animal es virtual, se destruye el tipo correcto.
- El arreglo `Animal**` lo crea el constructor de Refugio. Cuando se llena, `agrandarArreglo()` reserva uno más grande y libera el viejo. Lo libera el destructor de Refugio.
- El arreglo interno de `Coleccion<T>` lo crea su constructor, crece cuando hace falta y lo libera su destructor.
- Los animales duplicados al copiar un refugio los crea el constructor de copia (o `operator=`) con `clonar()`, y los libera el destructor de esa copia.

Refugio es el único dueño de los animales. `agregarAnimal` se queda con el puntero solo si no falla; si lanza `IdRepetidoException`, el animal sigue siendo de quien lo pasó. Por eso `registrarPerro` y `registrarGato` borran el animal que crearon si `agregarAnimal` falla.

### Regla de los Tres

Refugio y Coleccion reservan memoria dinámica, así que definen constructor de copia, `operator=` y destructor, con copia profunda. Si se usara la copia por defecto, dos refugios compartirían los mismos animales y se borrarían dos veces.

Para copiar los animales usamos `clonar()`: cada clase devuelve una copia de sí misma (un Perro devuelve un Perro y un Gato devuelve un Gato). Así no hace falta saber el tipo al copiar. `operator=` reserva primero la copia y después libera lo anterior, y controla que no se asigne un objeto a sí mismo.

Animal, Perro, Gato, Adoptante y SolicitudAdopcion solo tienen números, `bool` y `std::string`, así que la copia por defecto alcanza. Igual definimos el constructor de copia, y `operator=` en Adoptante y SolicitudAdopcion.

### Aritmética de punteros

`Refugio::buscarAnimal()` recorre el arreglo de animales con `*(animales + i)`.

## Pruebas

```bash
make pruebas            # corre las pruebas automáticas
make pruebas-asan       # lo mismo, con AddressSanitizer (detecta errores de memoria)
make pruebas-memoria    # solo en macOS, usa "leaks" para buscar memoria sin liberar
```

`pruebas/pruebas.cpp` hace 35 verificaciones y al final dice cuántas salieron bien.

Casos válidos que se prueban:

- Registrar perros y gatos con IDs consecutivos, buscarlos por ID y por posición, y comprobar que cada uno es del tipo correcto.
- Los operadores `==` (mismo ID aunque sean de distinto tipo) y `!`.
- El flujo de adopción completo: crear, confirmar, devolver, y cancelar sin que el animal cambie.
- `Coleccion<int>` y `Coleccion<std::string>`: que crezcan más allá de la capacidad inicial y que tengan contadores estáticos separados.

Casos de error que se prueban:

- ID de animal repetido (el refugio queda igual).
- Índice fuera de rango o negativo, en Refugio y en Coleccion.
- Pedir un animal ya adoptado.
- Adoptante, animal o solicitud que no existe.
- Confirmar una solicitud ya confirmada, o devolver un animal que no estaba adoptado.

Copia profunda y memoria:

- Al copiar un refugio, los animales están en direcciones de memoria distintas. Adoptar uno en el original no cambia la copia, y agregar animales a uno no afecta al otro.
- Con `b = a`, `b` queda con los mismos animales que `a`, y `a = a` no rompe nada.
- Se crean, copian y destruyen 50 refugios de 100 animales cada uno. Los contadores estáticos vuelven a 0 y no hay errores de memoria.

### Pruebas a mano con el menú

- Opción `99`: muestra "Digito Invalido" y vuelve al menú.
- Una edad negativa o texto en vez de un número: dice "Valor invalido." y la vuelve a pedir.
- Crear una solicitud con un adoptante que no existe: muestra el error y sigue.
- Crear una solicitud con un animal ya adoptado: dice que no está disponible.
- Confirmar una solicitud que ya estaba confirmada: dice que no está pendiente.
- Devolver un animal que estaba disponible: dice que no estaba adoptado.
- Listar animales sin haber registrado ninguno: dice que no hay animales.

## Diagramas de flujo

En la carpeta `diagramas/` están el pseudocódigo hecho en PSeInt (`.psc`) y su diagrama de flujo (`.png`):

- `menu_principal`: el menú, que se repite hasta elegir Salir. Cada opción muestra los pasos generales de lo que hace (pedir los datos, buscar, verificar, crear o mostrar el resultado).
- `proceso_adopcion`: el proceso de adopción en detalle. Se fija si existen el adoptante y el animal y si el animal está disponible; después crea la solicitud y se confirma o se cancela.

El diagrama del menú es muy ancho porque tiene las 11 opciones; conviene abrir `menuprincipal.png` y acercar para verlo con detalle.
