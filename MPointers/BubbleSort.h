#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "MPointer.h"
#include "Nodo.h"
#include "ListaDobleEnlazada.h"

#include <iostream>
#include <utility> // Para std::swap

// Implementación del BubbleSort
template <typename T>
void bubbleSort(ListaDobleEnlazada<T>& lista) {
    if (lista.obtenerCabeza().isNull()) {
        return; // Lista vacía
    }

    bool swapped;
    do {
        swapped = false;
        MPointer<Nodo<T>> current = lista.obtenerCabeza();
        while (!current->siguiente.isNull()) {
            MPointer<Nodo<T>> next = current->siguiente;
            if (current->data > next->data) {
                std::swap(current->data, next->data);
                swapped = true;
            }
            current = next;
        }
    } while (swapped);
}

// Función para ordenar la lista con BubbleSort
template <typename T>
void ordenarListaBubbleSort(ListaDobleEnlazada<T>& lista) {
    bubbleSort(lista);
}

#endif // BUBBLESORT_H