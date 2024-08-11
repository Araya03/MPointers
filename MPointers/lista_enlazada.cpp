#include <iostream>

//Definición de la estructura Nodo
template<typename T>
struct Nodo {
    T* dato; //Puntero al valor que almacenamos
    Nodo* siguiente; //Puntero que apunta al siguiente nodo en la lista

    //Constructor que inicializa un nodo con un valor y establece "siguiente" como nullptr
    Nodo(T* valor) : dato(valor), siguiente(nullptr) {}
};

//Definición de la clase ListaEnlazada
template<typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza; //Puntero al primer nodo de la lista (cabeza de la lista)

public:
    //Constructor que inicializa la lista como vacía (cabeza es nullptr)
    ListaEnlazada() : cabeza(nullptr) {}

    //Método para insertar un nodo al inicio de la lista
    void insertarAlInicio(T* valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor); //Creamos un nuevo nodo con el valor dado
        nuevoNodo->siguiente = cabeza; //El nuevo nodo apunta al nodo que era la cabeza de la lista
        cabeza = nuevoNodo; //Actualizamos la cabeza de la lista para que sea el nuevo nodo
    }

    //Método para insertar un nodo al final de la lista
    void insertarAlFinal(T* valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor); //Creamos un nuevo nodo con el valor dado
        if (cabeza == nullptr) { //Si la lista está vacía
            cabeza = nuevoNodo; //El nuevo nodo se convierte en la cabeza de la lista
        } else { //Si la lista no está vacía
            Nodo<T>* ptrtemporal = cabeza; //Usamos un puntero temporal para recorrer la lista
            while (ptrtemporal->siguiente != nullptr) { //Avanzamos hasta el último nodo
                ptrtemporal = ptrtemporal->siguiente;
            }
            ptrtemporal->siguiente = nuevoNodo; //El último nodo ahora apunta al nuevo nodo
        }
    }

    //Método para imprimir las direcciones de memoria de la lista
    void imprimirDirecciones() const {
        Nodo<T>* ptrtemporal = cabeza;
        while (ptrtemporal != nullptr) {
            std::cout << ptrtemporal->dato << " -> "; //Imprimimos la dirección de memoria a la que apunta "dato"
            ptrtemporal = ptrtemporal->siguiente;
        }
        std::cout << "Fin de la lista" << std::endl; // Fin de la lista
    }

    //Destructor para liberar la memoria de los nodos al destruir la lista
    ~ListaEnlazada() {
        Nodo<T>* ptrtemporal;
        while (cabeza != nullptr) { //Mientras haya nodos en la lista
            ptrtemporal = cabeza; //Guardamos el nodo actual
            cabeza = cabeza->siguiente; //Avanzamos al siguiente nodo
            delete ptrtemporal->dato; //Liberamos la memoria del valor al que "dato" apunta
            delete ptrtemporal; //Borramos el nodo actual para liberar memoria
        }
    }
};

int main() {
    ListaEnlazada<int> lista; //Creamos una lista vacía que acepte enteros

    int* valor1 = new int(1);
    int* valor2 = new int(2);
    int* valor3 = new int(3);

    lista.insertarAlInicio(valor1); //Insertamos valores en la lista
    lista.insertarAlInicio(valor2);
    lista.insertarAlInicio(valor3);

    lista.imprimirDirecciones(); //Imprimimos las direcciones de memoria

    return 0; //Fin del programa, retorno 0 indica que el programa terminó correctamente
}