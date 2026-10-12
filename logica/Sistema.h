#pragma once

#include "../dominio/Paciente.h"
#include "../estructuras/Node.h"
#include "../estructuras/List.h"
#include "../estructuras/Queue.h"
#include "../estructuras/NodeArbol.h"
#include <string>

using namespace std;

class Sistema {

//Atributos
private:
    Queue<Paciente*>* colaPacientes;
    NodeArbol<string>* arbolDeDesicion;

public:

    //Constructor
    Sistema();

    //metodos

    List<string>* split(const string& t, char separador);
    void crearPaciente(const string& linea);
    void guardarPacienteEnCola(Paciente* paciente);
    NodeArbol<string>* crearArbolDesicion();
    string definirServicio(Paciente* paciente, NodeArbol<string>* nodoActual);

    //Destructor
    ~Sistema();

};