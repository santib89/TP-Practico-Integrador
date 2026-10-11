# Sistema de Gestión de un Refugio de Animales

Trabajo Práctico Integrador - Programación Orientada a Objetos 2026 (C++).

## Integrantes

- Santiago Becerra
- Juan Leon Flesca

## Descripción

Programa de consola que administra un refugio ficticio: registra perros y gatos, registra adoptantes y gestiona el proceso de adopción mediante solicitudes que pueden estar pendientes, confirmadas o canceladas. Los datos viven en memoria mientras el programa está abierto (no se guardan en archivos).

## Por qué el problema se adapta al paradigma orientado a objetos

El programa se estructura como una colección de objetos que interactúan entre sí. Cada objeto tiene un estado (datos) y un comportamiento (métodos).

Las entidades del enunciado se corresponden directamente con clases: un animal tiene datos propios (ID, nombre, edad, salud, estado de adopción) y acciones propias (mostrar su información, marcarse como adoptado). Un perro y un gato son tipos de animal con atributos adicionales, lo que se expresa naturalmente con herencia y permite tratarlos de forma uniforme mediante polimorfismo. El refugio coordina a todos los demás objetos (animales, adoptantes, solicitudes), y el encapsulamiento evita que el resto del programa modifique datos sin pasar por las operaciones que garantizan que el sistema siga siendo consistente (por ejemplo, un animal adoptado no puede volver a ser solicitado).

## Estructura del proyecto

```
include/            Headers (.h)
  Animal.h          Clase abstracta base
  Perro.h, Gato.h   Clases derivadas
  Adoptante.h
  SolicitudAdopcion.h  Incluye el enum EstadoSolicitud
  Refugio.h         Clase central del sistema
  Coleccion.h       Clase genérica (template) con miembro estático
  Excepciones.h     Jerarquía de excepciones personalizadas
src/                Implementaciones (.cpp) y main.cpp (menú)
pruebas/pruebas.cpp Pruebas automáticas
Makefile
```

## Compilación y uso

Requiere un compilador con soporte de C++17 (`g++` o `clang++`) y `make`.

```bash
make            # compila y genera el ejecutable "refugio"
./refugio       # ejecuta el programa (también: make run)
make clean      # borra lo generado
```

