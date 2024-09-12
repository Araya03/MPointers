#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "MPointer.h"
#include "Nodo.h"
#include "ListaDobleEnlazada.h"

#include <iostream>
#include <utility> // Para std::swap

// Implementación del InsertionSort
template <typename T>
void insertionSort(ListaDobleEnlazada<T>& lista) {
    if (lista.obtenerCabeza().isNull()) {
        return; // Lista vacía
    }

    MPointer<Nodo<T>> head = lista.obtenerCabeza();
    MPointer<Nodo<T>> sorted = nullptr;

    while (!head.isNull()) {
        MPointer<Nodo<T>> current = head;
        head = head->siguiente;

        if (sorted.isNull() || sorted->data >= current->data) {
            // Insertar al principio
            current->siguiente = sorted;
            current->anterior = nullptr;
            if (!sorted.isNull()) {
                sorted->anterior = current;
            }
            sorted = current;
        } else {
            // Encontrar la posición correcta
            MPointer<Nodo<T>> temp = sorted;
            while (!temp->siguiente.isNull() && temp->siguiente->data < current->data) {
                temp = temp->siguiente;
            }
            // Insertar en la posición correcta
            current->siguiente = temp->siguiente;
            if (!temp->siguiente.isNull()) {
                temp->siguiente->anterior = current;
            }
            temp->siguiente = current;
            current->anterior = temp;
        }
    }

    // Actualizar la cabeza de la lista
    lista = ListaDobleEnlazada<T>();
    MPointer<Nodo<T>> last = sorted;
    while (!sorted.isNull()) {
        lista.insertar(sorted->data);
        sorted = sorted->siguiente;
    }
}

#endif // INSERTIONSORT_H