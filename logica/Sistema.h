#pragma once

#include "../dominio/Paciente.h"
#include "../estructuras/Node.h"
#include "../estructuras/List.h"
#include "../estructuras/Queue.h"
#include "../estructuras/NodeArbol.h"
#include "../estructuras/AVL.h"
#include <string>

using namespace std;

class Sistema {

//Atributos
private:
    Queue<Paciente*>* colaPacientes;
    NodeArbol<string>* arbolDeDesicion;
    List<string>* idPacientes;
    string servicios[8] = {
        "Urgencias",
        "Medicina General",
        "Cardiología",
        "Neurología",
        "Traumatología",
        "Cirugía",
        "Pediatría",
        "Hospitalización"
    };
    List<AVL<Paciente*>*>* arboles;

public:

    //Constructor
    Sistema();

    //metodos

    List<string>* split(const string& t, char separador);
    void crearPaciente(const string& linea);
    void guardarPacienteEnCola(Paciente* paciente);
    NodeArbol<string>* crearArbolDesicion();
    string definirServicio(Paciente* paciente, NodeArbol<string>* nodoActual, string texto);
    string atenderPacientes(int n);
    string buscarPaciente(int id);
    string entregarServiciosPacientes();

    //Destructor
    ~Sistema();

};