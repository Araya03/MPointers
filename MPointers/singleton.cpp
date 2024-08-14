#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

class Singleton {
private:
    static Singleton* instancia; //Puntero estático a la instancia única del Singleton
    static std::mutex mutex; //Mutex estático para sincronizar el acceso a la instancia
    std::thread workerThread; //Hilo para ejecutar la tarea periódica
    std::atomic<bool> running; //Variable atómica para indicar si el hilo debe seguir ejecutándose
    int intervalo; //Intervalo en segundos para ejecutar la tarea periódica

    //Constructor privado para evitar la creación directa de instancias
    Singleton(int intervalo) : intervalo(intervalo), running(false) {
        std::cout << "Constructor Singleton" << std::endl; //Mensaje para indicar la creación del Singleton
    }

    //Método que se ejecuta en el hilo para realizar la tarea periódica
    void tareaPeriodica() {
        while (running) { //Mientras running sea true, el bucle sigue ejecutándose
            std::this_thread::sleep_for(std::chrono::seconds(intervalo)); //Espera durante el intervalo especificado
            ejecutarTarea(); //Ejecuta la tarea periódica
        }
    }

    //Método que define la tarea que se ejecutará periódicamente
    void ejecutarTarea() {
        std::cout << "Ejecutando tarea periodica" << std::endl; //Mensaje de ejemplo para indicar que la tarea se está ejecutando
    }

public:
    //Método estático para obtener la instancia única del Singleton
    static Singleton* obtenerInstancia(int intervalo) {
        if (instancia == nullptr) { //Si la instancia aún no ha sido creada
            std::lock_guard<std::mutex> lock(mutex); //Bloqueo el mutex para asegurar que solo un hilo cree la instancia
            if (instancia == nullptr) { //Verifico de nuevo en caso de que otra instancia haya sido creada en otro hilo
                instancia = new Singleton(intervalo); //Crea la instancia única del Singleton
                instancia->iniciarHilo(); //Inicia el hilo que ejecutará la tarea periódica
            }
        }
        return instancia; //Devuelve el puntero a la instancia única
    }

    //Inicia el hilo para ejecutar la tarea periódica
    void iniciarHilo() {
        running = true; //Indica que el hilo debe seguir ejecutándose
        workerThread = std::thread(&Singleton::tareaPeriodica, this); //Crea un nuevo hilo que ejecuta el método tareaPeriodica
    }

    //Detiene el hilo y limpia los recursos
    void detenerHilo() {
        running = false; //Indica que el hilo debe detenerse
        if (workerThread.joinable()) { //Si el hilo es un hilo válido
            workerThread.join(); //Espera a que el hilo termine su ejecución
        }
    }

    //Destructor para liberar los recursos
    ~Singleton() {
        detenerHilo(); //Asegura que el hilo se detenga antes de destruir la instancia
        std::cout << "Destructor Singleton" << std::endl; //Mensaje para indicar la destrucción del Singleton
    }
};

//Inicialización de la instancia única y el mutex
Singleton* Singleton::instancia = nullptr; //La instancia inicial es nullptr
std::mutex Singleton::mutex; //Inicialización del mutex

//Ejemplo de uso
int main() {
    //Obtén la instancia del Singleton con un intervalo de 3 segundos
    Singleton* singleton = Singleton::obtenerInstancia(3);

    //Ejecutar durante un tiempo y luego salir
    std::this_thread::sleep_for(std::chrono::seconds(20)); //Espera 20 segundos para ver la tarea periódica en acción

    //Destructor se llama automáticamente al final del scope de main
    return 0; //Termina el programa
}