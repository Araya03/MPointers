#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"
#include <iostream>

template <typename T>
class RefCount {
public:
    int count;
    T* ptr;

    RefCount(T* p) : count(1), ptr(p) {}
    ~RefCount() {
        delete ptr;
    }
};

template <typename T>
class MPointer {
private:
    RefCount<T>* refCount;
    int id;

public:
    //Constructor
    MPointer(T* p = nullptr) : refCount(new RefCount<T>(p)) {
        id = MPointerGC::getInstance().generateId();
        MPointerGC::getInstance().addPointer(refCount->ptr, id);
    }

    //Destructor
    ~MPointer() {
        release();
    }

    //Constructor de copia
    MPointer(const MPointer& other) : refCount(other.refCount), id(other.id) {
        ++refCount->count;
    }

    //Operador de asignación de copia
    MPointer& operator=(const MPointer& other) {
        if (this != &other) {
            release();
            refCount = other.refCount;
            id = other.id;
            ++refCount->count;
        }
        return *this;
    }

    //Operador de acceso al puntero
    T* operator->() const {
        return refCount->ptr;
    }

    //Operador de desreferenciación
    T& operator*() const {
        return *refCount->ptr;
    }

    //Operador de asignación para el tipo T
    MPointer& operator=(const T& value) {
        if (refCount->ptr) {
            *refCount->ptr = value;
        }
        return *this;
    }

    //Operador de asignación para el tipo T*
    MPointer& operator=(T* p) {
        if (refCount->ptr != p) {
            release();
            refCount = new RefCount<T>(p);
            id = MPointerGC::getInstance().generateId(); //Nuevo ID en caso de reasignación
            MPointerGC::getInstance().addPointer(refCount->ptr, id);
        }
        return *this;
    }

    //Verificar si el puntero es nulo
    bool isNull() const {
        return refCount->ptr == nullptr;
    }

    //Getter del puntero
    T* get() const {
        return refCount->ptr;
    }

    //Setter del puntero
    void set(T* p) {
        release();
        refCount = new RefCount<T>(p);
        id = MPointerGC::getInstance().generateId(); //Nuevo ID en caso de reasignación
        MPointerGC::getInstance().addPointer(refCount->ptr, id);
    }

    //Método estático para crear un nuevo MPointer con argumentos
    template<typename... Args>
    static MPointer New(Args&&... args) {
        return MPointer(new T(std::forward<Args>(args)...));
    }

    //Operadores de comparación
    bool operator==(const MPointer& other) const {
        return refCount->ptr == other.refCount->ptr;
    }

    bool operator!=(const MPointer& other) const {
        return refCount->ptr != other.refCount->ptr;
    }

private:
    void release() {
        if (--refCount->count == 0) {
            MPointerGC::getInstance().removePointer(refCount->ptr);
            delete refCount;
        }
    }
};

#endif //MPOINTER_H