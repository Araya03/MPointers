#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>

//Declaración adelantada de MPointer para evitar dependencias circulares
template <typename T>
class MPointer;

/**
 * @brief Clase singleton que gestiona la recolección de basura para MPointer.
 * 
 * MPointerGC se encarga de registrar, monitorear y liberar los objetos MPointer 
 * cuando ya no son necesarios (cuando su contador de referencias llega a cero).
 */

template <typename T>
class MPointerGC {
private:
    std::unordered_map<int, MPointer<T>*> pointers; //Mapa de punteros conocidos con su ID
    std::atomic<int> nextId; //ID autogenerado para cada MPointer
    std::mutex gcMutex; //Mutex para sincronizar el acceso a los punteros
    std::thread gcThread; //Hilo que ejecuta el ciclo de recolección de basura
    bool running; //Indicador para el ciclo de recolección de basura

    MPointerGC(); //Constructor privado para implementar el patrón singleton
    void runGC(); //Método que ejecuta el ciclo de recolección de basura en el hilo

public:
    ~MPointerGC(); //Destructor que detiene el hilo de recolección y libera memoria
    static MPointerGC& getInstance(); //Método estático para obtener la única instancia de MPointerGC

    int registerPointer(MPointer<T>* ptr); //Registra un nuevo MPointer y le asigna un ID
    void unregisterPointer(int id); //Desregistra un MPointer cuando ya no es necesario

    //Prohibir la copia y asignación de la instancia singleton
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#include "MPointerGC.tpp" //Incluye la implementación del template

#endif