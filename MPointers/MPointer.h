#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"
#include "RefCount.h" // Incluye el archivo de encabezado de RefCount

template <typename T>
class MPointer {
private:
    T* ptr; // Puntero encapsulado
    int id; // ID proporcionado por MPointerGC
    RefCount* refCount; // Contador de referencias personalizado

    MPointer(); // Constructor privado

public:
    // Constructor de copia
    MPointer(const MPointer& other);

    // Destructor
    ~MPointer();

    // Método estático para crear un nuevo MPointer
    static MPointer<T> New();

    // Sobrecarga del operador de asignación para otro MPointer
    MPointer<T>& operator=(const MPointer<T>& other);

    // Sobrecarga del operador de asignación para un valor de tipo T
    MPointer<T>& operator=(const T& value);

    // Sobrecarga del operador de desreferenciación
    T& operator*();
    T operator&();

    // Obtener el conteo de referencias
    int getRefCount() const;

    // Imprimir información del puntero
    void printInfo() const;
};

#include "MPointer.tpp" // Incluye la implementación template

#endif // MPOINTER_H