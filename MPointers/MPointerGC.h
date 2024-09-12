// MPointerGC.h
#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <list>
#include <mutex>

// Clase singleton para gestionar las instancias de MPointer
class MPointerGC {
public:
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    // Agregar MPointer a la lista
    void addPointer(void* ptr, int id) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.push_back({ptr, id});
        //std::cout << "Anadido puntero con ID: " << id << std::endl;
    }

    // Eliminar MPointer de la lista
    void removePointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.remove_if([ptr](const PointerInfo& info) { return info.ptr == ptr; });
    }

    // Generar nuevo ID
    int generateId() {
        return ++currentId;
    }

    // Ejecutar el recolector de basura
    void runGC() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            cleanup();
        }
    }

    // Parar el thread del GC
    void stopGC() {
        //std::cout << "Solicitando parada del hilo del recolector de basura..." << std::endl;
        running = false;
        // Asegúrate de que el hilo del GC termine correctamente
        if (gcThread.joinable()) {
            //std::cout << "Esperando a que el hilo del recolector de basura termine..." << std::endl;
            gcThread.join();
            //std::cout << "Hilo del recolector de basura detenido." << std::endl;
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
        //std::cout << "Ejecutando limpieza de recolector de basura" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        
        std::list<void*> toDelete;
        
        for (auto it = pointers.begin(); it != pointers.end(); ++it) {
            bool hasReferences = false;
            
            for (auto jt = pointers.begin(); jt != pointers.end(); ++jt) {
                if (jt->ptr == it->ptr && jt != it) {
                    hasReferences = true;
                    break;
                }
            }

            if (!hasReferences) {
                //std::cout << "Marcando puntero con ID: " << it->id << " para liberacion" << std::endl;
                toDelete.push_back(it->ptr);
            }
        }

        for (auto ptr : toDelete) {
            //std::cout << "Liberando puntero: " << ptr << std::endl;
            delete static_cast<int*>(ptr); // Ajusta el tipo según sea necesario
            pointers.remove_if([ptr](const PointerInfo& info) { return info.ptr == ptr; });
        }
    }

    struct PointerInfo {
        void* ptr;
        int id;
    };

    std::list<PointerInfo> pointers;
    int currentId;
    std::atomic<bool> running;
    int interval;
    std::thread gcThread;
    std::mutex mtx;

    // Eliminar constructor de copia y operador de asignación
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif // MPOINTERGC_H