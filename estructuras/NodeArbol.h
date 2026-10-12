
#pragma once
template <class T>

class NodeArbol {

//Atributos
private:
    T value;
    NodeArbol<T>* derecha;
    NodeArbol<T>* izquierda;

public:

    //Constructor
    NodeArbol(T value) {
        this->value = value;
        this->derecha = nullptr;
        this->izquierda = nullptr;
    }

    //Getters
    T getValue() const {return this->value;}
    NodeArbol<T>* getDerecho() const {return this->derecho;}
    NodeArbol<T>* getIzquierdo() const {return this->izquierdo;}

    //Setters
    void setValue(T value){this->value = value;}
    void setDerecha(NodeArbol<T>* derecha){ this->derecha = derecha;}
    void setIzquierda(NodeArbol<T>* izquierda){this->izquierda = izquierda;}

    //Destructor
    ~NodeArbol(){
        delete derecha;
        delete izquierda;
    }

};