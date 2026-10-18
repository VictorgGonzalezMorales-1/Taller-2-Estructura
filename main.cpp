
#include <iostream>
#include <string>
#include <fstream>
#include "logica/Sistema.h"

using namespace std;

//Importar el sistema de Manera global
static Sistema* S = new Sistema();

//Metodo para imprimir rapidamente
static void p(const string& t) {cout << t << endl;}

//Metodo para leer el archivo
static bool read() {

    //Cargar el archivo
    ifstream archivo("../Pacientes.txt");

    //Si el archivo no está termina la lectura y no permite abrir el menu
    if (!archivo.is_open()) {
        p("No se puede cargar el archivo");
        return false;
    }

    //Variable para almacenar la linea
    string linea;

    //Bucle para leer las líneas del archivo
    while (getline(archivo, linea)) {
        S->crearPaciente(linea);
    }

    //Cerrar el archivo
    archivo.close();

    return true;
}

//Metodo para desarrollar la opcion 1 del menu
static void opcion1() {

    try {

        //Solicitar los datos
        string respuesta = "";
        p("Entregue la cantidad de pacientes que desee antender: ");

        cin >> respuesta;

        int numero = stoi(respuesta);

        //Revisar que sean datos válidos
        if (numero > 0) {
            p(S->atenderPacientes(numero));
        }
        else {
            p("Ingrese un numero mayor que 0 ....\n");
        }

    }
    catch (...) {
        p("Datos invalidos....\n");
    }
}

//Metodo para desarrollar la opcion 2 del menu
static void opcion2() {
    p(S->entregarServiciosPacientes());
}

//Metodo para desarrollar la opcion 3 del menu
static void opcion3() {

    try {

        //Solicitar los datos
        string respuesta = "";
        p("Ingrese el id que desea buscar: ");

        cin >> respuesta;

        int numero = stoi(respuesta);

        //Revisar que sean datos válidos
        if (numero > 0) {
            p(S->buscarPaciente(numero) + "\n");
        }
        else {
            p("Ingrese un id válido ....\n");
        }

    }
    catch (...) {
        p("Ingrese un id válido ....\n");
    }

}

//Metodo el cual desplegara el menu a emplear
static void menu() {

    //Variable para almacenar la respuesta
    string opcion;

    //Bucle para preguntar hasta que quiera salir
    while (opcion != "4") {

        //Mostrar el menu reiteradamente
        p("=== HOSPITAL MARMAJA === \n"
          "1. Atender paciente\n"
          "2. Ver departamento\n"
          "3. Buscar paciente\n"
          "4. Salir\n");

        p("Seleccionar opcion:");

        //Escribir la opcion
        cin >> opcion;

        //Reaccionar segun la opcion dada
       if (opcion == "1"){opcion1();}
       else if (opcion == "2"){opcion2();}
       else if (opcion == "3"){opcion3();}
       else if (opcion == "4"){p("saliendo....\n");}
       else{p("Seleccione una opción disponible\n");}

    }

}

int main() {

    //Si la lectura se concreta se habilita el menu
    if (read()) {
        menu();
    }

    //Eliminar el sistema
    delete S;

    return 0;
}

