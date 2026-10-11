
#pragma once
#include "Node.h"
template <class T> //Para usar los genéricos

class Queue {
private:
    Node<T>* start;
    Node<T>* end;
    int sizeQueue;

public:

    //Constructor
    Queue() {
        this->start = nullptr;
        this->end = nullptr;
        this->sizeQueue = 0;
    }

    //Insertar al final
    void push(T value) {
        Node<T>* add = new Node<T>(value);

        if (this->start == nullptr) {
            this->start = add;
            this->end = add;
            sizeQueue++;
            return;
        }

        this->end->setNext(add);
        this->end = add;
        sizeQueue++;
    }

    //Elimina al del frente
    void pop() {
        if (this->start == nullptr) throw 0;

        Node<T>* toDelete = this->start;
        this->start = toDelete->getNext();

        if (this->start == nullptr)
            this->end = nullptr;

        delete toDelete;
        sizeQueue--;
    }

    //Entrega el valor del principio de la fila
    T front() {
        if (this->start == nullptr) throw 0;
        return this->start->getValue();
    }

    //Entrega el valor del final de la fila
    T back() {
        if (this->start == nullptr) throw 0;
        return this->end->getValue();
    }

    //Dice si está o no vacia la cola
    bool isEmpty() {
        if (this->start == nullptr) return true;
        return false;
    }

    //Entrega el tamaño
    int size() {
        return sizeQueue;
    }

    //Destructor
    ~Queue() {
        while (start != nullptr) {
            Node<T>* toDelete = this->start;
            start = toDelete->getNext();
            delete toDelete;
        }

        this->sizeQueue = 0;
    }

};