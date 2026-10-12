
#include "Sistema.h"

//Constructor
Sistema :: Sistema() {
    this->colaPacientes = new Queue<Paciente*>();
    this->arbolDeDesicion = crearArbolDesicion();
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

//Metodo el cual generara un arbol de decisión para cada paciente con el cual se podra
//definir a que servicio se debe enviar
NodeArbol<string>* Sistema :: crearArbolDesicion() {

    //Ramas del arbol
    NodeArbol<string>* urgencias = new NodeArbol<string>("Urgencias");
    NodeArbol<string>* medicinaGeneral = new NodeArbol<string>("Medicina General");
    NodeArbol<string>* cardiología = new NodeArbol<string>("Cardiología");
    NodeArbol<string>* neurología = new NodeArbol<string>("Neurología");
    NodeArbol<string>* traumatología = new NodeArbol<string>("Traumatología");
    NodeArbol<string>* cirugía = new NodeArbol<string>("Cirugía");
    NodeArbol<string>* pediatría = new NodeArbol<string>("Pediatría");
    NodeArbol<string>* hospitalización = new NodeArbol<string>("Hospitalización");

    //Conecciones entre las ramas y preguntas de la izquierda

    //Conección de la pregunta edad
    NodeArbol<string>* edad = new NodeArbol<string>("");
    edad->setPregunta("Edad");
    edad->setIzquierda(pediatría);  //Menor que 15
    edad->setDerecha(neurología);   //Mayor o igual que 15

    //Conección de la pregunta Temperatura
    NodeArbol<string>* temperatura = new NodeArbol<string>("");
    temperatura->setPregunta("Temperatura");
    temperatura->setIzquierda(edad);   //Entre 36 y 38
    temperatura->setDerecha(urgencias);    //Menor que 36 y Mayor que 38

    //Conección de la pregunta Presión Arterial
    NodeArbol<string>* presionArterial = new NodeArbol<string>("");
    presionArterial->setPregunta("Presión Arterial");
    presionArterial->setIzquierda(temperatura);   //Entre 80 y 120
    presionArterial->setDerecha(cardiología);   // Meno que 80 y mayor que 120

    //Conecciones entre las ramas y preguntas de la derecha

    //Conección de la pregunta Requiere Cirujía
    NodeArbol<string>* requiereCirugia = new NodeArbol<string>("");
    requiereCirugia->setPregunta("Requiere Cirugia");
    requiereCirugia->setIzquierda(cirugía);  //Si
    requiereCirugia->setDerecha(traumatología);  //No

    //Conección de la pregunta Tipo de Dolor
    NodeArbol<string>* tipoDeDolor = new NodeArbol<string>("");
    tipoDeDolor->setPregunta("Tipo De Dolor");
    tipoDeDolor->setIzquierda(hospitalización);  // pecho, cabeza, abdomen, extremidad
    tipoDeDolor->setDerecha(urgencias);  //Otro

    //Conección de la pregunta trauma
    NodeArbol<string>* trauma = new NodeArbol<string>("");
    trauma->setPregunta("Trauma");
    trauma->setIzquierda(requiereCirugia);  //Si
    trauma->setDerecha(tipoDeDolor);

    //Conección de la pregunta dolor
    NodeArbol<string>* dolor = new NodeArbol<string>("");
    dolor->setPregunta("Dolor");
    dolor->setIzquierda(medicinaGeneral);  // Menor que 5
    dolor->setDerecha(trauma); // Mayor o igual que 5

    //Conección izquieda y derecha con la raíz

    //Conección de la pregunta Sintomas Neurológicos
    NodeArbol<string>* sintomasNeurologicos = new NodeArbol<string>("");
    sintomasNeurologicos->setPregunta("Sintomas Neurologicos");
    sintomasNeurologicos->setIzquierda(presionArterial);  //Si
    sintomasNeurologicos->setDerecha(dolor);  //No

    return sintomasNeurologicos;

}

//Metodo generado para que segun el paciente que se le entregue este defina
//a que sector será enviado
string Sistema :: definirServicio(Paciente* paciente, NodeArbol<string>* nodoActual) {

    try {

        //Solicitar la pregunta del nodo
        string pregunta = nodoActual->getPregunta();

        //Si no hay pregunta quiere decir que llegamos al nodo que entrega el servicio
        if (pregunta == "") {
            return nodoActual->getValue();
        }

        //Direccionamiento en caso de la pregunta Sintomas Neurológicos
        if (pregunta == "Sintomas Neurologicos") {

            if (paciente->getSintomasNeurologicos() == true) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Presión Arterial
        if (pregunta == "Presión Arterial") {

            if (paciente->getPresionArterial() >= 80  && paciente->getPresionArterial() <= 120) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Dolor
        if (pregunta == "Dolor") {

            if (paciente->getDolor() < 5) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Temperatura
        if (pregunta == "Temperatura") {

            if (paciente->getTemperatura() >= 36 && paciente->getTemperatura() <= 38) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Trauma
        if (pregunta == "Trauma") {

            if (paciente->getTrauma() == true) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Edad
        if (pregunta == "Edad") {

            if (paciente->getEdad() < 15) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Requiere Cirugia
        if (pregunta == "Requiere Cirugia") {

            if (paciente->getRequiereCirugia() == true) {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

        //Direccionamiento en caso de la pregunta Tipo De Dolor
        if (pregunta == "Tipo De Dolor") {

            if (paciente->getTipoDolor() != "otro") {
                return definirServicio(paciente, nodoActual->getIzquierdo());
            }
            return definirServicio(paciente, nodoActual->getDerecho());
        }

    }catch (...) {
        //Si no se logra conseguir un servicio el cual lo pueda atender de buena manera
        //se envia a Medicina General de Defaul
        return "Medicina General";
    }

    return "Medicina General";
}

//Destructor
Sistema::~Sistema() {
    delete this->colaPacientes;
    delete this->arbolDeDesicion;
}