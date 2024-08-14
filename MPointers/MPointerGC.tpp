#include "MPointerGC.h"
#include "MPointer.h"
#include <chrono>

/**
 * @brief Constructor privado de MPointerGC.
 * 
 * Inicializa el ID autogenerado y arranca el hilo que ejecuta la recolección de basura.
 */

template <typename T>
MPointerGC<T>::MPointerGC() : nextId(0), running(true) {
    gcThread = std::thread(&MPointerGC::runGC, this);
}

/**
 * @brief Destructor de MPointerGC.
 * 
 * Detiene el hilo de recolección de basura y libera todos los MPointer registrados.
 */

template <typename T>
MPointerGC<T>::~MPointerGC() {
    running = false;
    if (gcThread.joinable()) {
        gcThread.join(); //Espera a que el hilo termine
    }

    //Libera toda la memoria de los MPointer que aún estén registrados
    for (auto& entry : pointers) {
        delete entry.second;
    }
    pointers.clear();
}

/**
 * @brief Obtiene la única instancia de MPointerGC.
 * 
 * @return Referencia a la instancia singleton de MPointerGC.
 */

template <typename T>
MPointerGC<T>& MPointerGC<T>::getInstance() {
    static MPointerGC<T> instance;
    return instance;
}

/**
 * @brief Ciclo que se ejecuta en un hilo separado para la recolección de basura.
 * 
 * Revisa periódicamente todos los MPointer registrados y libera aquellos cuyo contador de referencias sea 0.
 */

template <typename T>
void MPointerGC<T>::runGC() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Pausa de n segundos

        std::lock_guard<std::mutex> lock(gcMutex);
        for (auto it = pointers.begin(); it != pointers.end(); ) {
            if (it->second->getRefCount() == 0) { //Si el contador de referencias es 0
                delete it->second; //Libera la memoria del MPointer
                it = pointers.erase(it); //Elimina la entrada del mapa
            } else {
                ++it; //Avanza al siguiente elemento
            }
        }
    }
}

/**
 * @brief Registra un nuevo MPointer en el GC y le asigna un ID.
 * 
 * @param ptr Puntero al objeto MPointer que se va a registrar.
 * @return ID autogenerado asignado al MPointer.
 */

template <typename T>
int MPointerGC<T>::registerPointer(MPointer<T>* ptr) {
    std::lock_guard<std::mutex> lock(gcMutex);
    int id = nextId++;
    pointers[id] = ptr;
    return id;
}

/**
 * @brief Desregistra un MPointer del GC, indicando que ya no es necesario.
 * 
 * @param id ID del MPointer que se va a desregistrar.
 */

template <typename T>
void MPointerGC<T>::unregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(gcMutex);
    pointers.erase(id);
}