#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include "ListaEnlazada.h"

//Clase singleton para gestionar las instancias de MPointer
class MPointerGC {
public:
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    //Agregar MPointer a la lista
    void addPointer(void* ptr, int id) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.append({ptr, id});
    }

    //Eliminar MPointer de la lista
    void removePointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.remove(PointerInfo(ptr, 0));
    }

    //Generar nuevo ID
    int generateId() {
        return ++currentId;
    }

    //Ejecutar el recolector de basura
    void runGC() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            cleanup();
        }
    }

    //Parar el thread del GC
    void stopGC() {
        running = false;
        if (gcThread.joinable()) {
            gcThread.join();
        }
    }

private:
    MPointerGC() : currentId(0), running(true), interval(3) {
        gcThread = std::thread(&MPointerGC::runGC, this);
    }

    ~MPointerGC() {
        stopGC();
    }

    void cleanup() {
        std::lock_guard<std::mutex> lock(mtx);

        LinkedList<void*> toDelete;

        // Buscar punteros sin referencias
        Node<PointerInfo>* it = pointers.begin();
        while (it) {
            bool hasReferences = false;
            Node<PointerInfo>* jt = pointers.begin();
            while (jt) {
                if (jt->data.ptr == it->data.ptr && jt != it) {
                    hasReferences = true;
                    break;
                }
                jt = jt->next;
            }

            if (!hasReferences) {
                toDelete.append(it->data.ptr);
            }

            it = it->next;
        }

        //Liberar los punteros no referenciados
        Node<void*>* deleteNode = toDelete.begin();
        while (deleteNode) {
            delete static_cast<int*>(deleteNode->data);
            deleteNode = deleteNode->next;
        }

        //Eliminar los punteros de la lista
        for (auto ptr : toDelete) {
            pointers.remove(PointerInfo(deleteNode->data, 0));
        }
    }

    struct PointerInfo {
        void* ptr;
        int id;
        
        PointerInfo(void* p, int i) : ptr(p), id(i) {}

        bool operator==(const PointerInfo& other) const {
            return ptr == other.ptr;
        }
    };

    LinkedList<PointerInfo> pointers;
    int currentId;
    std::atomic<bool> running;
    int interval;
    std::thread gcThread;
    std::mutex mtx;

    //Eliminar constructor de copia y operador de asignación
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif //MPOINTERGC_H