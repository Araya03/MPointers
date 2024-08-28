#include <iostream>
#include <memory> // Para std::shared_ptr y std::make_shared>
#include "MPointer.h"

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        MPointer<T> data;        // Cambiado de T a MPointer<T>
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;

        Node(const MPointer<T>& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(const MPointer<T>& data) {
        auto newNode = std::make_shared<Node>(data);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printList() const {
        auto current = head;
        while (current) {
            std::cout << *current->data << " "; // Usando el operador de desreferenciación de MPointer
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Función de partición para QuickSort
    std::shared_ptr<Node> partition(std::shared_ptr<Node> low, std::shared_ptr<Node> high) {
        MPointer<T> pivot = high->data;
        auto i = low ? low->prev : nullptr;

        for (auto j = low; j != high; j = j->next) {
            if (*j->data <= *pivot) { // Comparación usando el operador de desreferenciación
                i = (i == nullptr) ? low : i->next;
                std::swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? low : i->next;
        std::swap(i->data, high->data);
        return i;
    }

    // Función recursiva de QuickSort
    void quickSortRec(std::shared_ptr<Node> low, std::shared_ptr<Node> high) {
        if (high && low && low != high && low != high->next) {
            auto p = partition(low, high);
            quickSortRec(low, p->prev);
            quickSortRec(p->next, high);
        }
    }

    // Función pública para ordenar la lista con QuickSort
    void quickSort() {
        quickSortRec(head, tail);
    }

    // BubbleSort
    void bubbleSort() {
        if (!head) return;
        
        bool swapped;
        do {
            swapped = false;
            auto current = head;
            while (current && current->next) {
                if (*current->data > *current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // InsertionSort
    void insertionSort() {
    if (!head) return;

    // Initialize the sorted list
    auto sorted = head;
    auto unsorted = head->next;
    sorted->prev = nullptr;
    sorted->next = nullptr;

    while (unsorted) {
        auto current = unsorted;
        unsorted = unsorted->next;

        // Detach the current node from the unsorted list
        current->next = nullptr;
        current->prev = nullptr;

        // Insert the current node into the sorted list
        if (*current->data < *head->data) {
            // Insert at the beginning
            current->next = head;
            head->prev = current;
            head = current;
        } else {
            // Insert in the middle or at the end
            auto temp = head;
            while (temp->next && *temp->next->data < *current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }
    }

    // Recalculate the tail pointer
    tail = head;
    while (tail->next) {
        tail = tail->next;
    }
}

};

// Programa principal para probar las funciones
int main() {
    DoublyLinkedList<int> list;
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 28;
    MPointer<int> ptr2 = MPointer<int>::New();
    *ptr2 = 35;
    MPointer<int> ptr3 = MPointer<int>::New();
    *ptr3 = 70;
    MPointer<int> ptr4 = MPointer<int>::New();
    *ptr4 = 813;
    MPointer<int> ptr5 = MPointer<int>::New();
    *ptr5 = 1;
    MPointer<int> ptr6 = MPointer<int>::New();
    *ptr6 = 2;
    MPointer<int> ptr7 = MPointer<int>::New();
    *ptr7 = 230;

    list.append(ptr1);
    list.append(ptr2);
    list.append(ptr3);
    list.append(ptr4);
    list.append(ptr5);
    list.append(ptr6);
    list.append(ptr7);

    std::cout << "Lista antes de ordenar: ";
    list.printList();

    // QuickSort
    list.quickSort();
    std::cout << "Lista despues de QuickSort: ";
    list.printList();

    // Re-inicializa la lista para otras pruebas
    list = DoublyLinkedList<int>();
    list.append(ptr1);
    list.append(ptr2);
    list.append(ptr3);
    list.append(ptr4);
    list.append(ptr5);
    list.append(ptr6);
    list.append(ptr7);

    // BubbleSort
    list.bubbleSort();
    std::cout << "Lista despues de BubbleSort: ";
    list.printList();

    // Re-inicializa la lista para otras pruebas
    list = DoublyLinkedList<int>();
    list.append(ptr1);
    list.append(ptr2);
    list.append(ptr3);
    list.append(ptr4);
    list.append(ptr5);
    list.append(ptr6);
    list.append(ptr7);

    // InsertionSort
    list.insertionSort();
    std::cout << "Lista despues de InsertionSort: ";
    list.printList();

    return 0;
}