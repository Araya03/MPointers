#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "MPointer.h"
#include "Nodo.h"
#include "ListaDobleEnlazada.h"
#include <iostream>
#include "Swap.h"

//Función de partición para QuickSort
template <typename T>
MPointer<Nodo<T>> partition(MPointer<Nodo<T>> low, MPointer<Nodo<T>> high) {
    T pivot = high->data;
    MPointer<Nodo<T>> i = low->anterior;

    for (MPointer<Nodo<T>> j = low; j != high; j = j->siguiente) {
        if (j->data < pivot) {
            i = (i.isNull()) ? low : i->siguiente;
            swap(i->data, j->data);
        }
    }
    i = (i.isNull()) ? low : i->siguiente;
    swap(i->data, high->data);
    return i;
}

//Función QuickSort
template <typename T>
void QuickSort(MPointer<Nodo<T>> low, MPointer<Nodo<T>> high) {
    if (!low.isNull() && !high.isNull() && low != high && low != high->siguiente) {
        MPointer<Nodo<T>> p = partition(low, high);
        QuickSort(low, p->anterior);
        QuickSort(p->siguiente, high);
    }
}

//Función para obtener el último nodo
template <typename T>
MPointer<Nodo<T>> getLastNode(MPointer<Nodo<T>> head) {
    MPointer<Nodo<T>> temp = head;
    while (!temp->siguiente.isNull()) {
        temp = temp->siguiente;
    }
    return temp;
}

//Función para ordenar la lista con QuickSort
template <typename T>
void quickSort(ListaDobleEnlazada<T>& lista) {
    MPointer<Nodo<T>> last = getLastNode(lista.obtenerCabeza());
    QuickSort(lista.obtenerCabeza(), last);
}

#endif //QUICKSORT_H