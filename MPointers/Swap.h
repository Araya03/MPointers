#ifndef SWAP_H
#define SWAP_H

//Función para intercambiar dos valores
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

#endif //SWAP_H