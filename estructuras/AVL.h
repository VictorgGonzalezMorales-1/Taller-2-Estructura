
#pragma once

#include "NodeAVL.h"
#include <string>
#include <algorithm>
#include "../dominio/Paciente.h"

using namespace std;

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
    Paciente* buscarValorID(NodeAVL<T>* padre, int valor, string& ruta) {

        //Si no hay nada
        if (padre == nullptr) return nullptr;

        //Almacenar la ruta
        ruta += to_string(padre->getValue()->getId()) + "-> ";

        // Si ya lo encontro
        if (padre->getValue()->getId() == valor) return padre->getValue();

        //Camino si es menor
        if (padre->getValue()->getId() > valor) {return buscarValorID(padre->getIzquierdo(), valor, ruta);}

        //Camino si es Mayor
        return buscarValorID(padre->getDerecho(), valor, ruta);
    }

    // Sistema para aplicar la busqueda
    Paciente* buscarValorNombre(NodeAVL<T>* padre, const string& nombre, string& ruta) {

        //Si no hay nada
        if (padre == nullptr) return nullptr;

        //Almacenar la ruta
        ruta += to_string(padre->getValue()->getId()) + "-> ";

        // Si ya lo encontro
        if (padre->getValue()->getNombre() == nombre) return padre->getValue();

        //Buscar en el subarbol izquierdo
        Paciente* encontrado = buscarValorNombre(padre->getIzquierdo(), nombre, ruta);
        if (encontrado != nullptr) return encontrado;

        //Si no estaba a la izquierda, buscar en el derecho
        return buscarValorNombre(padre->getDerecho(), nombre, ruta);
    }

    // Calcular el InOrden
    void calcInOrden(NodeAVL<T>* padre, string& texto) {

        //Caso de que estpe vacio
        if (padre == nullptr) return;

        //Entrar al nodo Izquierdo
        if (padre->getIzquierdo() != nullptr){calcInOrden(padre->getIzquierdo(), texto);}

        //Almacenar el dato del padre
        texto +=  "Pacientes: " + padre->getValue()->getNombre() + " (" + to_string(padre->getValue()->getId()) + ")" + "\n";

        //Entrar al nodo Derecho
        if (padre->getDerecho() != nullptr){calcInOrden(padre->getDerecho(), texto);}

    }

    // Calcular el PreOrden
    void calcPreOrden(NodeAVL<T>* padre, string& texto) {

        //Revisar que no tire fallo si está vacio
        if (padre == nullptr) return;

        //Almacenar el valor del padre
        texto +=  "Pacientes: " + padre->getValue()->getNombre() + " (" + to_string(padre->getValue()->getId()) + ")" + "\n";

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

        texto +=  "Pacientes: " + padre->getValue()->getNombre() + " (" + to_string(padre->getValue()->getId()) + ")" + "\n";

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

    //Metodo para encontrar al menor del nodo que le den
    NodeAVL<T>* getMenor(NodeAVL<T>* padre) {

        //Guardar el nodo
        NodeAVL<T>* actual = padre;

        //Bucle para ir lo más a la derecha posible
        while (actual->getIzquierdo() != nullptr) {
            actual = actual->getIzquierdo();
        }

        return actual;
    }

    //Metodo para trabajar toda la lógica de eliminar elemento
    NodeAVL<T>* eliminarElemento(NodeAVL<T>* padre, int posicion) {

        //Si no hay nada
        if (padre == nullptr) return nullptr;

        //Guardar el id a comparar
        int idComparada = padre->getValue()->getId();

        //Si el id es menor pasamos al izquierdo
        if (posicion < idComparada) {padre->setIzquierdo(eliminarElemento(padre->getIzquierdo(), posicion));}
        //Si el id es mayor pasamos al derecho
        else if (posicion > idComparada) {padre->setDerecho(eliminarElemento(padre->getDerecho(), posicion));}
        //Si encontramos el valor
        else {
            // Si se tiene uno o ningún hijo
            if (padre->getIzquierdo() == nullptr || padre->getDerecho() == nullptr) {

                NodeAVL<T>* hijo = nullptr;

                if (padre->getIzquierdo() != nullptr){hijo = padre->getIzquierdo();}
                else{hijo = padre->getDerecho();}

                // Si no tiene hijo se elimina al padre y se almacenan sus datos
                if (hijo == nullptr){
                    hijo = padre;
                    padre = nullptr;

                    //Eliminar el paciente dentro del nodo
                    if (hijo->getValue() != nullptr) { delete hijo->getValue(); }
                    delete hijo;
                }
                // Si tiene un hijo se sustituye la información del padre con la de un hijo
                else {
                    //Almacenar el hijo
                    NodeAVL<T>* temporal = hijo;

                    //Eliminar el paciente guardado
                    delete padre->getValue();

                    //Pasar la informacion
                    padre->setValue(temporal->getValue());
                    padre->setIzquierdo(temporal->getIzquierdo());
                    padre->setDerecho(temporal->getDerecho());
                    padre->setAltura(temporal->getAltura());

                    //Se libera el nodo que quedó
                    delete temporal;
                }

            }
            else {

                //Guardar el menor del hijo derecho
                NodeAVL<T>* hijo = getMenor(padre->getDerecho());

                //Guardar el paciente del nodo que vamos a eliminar
                Paciente* pacienteABorrar = padre->getValue();

                //Intercambiamos el valor de los pacientes del padre y del hijo
                padre->setValue(hijo->getValue());
                hijo->setValue(pacienteABorrar);

                //Eliminamos
                padre->setDerecho(eliminarElemento(padre->getDerecho(), hijo->getValue()->getId()));

            }
        }

        //Si el padre esta vacio terminamos
        if (padre == nullptr) return nullptr;

        //Revisar que te balanceado y si no arreglar

        int altura = 1 + max(getAltura(padre->getIzquierdo()), getAltura(padre->getDerecho()));
        padre->setAltura(altura);

        int balance = getBalance(padre);

        if (balance > 1) {
            if (getBalance(padre->getIzquierdo()) >= 0) { return LL(padre);}
            return LR(padre);
        }

        if (balance < -1) {
            if (getBalance(padre->getDerecho()) <= 0) {return RR(padre);}
            return RL(padre);
        }

        return padre;

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
    Paciente* buscarID(int valor, string& ruta) {return buscarValorID(this->raiz, valor, ruta);}

    //Metodo para buscar un valor (en este caso el nombre)
    Paciente* buscarNombre(const string& nombre, string& ruta) {return buscarValorNombre(this->raiz, nombre, ruta);}

    //Metodo para entregar los paciente InOrden
    string inOrden() {

        string orden = "== InOrden ==\n\n";
        calcInOrden(this->raiz, orden);

        return orden;
    }

    //Metodo para entregar los paciente PreOrden
    string preOrden() {

        string orden = "== PreOrden ==\n\n";
        calcPreOrden(this->raiz, orden);

        return orden;
    }

    //Metodo para entregar los paciente PostOrden
    string postOrden() {

        string orden = "== PosOrden ==\n\n";
        calcPostOrden(this->raiz, orden);

        return orden;
    }

    //Metodo para eliminar un elemento
    void eliminar(int numero) {
        this->raiz = eliminarElemento(this->raiz, numero);
    }

    //Destructor
    ~AVL() {
        destruir(this->raiz);
        this->raiz = nullptr;
    }

};