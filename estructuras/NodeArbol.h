
#pragma once
#include<string>
template <class T>

class NodeArbol {

//Atributos
private:
    T value;
    string pregunta;
    NodeArbol<T>* derecha;
    NodeArbol<T>* izquierda;

public:

    //Constructor
    NodeArbol(T value) {
        this->value = value;
        this->derecha = nullptr;
        this->izquierda = nullptr;
        this->pregunta = "";
    }

    //Getters
    T getValue() const {return this->value;}
    NodeArbol<T>* getDerecho() const {return this->derecha;}
    NodeArbol<T>* getIzquierdo() const {return this->izquierda;}
    string getPregunta() const {return this->pregunta;}

    //Setters
    void setValue(T value){this->value = value;}
    void setDerecha(NodeArbol<T>* derecha){ this->derecha = derecha;}
    void setIzquierda(NodeArbol<T>* izquierda){this->izquierda = izquierda;}
    void setPregunta(string pregunta){this->pregunta = pregunta;}

    //Destructor
    ~NodeArbol(){
        delete derecha;
        delete izquierda;
    }

};