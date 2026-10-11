#pragma once
#include "Excepciones.h"

template <typename T>
class Coleccion
{
private:
    T* elementos;
    int cantidadElementos;
    int capacidad;

    static int instanciasVivas;

    void agrandar()
    {
        int nuevaCapacidad = capacidad * 2;
        T* nuevo = new T[nuevaCapacidad];
        for (int i = 0; i < cantidadElementos; i++)
        {
            nuevo[i] = elementos[i];
        }
        delete[] elementos;
        elementos = nuevo;
        capacidad = nuevaCapacidad;
    }

public:
    Coleccion() : elementos(new T[4]), cantidadElementos(0), capacidad(4)
    {
        instanciasVivas++;
    }

    Coleccion(const Coleccion& otro)
        : elementos(new T[otro.capacidad]),
          cantidadElementos(otro.cantidadElementos),
          capacidad(otro.capacidad)
    {
        for (int i = 0; i < cantidadElementos; i++)
        {
            elementos[i] = otro.elementos[i];
        }
        instanciasVivas++;
    }

    Coleccion& operator=(const Coleccion& otro)
    {
        if (this != &otro)
        {
            T* nuevo = new T[otro.capacidad];
            for (int i = 0; i < otro.cantidadElementos; i++)
            {
                nuevo[i] = otro.elementos[i];
            }
            delete[] elementos;
            elementos = nuevo;
            cantidadElementos = otro.cantidadElementos;
            capacidad = otro.capacidad;
        }
        return *this;
    }

    ~Coleccion()
    {
        delete[] elementos;
        instanciasVivas--;
    }

    void agregar(const T& elemento)
    {
        if (cantidadElementos == capacidad)
        {
            agrandar();
        }
        elementos[cantidadElementos] = elemento;
        cantidadElementos++;
    }

    int cantidad() const
    {
        return cantidadElementos;
    }

    T& operator[](int indice)
    {
        if (indice < 0 || indice >= cantidadElementos)
        {
            throw IndiceInvalidoException(indice, cantidadElementos);
        }
        return elementos[indice];
    }

    const T& operator[](int indice) const
    {
        if (indice < 0 || indice >= cantidadElementos)
        {
            throw IndiceInvalidoException(indice, cantidadElementos);
        }
        return elementos[indice];
    }

    static int cantidadInstancias()
    {
        return instanciasVivas;
    }
};

template <typename T>
int Coleccion<T>::instanciasVivas = 0;
