
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Metodo para imprimir rapidamente
static void p(const string& t) {cout << t << endl;}

//Metodo para leer el archivo
static bool read() {

    //Cargar el archivo
    ifstream archivo("Pacientes.txt");

    //Si el archivo no está termina la lectura y no permite abrir el menu
    if (!archivo.is_open()) {
        p("No se puede cargar el archivo");
        return false;
    }

    //Variable para almacenar la linea
    string linea;

    //Bucle para leer las líneas del archivo
    while (getline(archivo, linea)) {

    }

    return true;
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
       if (opcion == "1"){p("1\n");}
       else if (opcion == "2"){p("2\n");}
       else if (opcion == "3"){p("3\n");}
       else if (opcion == "4"){p("saliendo....\n");}
       else{p("Seleccione una opción disponible\n");}

    }

}

int main() {

    //Si la lectura se concreta se habilita el menu
    if (read()) {
        menu();
    }

    return 0;
}

