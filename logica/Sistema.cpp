
#include "Sistema.h"

//Constructor
Sistema :: Sistema() {
    this->colaPacientes = new Queue<Paciente*>();
};

List<string>* Sistema :: split(const string& t, char separador) {

    //Lista para almacenar las partes de la linea de texto
    List<string>* lista = new List<string>();

    //Variable para almacenar la palabra
    string texto = "";

    //Bucle para recorrer el texto
    for (char c: t) {

        //Si llegamos al separador guardamos lo que teniamos antes y borramos el texto
        if (c == separador) {
            lista->insertLast(texto);
            texto = "";
        }
        else {
            texto += c;
        }

    }

    //Guardar el último texto que quedó al aire
    lista->insertLast(texto);

    return lista;

}

void Sistema :: crearPaciente(const string& linea) {

    //Lista la cual poseerá los valores del paciente
    List<string>* d = split(linea,';');

    if (d->getSize() != 11) {
        delete d;
        return;
    }

    //Convertir los parámetros a su valor correspondiente, si no se puede los datos están mal
    //y no se crea al paciente
    try {

        // Texto
        string nombre = d->get(1);
        string tipoDolor = d->get(6);

        // Numéricos
        int id = stoi(d->get(0));
        int edad = stoi(d->get(2));
        double temperatura = stod(d->get(3));
        int presionArterial = stoi(d->get(4));
        int dolor = stoi(d->get(5));
        int diasHospitalizacion = stoi(d->get(10));

        // Booleanos
        bool trauma;
        bool sintomasNeurologicos;
        bool requiereCirugia;

        if (d->get(7) == "1") {trauma = true;}
        else if (d->get(7) == "0"){trauma = false;}

        if (d->get(8) == "1") { sintomasNeurologicos = true;}
        else if (d->get(8) == "0"){sintomasNeurologicos = false;}

        if (d->get(9) == "1") {requiereCirugia = true;}
        else if (d->get(9) == "0"){requiereCirugia = false;}

        //Crear al paciente
        Paciente* paciente= new Paciente(id, nombre, edad, temperatura, presionArterial,
            dolor, tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion);

        //Almacenar al paciente creado en la cola
        guardarPacienteEnCola(paciente);
        delete d;

    }catch (...) {
        delete d;
    }

}

void Sistema :: guardarPacienteEnCola(Paciente* paciente) {

    if (paciente != nullptr) {
        colaPacientes->push(paciente);
    }

}

//Destructor
Sistema::~Sistema() {
    delete this->colaPacientes;
}