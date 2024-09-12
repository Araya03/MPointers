// inicial.cpp
/*#include "MPointer.h"
#include "MPointerGC.h"
#include <iostream>
#include <thread>
#include <chrono>

void testMPointerGC() {
    // Espera unos segundos para permitir que el recolector de basura realice la limpieza
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main() {
    // Inicializar MPointerGC (automáticamente se inicializa por ser un singleton)
    // El recolector de basura se ejecutará en segundo plano

    // Crear MPointers
    MPointer<int> ptr1 = MPointer<int>::New();
    MPointer<int> ptr2 = MPointer<int>::New();

    // Asignar valores
    *ptr1 = 10;
    *ptr2 = 20;

    // Imprimir valores
    std::cout << "Valor en ptr1: " << *ptr1 << std::endl;
    std::cout << "Valor en ptr2: " << *ptr2 << std::endl;

    // Asignar ptr1 a ptr2 y verificar
    ptr2 = ptr1;
    std::cout << "Valor en ptr1 despues de asignacion a ptr2: " << *ptr1 << std::endl;
    std::cout << "Valor en ptr2 despues de asignacion de ptr1: " << *ptr2 << std::endl;

    // Asignar un nuevo valor a ptr1
    *ptr1 = 30;
    std::cout << "Valor en ptr1 despues de cambio: " << *ptr1 << std::endl;
    std::cout << "Valor en ptr2 despues de cambio en ptr1: " << *ptr2 << std::endl;

    // Eliminar referencias
    ptr1 = MPointer<int>::New();
    std::cout << "Valor en ptr1 despues de reinicializacion: " << *ptr1 << std::endl;

    // Esperar para permitir la ejecución del recolector de basura
    testMPointerGC();

    // Asegúrate de detener el recolector de basura
    MPointerGC::getInstance().stopGC();

    return 0;
}*/

#include "ListaDobleEnlazada.h"

int main() {
    ListaDobleEnlazada<int> lista;

    // Insertar valores
    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);

    // Imprimir la lista hacia adelante
    std::cout << "Lista hacia adelante: ";
    lista.imprimirAdelante();

    // Imprimir la lista hacia atrás
    std::cout << "Lista hacia atras: ";
    lista.imprimirAtras();

    // Eliminar un valor
    lista.eliminar(20);

    // Imprimir la lista después de la eliminación
    std::cout << "Lista despues de eliminar 20: ";
    lista.imprimirAdelante();

    // Asegúrate de detener el recolector de basura
    MPointerGC::getInstance().stopGC();

    return 0;
}