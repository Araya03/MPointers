#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void append(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remove(const T& value) {
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        while (current) {
            if (current->data == value) {
                if (previous) {
                    previous->next = current->next;
                    if (current == tail) {
                        tail = previous;
                    }
                } else {
                    head = current->next;
                    if (!head) {
                        tail = nullptr;
                    }
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    Node<T>* begin() const {
        return head;
    }

    Node<T>* end() const {
        return nullptr;
    }
};

#endif //LISTAENLAZADA_H