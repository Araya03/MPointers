#include "MPointer.h"
#include <iostream>

template <typename T>
MPointer<T>::MPointer() : ptr(new T()), id(-1), refCount(new RefCount()) {
    refCount->addRef(); //Incrementa el contador al crear un nuevo MPointer
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
    }
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    //Aquí se puede registrar el MPointer en MPointerGC y asignar un ID
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
        if (ptr && refCount->release()) {
            delete ptr; //Libera el objeto si el contador llega a cero
            delete refCount; //Libera el contador de referencias
        }
        ptr = other.ptr;
        refCount = other.refCount;
        refCount->addRef(); //Incrementa el contador de referencias en la asignación
        std::cout << "MPointer asignado. Valor: " << *ptr << ", Contador de Referencias: " << refCount->getCount() << std::endl;
    }
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(T value) {
    *ptr = value;
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