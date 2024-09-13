#include "MPointer.h"
#include <iostream>

int main() {
    std::cout << "Iniciando prueba de MPointer..." << std::endl;

    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;
    myPtr.printInfo(); //Muestra valor y contador de referencias

    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr;
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias

    MPointer<int> myPtr3 = myPtr; //Asigna myPtr a myPtr3
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias
    myPtr3.printInfo(); //Muestra valor y contador de referencias

    MPointer<int> myPtr4 = myPtr; //Asigna myPtr a myPtr4
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias
    myPtr3.printInfo(); //Muestra valor y contador de referencias
    myPtr4.printInfo(); //Muestra valor y contador de referencias
    
    
    MPointer<int> myPtr5 = myPtr; //Asigna myPtr a myPtr5
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias
    myPtr3.printInfo(); //Muestra valor y contador de referencias
    myPtr4.printInfo(); //Muestra valor y contador de referencias
    myPtr5.printInfo(); //Muestra valor y contador de referencias

    *myPtr = 20; //Cambia el valor a través de myPtr
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias
    myPtr3.printInfo(); //Muestra valor y contador de referencias
    myPtr4.printInfo(); //Muestra valor y contador de referencias
    myPtr5.printInfo(); //Muestra valor y contador de referencias

    *myPtr = 456; //Cambia el valor a través de myPtr
    myPtr.printInfo(); //Muestra valor y contador de referencias
    myPtr2.printInfo(); //Muestra valor y contador de referencias
    myPtr3.printInfo(); //Muestra valor y contador de referencias
    myPtr4.printInfo(); //Muestra valor y contador de referencias
    myPtr5.printInfo(); //Muestra valor y contador de referencias

    return 0;
}