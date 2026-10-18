
#pragma once

#include "NodeAVL.h"
#include <algorithm>
#include "../dominio/Paciente.h"
template <class T>

class AVL {

//Atributos
private:
    NodeAVL<T>* raiz;

    int getAltura(NodeAVL<T>* padre) {
        if (padre == nullptr) return 0;
        return padre->getAltura();
    }

    //Formula factor de balance
    int getBalance(NodeAVL<T>* padre) {
        if (padre == nullptr) return 0;
        return getAltura(padre->getIzquierdo()) - getAltura(padre->getDerecho());
    }

    //Metodo recursivo para insertar
    NodeAVL<T>* insertarValor(NodeAVL<T>* padre, NodeAVL<T>* insertar) {

        //Caso en el que no hay nada en la raiz
        if (padre == nullptr){return insertar;}

        // Caso cuando el valor es menor
        if (*(padre->getValue()) > *(insertar->getValue())) {
            padre->setIzquierdo(insertarValor(padre->getIzquierdo(), insertar));
        }

        // Caso cuando el valor es mayor
        else {
            padre->setDerecho(insertarValor(padre->getDerecho(), insertar));
        }

        //Actualizar la altura del padre
        int altura = 1 + max(getAltura(padre->getIzquierdo()), getAltura(padre->getDerecho()));
        padre->setAltura(altura);

        //Se calcula el factor de balance
        int balance = getBalance(padre);

        //Casos de balanceo

        //Izquierda Izquierda
        if (balance > 1 && *(insertar->getValue()) < *(padre->getIzquierdo()->getValue())) {
            return LL(padre);
        }

        //Derecha Derecha
        if (balance < -1 && *(insertar->getValue()) > *(padre->getDerecho()->getValue())) {
            return RR(padre);
        }

        //Izquierda Derecha
        if (balance > 1 && *(insertar->getValue()) > *(padre->getIzquierdo()->getValue())) {
            return LR(padre);
        }

        //Derecha Izquierda
        if (balance < -1 && *(insertar->getValue()) < *(padre->getDerecho()->getValue())) {
            return RL(padre);
        }

        return padre;

    }

    //Metodo del caso 1 cuando tenemos un LL
    NodeAVL<T>* LL(NodeAVL<T>* padre) {

        //Almacenar los hijos
        NodeAVL<T>* izquierdo = padre->getIzquierdo();
        NodeAVL<T>* derecho = izquierdo->getDerecho();

        //Acomodarlos
        izquierdo->setDerecho(padre);
        padre->setIzquierdo(derecho);

        //Actualizar las alturas
        padre->setAltura(1 + max(getAltura(padre->getIzquierdo()), getAltura(padre->getDerecho())));
        izquierdo->setAltura(1 + max(getAltura(izquierdo->getIzquierdo()), getAltura(izquierdo->getDerecho())));

        return izquierdo;
    }

    //Metodo cuando tenemos el caso RR
    NodeAVL<T>* RR(NodeAVL<T>* padre) {

        // Almacenar los hijos
        NodeAVL<T>* derecho = padre->getDerecho();
        NodeAVL<T>* izquierdo = derecho->getIzquierdo();

        // Acomodar
        derecho->setIzquierdo(padre);
        padre->setDerecho(izquierdo);

        // Actualizar las altura
        padre->setAltura(1 + max(getAltura(padre->getIzquierdo()), getAltura(padre->getDerecho())));
        derecho->setAltura(1 + max(getAltura(derecho->getIzquierdo()), getAltura(derecho->getDerecho())));

        return derecho;
    }

    //Metodo cuando tenemos el caso LR
    NodeAVL<T>* LR(NodeAVL<T>* padre) {
        //Arreglar los subarboles
        padre->setIzquierdo(RR(padre->getIzquierdo()));

        // Aplicar el LL
        return LL(padre);
    }

    //Metodo cuando tenemos el caso RL
    NodeAVL<T>* RL(NodeAVL<T>* padre) {
        //Acomodamos
        padre->setDerecho(LL(padre->getDerecho()));

        //Aplicar RR
        return RR(padre);
    }

