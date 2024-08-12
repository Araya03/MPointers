#include <iostream>

template <typename T>
class MPointer {
private:
    T* ptr; // Puntero encapsulado
    int id; // ID proporcionado por MPointerGC

    // Constructor privado para asegurar que solo se pueda crear a través de New()
    MPointer() {
        ptr = new T(); // Reservar memoria para el tipo T
        id = -1; // El ID será asignado por MPointerGC
    }

public:
    // Destructor para liberar la memoria
    ~MPointer() {
        delete ptr;
        // Aquí se debe notificar a MPointerGC que el objeto ha sido destruido
    }

    // Método estático para crear un nuevo MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        // Aquí se debe registrar el MPointer en MPointerGC y asignar un ID
        return mp;
    }

    // Sobrecarga del operador * para acceder al valor apuntado
    T& operator*() {
        return *ptr;
    }

    // Sobrecarga del operador & para obtener el valor apuntado
    T operator&() {
        return *ptr;
    }

    // Sobrecarga del operador = para manejar la asignación
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this == &other) {
            return *this; // Evitar auto-asignación
        }
        delete ptr; // Liberar la memoria actual
        ptr = other.ptr; // Copiar el puntero
        id = other.id; // Copiar el ID
        return *this;
    }

    // Sobrecarga del operador = para asignar un valor de tipo T
    MPointer<T>& operator=(T value) {
        *ptr = value;
        return *this;
    }
};

// Ejemplo de uso
int main() {
    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;
    std::cout << "Valor: " << &myPtr << std::endl;

    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr;

    std::cout << "Valor en myPtr2: " << &myPtr2 << std::endl;

    return 0;
}