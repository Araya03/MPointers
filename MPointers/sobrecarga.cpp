#include <iostream>

class myptr {
private:
    int valor; //myptr tiene un miembro privado llamado "valor" que almacena un entero

public:
    //Constructor que inicializa el miembro "valor" con el valor que se pasa como argumento
    myptr(int v) : valor(v) {}

    //Sobrecarga del operador & para la clase myptr
    myptr* operator&() {
        std::cout << "Sobrecarga del operador &" << std::endl;
        return this; //RETORNAMOS UN PUNTERO AL OBJETO ACTUAL
    }

    //Sobrecarga del operador * para la clase myptr
    int& operator*() {
        std::cout << "Sobrecarga del operador *" << std::endl;
        return valor; //RETORNAMOS EL VALOR QUE ESTÁ GUARDADO EN "int valor"
    }
};

int main() {
    myptr obj(100); //Creamos un objeto de tipo myptr y lo inicializamos con el valor 100

    //Aquí usamos la sobrecarga del operador & para obtener un puntero al objeto "obj"
    //Esto llamará a la función operator&() que hemos definido en la clase myptr
    myptr* ptr = &obj;

    //Aquí usamos la sobrecarga del operador * para obtener una referencia al miembro "valor" de "obj"
    //Esto llamará a la función operator*() que hemos definido en la clase myptr
    int valor = *obj;

    //Imprimimos el valor obtenido con la sobrecarga del operador *
    std::cout << "Valor: " << valor << std::endl;

    return 0; //Fin del programa, retorno 0 indica que el programa finalizó correctamente
}