Sin `make`:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o refugio
```

### Menú

```
1. Registrar un perro                 7. Crear una solicitud de adopción
2. Registrar un gato                  8. Confirmar una solicitud
3. Listar todos los animales          9. Cancelar una solicitud
4. Listar los animales disponibles   10. Devolver un animal al estado disponible
5. Registrar un adoptante            11. Ver solicitudes e historial de adopciones
6. Buscar un animal por ID            0. Salir
```

Flujo típico: registrar un animal (opción 1 o 2) y un adoptante (5); crear una solicitud con los IDs de ambos (7); confirmarla (8) o cancelarla (9). Una solicitud confirmada marca al animal como adoptado; la opción 10 lo devuelve a disponible. Los IDs de animales, adoptantes y solicitudes se asignan automáticamente desde 1 y se informan al crearlos. Todas las entradas se validan: ante un valor inválido el programa vuelve a pedirlo, y ante un error de operación muestra un mensaje y mantiene el menú activo.

## Diseño

### Clases

- **Animal** (abstracta): ID, nombre, edad, salud y estado de adopción. Declara `mostrarInfo()` y `clonar()` como funciones virtuales puras y tiene destructor virtual. No puede instanciarse.
- **Perro / Gato**: heredan públicamente de `Animal`. `Perro` agrega raza y tamaño; `Gato` agrega color de pelaje y si es de interior (un solo `bool`: interior o exterior son excluyentes). Implementan `mostrarInfo()` con `override` y `clonar()`.
- **Adoptante**: ID, nombre, contacto y tipo de vivienda.
- **SolicitudAdopcion**: relaciona un adoptante con un animal a través de sus IDs y guarda su estado (`Pendiente`, `Confirmada`, `Cancelada`).
- **Refugio**: administra todo el sistema. Es el equivalente al "main" de la lógica: el menú de `main.cpp` solo pide datos y delega cada operación en un método de `Refugio`. Relaciona `Animal`, `Adoptante` y `SolicitudAdopcion` por composición: es dueño de todos ellos y los destruye con él.
- **Coleccion\<T\>**: arreglo dinámico genérico con `agregar()`, `cantidad()` y acceso con `[]`. `Refugio` la usa con dos tipos: `Coleccion<Adoptante>` y `Coleccion<SolicitudAdopcion>`.

### Decisiones

- **Catálogo polimórfico**: los animales se guardan en un único arreglo de punteros `Animal**`. Se listan llamando a `mostrarInfo()` sin saber si cada elemento es un perro o un gato.
- **Relaciones por ID**: `SolicitudAdopcion` guarda los IDs, no punteros, de modo que copiar un `Refugio` no deja punteros apuntando al refugio original.
- **IDs automáticos**: cada tipo tiene su propio contador. `agregarAnimal()` actualiza el contador si recibe un ID más alto, de modo que no se generen IDs repetidos.
- **Errores con excepciones**: en lugar de códigos de retorno, `Refugio` lanza excepciones y el menú las captura.

### Sobrecarga de operadores

| Operador | Clase | Significado |
|---|---|---|
| `==` | `Animal` | Dos animales son iguales si tienen el mismo ID |
| `[]` | `Refugio` | Acceso a un animal por posición |
| `()` | `Refugio` | Búsqueda de un animal por ID (`nullptr` si no existe) |
| `!` | `Animal` | `!animal` es verdadero si el animal **no** está disponible |
| `=` | `Refugio`, `Adoptante`, `SolicitudAdopcion`, `Coleccion` | Asignación con copia profunda |

### Miembro estático en la clase genérica

`Coleccion<T>` tiene `static int instanciasVivas`, que cuenta cuántas colecciones de ese tipo existen. Cada instanciación del template (`Coleccion<int>`, `Coleccion<Adoptante>`, `Coleccion<SolicitudAdopcion>`, ...) es una clase distinta y tiene su propia copia del contador: crear una `Coleccion<int>` no modifica el contador de `Coleccion<std::string>`. El constructor y el de copia lo incrementan y el destructor lo decrementa, por lo que vuelve a 0 cuando se liberan todas.

### Excepciones

Todas heredan de `ErrorRefugio`, que a su vez hereda de `std::exception`:

| Excepción | Cuándo se lanza |
|---|---|
| `IdRepetidoException` | `agregarAnimal()` con un ID que ya existe |
| `IndiceInvalidoException` | `[]` con una posición fuera de rango (en `Refugio` y en `Coleccion`) |
| `AnimalNoDisponibleException` | Pedir o confirmar la adopción de un animal ya adoptado |
| `NoEncontradoException` | Adoptante, animal o solicitud inexistente |
| `OperacionInvalidaException` | Confirmar o cancelar una solicitud que no está pendiente; devolver un animal que no estaba adoptado |

En el menú se capturan con varios `catch` por referencia constante (de la más específica a la más general, terminando en `const std::exception&`), así el programa muestra el mensaje y vuelve al menú.

### Función genérica

`leerValor<T>()` (en `main.cpp`) lee un valor por consola, lo valida contra un mínimo y repite hasta que sea válido. Se usa con `int` (edades, IDs, opciones) y con `double` (tamaño de un perro).

## Memoria dinámica: quién crea y quién libera

| Bloque | Lo crea | Lo libera |
|---|---|---|
| Cada `Perro` / `Gato` (con `new`) | `Refugio::registrarPerro`, `registrarGato`, o quien llame a `agregarAnimal` | El destructor de `Refugio` (`delete animales[i]`); el destructor virtual de `Animal` hace que se destruya el tipo correcto |
| El arreglo `Animal**` | El constructor de `Refugio`; `agrandarArreglo()` reserva uno más grande al llenarse | El destructor de `Refugio` (`delete[]`); `agrandarArreglo()` libera el viejo |
| El arreglo interno de `Coleccion<T>` | El constructor de `Coleccion`; `agrandar()` | El destructor de `Coleccion` |
| Animales duplicados en una copia | `Refugio(const Refugio&)` y `operator=`, mediante `clonar()` | El destructor del refugio copia |

Reglas: `Refugio` es el único dueño de los animales. `agregarAnimal(Animal*)` toma posesión del puntero solo si no lanza una excepción; si lanza `IdRepetidoException`, el animal sigue siendo del que llamó. `registrarPerro` y `registrarGato` liberan el animal que acaban de crear si `agregarAnimal` falla.

### Regla de los Tres

- `Animal` (virtual), `Perro`, `Gato`, `Adoptante` y `SolicitudAdopcion` contienen solo valores (números, `bool`, `std::string`), por lo que la copia por defecto es correcta; igualmente se definen constructor de copia y, en `Adoptante` y `SolicitudAdopcion`, `operator=`.
- `Coleccion<T>` y `Refugio` reservan memoria dinámica y definen **constructor de copia, `operator=` y destructor** con copia profunda. En `Refugio`, cada animal se duplica con `clonar()`, que devuelve un `Perro` o un `Gato` según el tipo real. `operator=` reserva la copia antes de liberar lo anterior y protege contra la autoasignación (`a = a`).

### Recorrido con aritmética de punteros

`Refugio::buscarAnimal()` recorre el arreglo de animales con `*(animales + i)`.

## Pruebas

```bash
make pruebas            # ejecuta las pruebas automáticas
make pruebas-memoria    # además verifica fugas de memoria con "leaks" (macOS)
make pruebas-asan       # además usa AddressSanitizer (si el equipo lo soporta)
```

`pruebas/pruebas.cpp` ejecuta 50 verificaciones. Resultado actual: **50 de 50 correctas** y **0 fugas de memoria** (`leaks`).

### Casos válidos

- Registro de perro y gato con IDs consecutivos; búsqueda por ID (`()`) y por posición (`[]`); verificación del tipo real de cada animal (polimorfismo).
- Operadores `==` (mismo ID, aun siendo de distinto tipo) y `!` (animal disponible / adoptado).
- Flujo completo de adopción: crear, confirmar, devolver, y cancelar sin afectar al animal.
- `Coleccion<int>` y `Coleccion<std::string>`: crecimiento más allá de la capacidad inicial y contadores estáticos independientes.

### Casos de error

- ID de animal repetido → `IdRepetidoException` (y el refugio no cambia).
- Índice fuera de rango y negativo → `IndiceInvalidoException`, en `Refugio` y en `Coleccion`.
- Solicitar un animal ya adoptado → `AnimalNoDisponibleException`.
- Adoptante, animal o solicitud inexistente → `NoEncontradoException`.
- Confirmar una solicitud ya confirmada, o devolver un animal que no estaba adoptado → `OperacionInvalidaException`.
- Captura por clase base (`ErrorRefugio`) y por `const std::exception&`.

### Copia profunda y liberación de memoria

- Constructor de copia: la copia de un `Refugio` tiene los mismos animales pero en bloques de memoria distintos (direcciones distintas) y con su tipo real; adoptar un animal en el original **no** cambia la copia, y agregar animales a uno no afecta al otro.
- `operator=`: tras `b = a`, `b` queda con exactamente los animales de `a` (y libera los que tenía); cambios posteriores en `a` no afectan a `b`; la autoasignación no rompe el objeto.
- Liberación: se crean, copian, asignan y destruyen 50 refugios de 50 animales; los contadores estáticos de `Coleccion` vuelven a su valor inicial y `leaks` informa 0 fugas. Una doble liberación, que ocurriría si la copia fuera superficial, abortaría el programa.

### Casos de prueba manuales (menú)

| Entrada | Resultado esperado |
|---|---|
| Opción `99` | "Digito Invalido" y vuelve al menú |
| Edad `-5` o texto en lugar de número | "Valor invalido." y vuelve a pedirla |
| Opción 7 con adoptante inexistente | "Error: No existe un adoptante con ID ..." |
| Opción 7 con un animal ya adoptado | "Error: El animal con ID ... no esta disponible" |
| Opción 8 con una solicitud ya confirmada | "Error: La solicitud no esta pendiente" |
| Opción 10 con un animal disponible | "Error: El animal no estaba adoptado" |
| Opción 3 sin animales | "No hay animales registrados" |

## Diagramas de flujo

Los diagramas de flujo del menú principal y de cada opción del sistema se entregan por separado.
