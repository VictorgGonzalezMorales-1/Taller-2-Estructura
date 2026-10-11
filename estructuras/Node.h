//Contrato de la clase

#pragma once // Para que solo se use una vez
template <class T> //Para usar genéricos

class Node {

//Atributos de la clase
private:
    T value;
    Node<T>* next;

//Métodos
public:

    //Constructor
    Node(T value) {
        this->value = value;
        this->next = nullptr;
    }

    //Getters
    T getValue(){return this->value;}
    Node<T>* getNext(){return this->next;}

    //Setters
    void setValue(T value){this->value = value;}
    void setNext(Node<T>* next){this->next = next;}

    ~Node(){} //Destructor
};