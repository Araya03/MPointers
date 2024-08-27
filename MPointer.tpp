#include "MPointer.h"
#include <iostream>

template <typename T>
MPointer<T>::MPointer() : ptr(new T()), id(-1), refCount(new RefCount()) {
    refCount->addRef(); //Incrementa el contador al crear un nuevo MPointer
    // Registro el MPointer en MPointerGC después de inicializarlo completamente
    id = MPointerGC<T>::getInstance().registerPointer(this);
    std::cout << "MPointer creado. Valor: " << *ptr << ", Contador de Referencias: " << refCount->getCount() << std::endl;
}

template <typename T>
MPointer<T>::MPointer(const MPointer& other) : ptr(other.ptr), refCount(other.refCount) {
    refCount->addRef(); //Incrementa el contador de referencias en la copia
    std::cout << "MPointer copiado. Valor: " << *ptr << ", Contador de Referencias: " << refCount->getCount() << std::endl;
}

template <typename T>
MPointer<T>::~MPointer() {
    if (ptr && refCount->release()) {
        delete ptr; //Libera el objeto si el contador llega a cero
        delete refCount; //Libera el contador de referencias

        // Notifica al recolector de basura que este puntero ha sido destruido
        MPointerGC<T>::getInstance().unregisterPointer(id);
        std::cout << "MPointer destruido. Valor: " << *ptr << ", Contador de Referencias: " << refCount->getCount() << std::endl;
    }
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    return mp;
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T MPointer<T>::operator&() {
    return *ptr;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        // Si ptr no es nullptr y refCount puede liberar el objeto, lo hacemos
        if (ptr && refCount->release()) {
            delete ptr; // Libera el objeto si el contador llega a cero
            delete refCount; // Libera el contador de referencias
            MPointerGC<T>::getInstance().unregisterPointer(id); // Desregistra el puntero en el GC
        }

        // Asignar el nuevo puntero y actualizar el ID
        ptr = other.ptr;
        refCount = other.refCount;
        id = other.id;

        // Incrementar el contador de referencias del puntero copiado
        refCount->addRef();

        // Registrar el nuevo puntero en el recolector de basura
        MPointerGC<T>::getInstance().registerPointer(this); // O actualizar el ID si es necesario
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    if (ptr) {
        *ptr = value; // Asigna el valor al objeto apuntado
    } else {
        ptr = new T(value); // Crea un nuevo objeto si ptr es nullptr
        refCount = new RefCount(); // Inicializa el contador de referencias
        refCount->addRef(); // Incrementa el contador de referencias
    }
    return *this;
}

template <typename T>
int MPointer<T>::getRefCount() const {
    return refCount->getCount();
}

template <typename T>
void MPointer<T>::printInfo() const {
    std::cout << "Valor: " << *ptr << ", Contador de Referencias: " << getRefCount() << std::endl;
}