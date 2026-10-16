
#pragma once
template <class T>

class NodeAVL {

//Atributos
private:
    T value;
    int altura;
    NodeAVL<T>* izquierdo;
    NodeAVL<T>* derecho;

//Métodos
public:

    //Constructor
    NodeAVL(T value) {
        this->value = value;
        this->altura = 1;
        this->izquierdo = nullptr;
        this->derecho = nullptr;
    }

    //Getters
    T getValue() const {return this->value;}
    int getAltura() const {return this->altura;}
    NodeAVL<T>* getIzquierdo() const {return this->izquierdo;}
    NodeAVL<T>* getDerecho() const {return this->derecho;}

    //Setters
    void setValue(T value){this->value = value;}
    void setAltura(int altura){this->altura = altura;}
    void setIzquierdo(NodeAVL<T>* izquierdo){this->izquierdo = izquierdo;}
    void setDerecho(NodeAVL<T>* derecho){this->derecho = derecho;}

    //Destructor
    ~NodeAVL(){}

};