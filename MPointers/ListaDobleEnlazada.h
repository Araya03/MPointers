#ifndef LISTADOBLEENLAZADA_H
#define LISTADOBLEENLAZADA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaDobleEnlazada {
private:
    MPointer<Nodo<T>> cabeza;
    MPointer<Nodo<T>> cola;

public:
    ListaDobleEnlazada() : cabeza(nullptr), cola(nullptr) {}

    // Insertar al final de la lista
    void insertar(T valor) {
        MPointer<Nodo<T>> nuevoNodo = MPointer<Nodo<T>>::New(valor);

        if (cabeza.isNull()) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    // Imprimir la lista hacia adelante
    void imprimirAdelante() const {
        MPointer<Nodo<T>> actual = cabeza;
        while (!actual.isNull()) {
            std::cout << actual->data << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    // Imprimir la lista hacia atrás
    void imprimirAtras() const {
        MPointer<Nodo<T>> actual = cola;
        while (!actual.isNull()) {
            std::cout << actual->data << " ";
            actual = actual->anterior;
        }
        std::cout << std::endl;
    }

    // Eliminar un nodo de la lista
    void eliminar(T valor) {
        MPointer<Nodo<T>> actual = cabeza;
        while (!actual.isNull()) {
            if (actual->data == valor) {
                if (!actual->anterior.isNull()) {
                    actual->anterior->siguiente = actual->siguiente;
                } else {
                    cabeza = actual->siguiente;
                }

                if (!actual->siguiente.isNull()) {
                    actual->siguiente->anterior = actual->anterior;
                } else {
                    cola = actual->anterior;
                }
                return;
            }
            actual = actual->siguiente;
        }
    }

    // Obtener el primer nodo
    MPointer<Nodo<T>> obtenerCabeza() const {
        return cabeza;
    }

    // Obtener el último nodo
    MPointer<Nodo<T>> obtenerCola() const {
        return cola;
    }
};

#endif // LISTADOBLEENLAZADA_H