    // Sistema para aplicar la busqueda
    Paciente* buscarValor(NodeAVL<T>* padre, int valor, string& ruta) {

        //Si no hay nada
        if (padre == nullptr) return nullptr;

        //Almacenar la ruta
        ruta += to_string(padre->getValue()->getId()) + "-> ";

        // Si ya lo encontro
        if (padre->getValue()->getId() == valor) return padre->getValue();

        //Camino si es menor
        if (padre->getValue()->getId() > valor) {return buscarValor(padre->getIzquierdo(), valor, ruta);}

        //Camino si es Mayor
        return buscarValor(padre->getDerecho(), valor, ruta);
    }

    // Calcular el InOrden
    void calcInOrden(NodeAVL<T>* padre, string& texto) {

        //Caso de que estpe vacio
        if (padre == nullptr) return;

        //Entrar al nodo Izquierdo
        if (padre->getIzquierdo() != nullptr){calcInOrden(padre->getIzquierdo(), texto);}

        //Almacenar el dato del padre
        texto +=  padre->toString() + "\n\n";

        //Entrar al nodo Derecho
        if (padre->getDerecho() != nullptr){calcInOrden(padre->getDerecho(), texto);}

    }

    // Calcular el PreOrden
    void calcPreOrden(NodeAVL<T>* padre, string& texto) {

        //Revisar que no tire fallo si está vacio
        if (padre == nullptr) return;

        //Almacenar el valor del padre
        texto += padre->toString() + "\n\n";

        //Pasar al izquierdo
        if (padre->getIzquierdo() != nullptr) {
            calcPreOrden(padre->getIzquierdo(), texto);
        }

        //Pasar al Derecho
        if (padre->getDerecho() != nullptr) {
            calcPreOrden(padre->getDerecho(), texto);
        }

    }

    // Calcular el PostOrden
    void calcPostOrden(NodeAVL<T>* padre, string& texto) {

        // Revisar que no esté vacío el padre
        if (padre == nullptr) {return;}

        // Entrar al izquierdo
        if (padre->getIzquierdo() != nullptr) {calcPostOrden(padre->getIzquierdo(), texto);}

        // Entrar al Derecho
        if (padre->getDerecho() != nullptr) {calcPostOrden(padre->getDerecho(), texto);}

        texto+= padre->toString() + "\n\n";

    }

    //Metodo recursivo para eliminar todos los nodos
    void destruir(NodeAVL<T>* padre) {

        //Si no hay nada que destruir simplemente se termina la función
        if (padre == nullptr) return;

        //Ir a las ramas
        destruir(padre->getIzquierdo());
        destruir(padre->getDerecho());

        //Eliminar el dato interno del nodo
        if (padre->getValue() != nullptr) {
            delete padre->getValue();
        }

        //Eliminar el nodo
        delete padre;

    }

//Metodos
public:

    //Constructor
    AVL() {
        this->raiz = nullptr;
    }

    //Metodo para insertar un valor pero quitando la lógica de la actualización del nodo padre
    void insertar(NodeAVL<T>* valor) {
        if (valor == nullptr) return;

        //Como el orden cambia por el ordenamiento aveces, se actualiza por completo la estructura
        this->raiz = insertarValor(this->raiz, valor);
    }

    //Metodo para buscar un valor (en este caso el id)
    Paciente* buscar(int valor, string& ruta) {return buscarValor(this->raiz, valor, ruta);}

    //Metodo para entregar los paciente InOrden
    string inOrden() {

        string orden = "== InOrden ==";
        calcInOrden(this->raiz, orden);

        return orden;
    }

    //Metodo para entregar los paciente PreOrden
    string preOrden() {

        string orden = "== PreOrden ==";
        calcPreOrden(this->raiz, orden);

        return orden;
    }

    //Metodo para entregar los paciente PostOrden
    string postOrden() {

        string orden = "== PosOrden ==";
        calcPostOrden(this->raiz, orden);

        return orden;
    }

    //Destructor
    ~AVL() {
        destruir(this->raiz);
        this->raiz = nullptr;
    }

};