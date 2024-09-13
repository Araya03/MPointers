# MPointers

MPointers es un proyecto que presenta una implementación de punteros inteligentes en C++. A diferencia de los punteros tradicionales, los MPointers permiten un control automático sobre la asignación y liberación de memoria, previniendo problemas comunes como las fugas de memoria. Para esto, incluye la implementación de una clase plantilla llamada MPointer que se encarga de encapsular un puntero. Además, utiliza un recolector de basura que de forma automática libera la memoria de los punteros que tienen el conteo de referencias en 0, asegurando así una gestión eficiente de los recursos. Dicho recolector se implementa mediante un hilo que periódicamente revisa los punteros y realiza la limpieza cuando es necesario.
Para probar la funcionalidad del proyecto, se elaboró una lista doblemente enlazada que contiene números enteros y es gestionada a través de MPointers. Con base a esta lista, se implementaron los algoritmos de ordenamiento QuickSort, BubbleSort e InsertionSort. La idea es que dichos algoritmos reciban como parámetro de entrada la lista doblemente enlazada y ordenen los elementos de manera ascendente.

Para probar MPointers:
1) Se debe abrir una terminal.
2) Escribir el comando "g++ -o (el nombre que desee) pruebas.cpp".
3) Escribir "./(nombre elegido)"
Esto ejecutará un archivo con varias pruebas.
