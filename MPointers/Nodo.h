#ifndef NODO_H
#define NODO_H

#include "MPointer.h"

template <typename T>
class Nodo {
public:
    T data;
    MPointer<Nodo<T>> siguiente;
    MPointer<Nodo<T>> anterior;

    // Constructor por defecto
    Nodo() : data(T()), siguiente(nullptr), anterior(nullptr) {}

    // Constructor con valor
    Nodo(T valor) : data(valor), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODO_H