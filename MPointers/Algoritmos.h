#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "Nodo.h"
#include "MPointer.h"

// Función para encontrar el nodo con el valor mínimo
template <typename T>
MPointer<Nodo<T>> findMinNode(MPointer<Nodo<T>> start) {
    MPointer<Nodo<T>> minNode = start;
    MPointer<Nodo<T>> current = start;

    while (!current.isNull()) {
        if (current->data < minNode->data) {
            minNode = current;
        }
        current = current->siguiente;
    }

    return minNode;
}

// Función de partición para QuickSort
template <typename T>
MPointer<Nodo<T>> partition(MPointer<Nodo<T>> low, MPointer<Nodo<T>> high) {
    T pivot = high->data;
    MPointer<Nodo<T>> i = low->anterior;

    for (MPointer<Nodo<T>> j = low; j != high; j = j->siguiente) {
        if (j->data < pivot) {
            i = (i.isNull()) ? low : i->siguiente;
            std::swap(i->data, j->data);
        }
    }
    i = (i.isNull()) ? low : i->siguiente;
    std::swap(i->data, high->data);
    return i;
}

// Función QuickSort
template <typename T>
void quickSort(MPointer<Nodo<T>> low, MPointer<Nodo<T>> high) {
    if (!low.isNull() && !high.isNull() && low != high && low != high->siguiente) {
        MPointer<Nodo<T>> p = partition(low, high);
        quickSort(low, p->anterior);
        quickSort(p->siguiente, high);
    }
}

// Función para obtener el último nodo
template <typename T>
MPointer<Nodo<T>> getLastNode(MPointer<Nodo<T>> head) {
    MPointer<Nodo<T>> temp = head;
    while (!temp->siguiente.isNull()) {
        temp = temp->siguiente;
    }
    return temp;
}

#endif // ALGORITMOS_H