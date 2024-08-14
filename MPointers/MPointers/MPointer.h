#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"
#include "RefCount.h" // Incluye el archivo de encabezado de RefCount

template <typename T>
class MPointer {
private:
    T* ptr; //Puntero encapsulado
    int id; //ID proporcionado por MPointerGC
    RefCount* refCount; //Contador de referencias personalizado

    MPointer(); //Constructor privado

public:
    //Constructor de copia
    MPointer(const MPointer& other);

    //Destructor
    ~MPointer();

    //Método estático para crear un nuevo MPointer
    static MPointer<T> New();

    //Sobrecarga de operadores
    T& operator*();
    T operator&();
    MPointer<T>& operator=(const MPointer<T>& other);
    MPointer<T>& operator=(T value);

    //Obtener el conteo de referencias
    int getRefCount() const;

    //Imprimir información del puntero
    void printInfo() const;
};

#include "MPointer.tpp" //Incluye la implementación template

#endif //MPOINTER_H