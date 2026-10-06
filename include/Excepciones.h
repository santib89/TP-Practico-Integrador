#pragma once
#include <exception>
#include <string>

class ErrorRefugio : public std::exception
{
private:
    std::string mensaje;

public:
    explicit ErrorRefugio(const std::string& unMensaje) : mensaje(unMensaje) {}
    virtual ~ErrorRefugio() noexcept {}
    const char* what() const noexcept override { return mensaje.c_str(); }
};

class IdRepetidoException : public ErrorRefugio
{
public:
    explicit IdRepetidoException(int id)
        : ErrorRefugio("Ya existe un animal con el ID " + std::to_string(id)) {}
};

class IndiceInvalidoException : public ErrorRefugio
{
public:
    IndiceInvalidoException(int indice, int cantidad)
        : ErrorRefugio("Indice " + std::to_string(indice) + " fuera de rango (hay " +
                       std::to_string(cantidad) + " elementos)") {}
};

class AnimalNoDisponibleException : public ErrorRefugio
{
public:
    explicit AnimalNoDisponibleException(int id)
        : ErrorRefugio("El animal con ID " + std::to_string(id) + " no esta disponible") {}
};

class NoEncontradoException : public ErrorRefugio
{
public:
    NoEncontradoException(const std::string& que, int id)
        : ErrorRefugio("No existe " + que + " con ID " + std::to_string(id)) {}
};

class OperacionInvalidaException : public ErrorRefugio
{
public:
    explicit OperacionInvalidaException(const std::string& motivo)
        : ErrorRefugio(motivo) {}
};
