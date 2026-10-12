#pragma once

#include "../dominio/Paciente.h"
#include "../estructuras/Node.h"
#include "../estructuras/List.h"
#include "../estructuras/Queue.h"
#include <string>

using namespace std;

class Sistema {

//Atributos
private:
    Queue<Paciente*>* colaPacientes;

public:

    //Constructor
    Sistema();

    //metodos

    List<string>* split(const string& t, char separador);
    void crearPaciente(const string& linea);
    void guardarPacienteEnCola(Paciente* paciente);

    //Destructor
    ~Sistema();

};