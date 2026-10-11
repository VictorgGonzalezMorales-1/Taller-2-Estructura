
#pragma once
#include "Node.h"
template <class T> //Para usar los genéricos

class Stack {

private:
    Node<T>* start;
    int sizeStack;


    //Métodos
public:

    //Constructor
    Stack() {
        this->start = nullptr;
        this->sizeStack = 0;
    }

    //Insertar al inicio
    void push(T value) {
        Node<T>* n = new Node<T>(value);
        n->setNext(this->start);
        this->start = n;

        this->sizeStack++;
    }

    //Retira el elemento superior
    void pop() {
        if (this->start == nullptr) throw 0;

        Node<T>* toDelete = this->start;
        this->start = toDelete->getNext();
        delete toDelete;
        this->sizeStack--;
    }

    //Mira el elemento de arriba sin alterarlo
    T top() {
        if (start == nullptr) throw 0;
        return this->start->getValue();
    }

    //Revisa si está vacia
    bool isEmpty() {
        if (this->start == nullptr) return true;
        return false;
    }

    //Entrega el tamaño
    int size() {return this->sizeStack;}

    //Destructor
    ~Stack() {
        while (this->start != nullptr) {
            Node<T>* toDelete = this->start;
            this->start = toDelete->getNext();
            delete toDelete;
        }
        this->sizeStack = 0;
    }

};