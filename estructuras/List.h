//Contrato de la clase

#pragma once
#include "Node.h"
template <class T> //Para usar genéricos

class List {

//Atributos
private:
    Node<T>* start;
    int size;

//Metodos
public:

    //Constructor
    List() {
        this-> start = nullptr;
        this-> size = 0;
    }

    //Getters
    T getFirst() {
        if (start == nullptr) throw 0;
        return this->start->getValue();
    }

    T getLast() {
        if (start == nullptr) throw 0;

        Node<T>* cursor = this->start;

        while(cursor->getNext() != nullptr) {
            cursor = cursor->getNext();
        }

        return cursor->getValue();
    }

    T get(int index) {
        if (start == nullptr || index < 0) throw 0;

        int count = 0;
        Node<T>* cursor = this->start;

        while (cursor!= nullptr && count < index) {
            cursor = cursor->getNext();
            count++;
        }

        if (cursor == nullptr) throw 0;

        return cursor->getValue();
    }

    int getSize() {return this->size;}

    //Setters
    void insertFirst(T value) {
        Node<T>* n = new Node<T>(value);
        n->setNext(this->start);
        this->start = n;
        size++;
    }

    void insertLast(T value) {
        if (start == nullptr) {
            this->start = new Node<T>(value);
            size++;
            return;
        }

        Node<T>* cursor = this->start;

        while (cursor->getNext() != nullptr) {
            cursor = cursor-> getNext();
        }

        cursor->setNext(new Node<T>(value));
        size++;
    }

    void insert(T value, int index) {
        if (index < 0) throw 0;
        if (index == 0) {
            this->insertFirst(value);
            return;
        }
        if (start == nullptr) throw 0;

        Node<T>* cursor = this->start;

        for (int a = 0; a < index-1; a++) {
            cursor = cursor->getNext();
            if (cursor == nullptr) throw 0;
        }

        Node<T>* n = new Node<T>(value);
        n->setNext(cursor->getNext());
        cursor->setNext(n);
        size++;
    }

    //Otros
    bool isEmpty() {
        if (start == nullptr) return true;
        return false;
    }

    void remove(int index) {
        if (index < 0 || start == nullptr) throw 0;
        if (index == 0) {
            Node<T>* toDelete = this->start;
            this->start = start->getNext();
            delete toDelete;
            size--;
            return;
        }

        Node<T>* cursor = this->start;

        for (int a = 0; a < index - 1; a++) {
            cursor = cursor-> getNext();
            if (cursor == nullptr) throw 0;
        }

        Node<T>* toDelete = cursor->getNext();

        if (toDelete == nullptr) throw 0;
        cursor->setNext(toDelete->getNext());
        delete toDelete;
        size--;
    }

    void clear() {
        while (this->start != nullptr) {
            Node<T>* save = this->start->getNext();
            delete this->start;
            size--;
            this->start = save;
        }
    }

    ~List() {this->clear();} //Destructor

};