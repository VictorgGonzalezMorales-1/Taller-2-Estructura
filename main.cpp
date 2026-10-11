
#include <iostream>
#include <string>
using namespace std;

//Metodo para imprimir rapidamente
static void p(const string& t) {cout << t << endl;}

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

    menu();

    return 0;
}

