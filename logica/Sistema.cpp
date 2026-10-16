
#include "Sistema.h"

//Constructor
Sistema :: Sistema() {
    this->colaPacientes = new Queue<Paciente*>();
    this->arbolDeDesicion = crearArbolDesicion();
    this->idPacientes = new List<string>();
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

        //Convertir los Booleanos o ver si no son posibles
        if (d->get(7) == "1") {trauma = true;}
        else if (d->get(7) == "0"){trauma = false;}
        else{delete d; return;}

        if (d->get(8) == "1") { sintomasNeurologicos = true;}
        else if (d->get(8) == "0"){sintomasNeurologicos = false;}
        else{delete d; return;}

        if (d->get(9) == "1") {requiereCirugia = true;}
        else if (d->get(9) == "0"){requiereCirugia = false;}
        else{delete d; return;}

        //Revisar la naturaleza de los números
        if (id < 0 || edad < 0 || temperatura < 0 || presionArterial < 0 || diasHospitalizacion < 0) {
            delete d;
            return;
        }

        //Revisar la escala de dolor
        if (dolor < 0 || dolor > 10 ) {
            delete d;
            return;
        }

        //Revisar que el tipo de dolor sea una respuesta válida
        if (tipoDolor != "pecho" && tipoDolor != "cabeza" && tipoDolor != "abdomen" &&
            tipoDolor != "extremidad" && tipoDolor != "otro") {
            delete d;
            return;
        }

        //Revisar que el nuevo paciente no repita el ID de otro
        for (int a = 0; a < this->idPacientes->getSize(); a++) {

            //Si encuentra una id igual termina y no guarda el paciente
            if (this->idPacientes->get(a) == d->get(0)) {
                delete d;
                return;
            }

        }

        //Crear al paciente
        Paciente* paciente= new Paciente(id, nombre, edad, temperatura, presionArterial,
            dolor, tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion);

        //Almacenar al paciente creado en la cola
        guardarPacienteEnCola(paciente);

        //Almacenar el id del paciente en la lista
        idPacientes->insertLast(d->get(0));

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
string Sistema :: definirServicio(Paciente* paciente, NodeArbol<string>* nodoActual, string texto) {

    try {

        //Solicitar la pregunta del nodo
        string pregunta = nodoActual->getPregunta();

        //Si no hay pregunta quiere decir que llegamos al nodo que entrega el servicio
        if (pregunta == "") {

            //Acá irá el metodo para guardarlo en le AVL

            texto += "\n\nServicio asignado: " + nodoActual->getValue() + "\n\n";
            return texto;
        }

        //Direccionamiento en caso de la pregunta Sintomas Neurológicos
        if (pregunta == "Sintomas Neurologicos") {

            if (paciente->getSintomasNeurologicos() == true) {
                texto+= "Sintomas Neurologicos = Si-> ";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Sintomas Neurologicos = No-> ";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Presión Arterial
        if (pregunta == "Presión Arterial") {

            if (paciente->getPresionArterial() >= 80  && paciente->getPresionArterial() <= 120) {
                texto+= "Presión Arterial = Normal-> ";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Presión Arterial = Anormal";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Dolor
        if (pregunta == "Dolor") {

            if (paciente->getDolor() < 5) {
                texto+= "Dolor < 5";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Dolor >= 5-> ";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Temperatura
        if (pregunta == "Temperatura") {

            if (paciente->getTemperatura() >= 36 && paciente->getTemperatura() <= 38) {
                texto+= "Temperatura = Normal-> ";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Temperatura = Anormal";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Trauma
        if (pregunta == "Trauma") {

            if (paciente->getTrauma() == true) {
                texto+= "Trauma = Si-> ";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Trauma = No-> ";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Edad
        if (pregunta == "Edad") {

            if (paciente->getEdad() < 15) {
                texto+= "Edad < 15";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Edad >= 15";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Requiere Cirugia
        if (pregunta == "Requiere Cirugia") {

            if (paciente->getRequiereCirugia() == true) {
                texto+= "Requiere Cirugia = Si";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Requiere Cirugia = No";
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

        //Direccionamiento en caso de la pregunta Tipo De Dolor
        if (pregunta == "Tipo De Dolor") {

            if (paciente->getTipoDolor() != "otro") {
                texto+= "Tipo De Dolor = Otro";
                return definirServicio(paciente, nodoActual->getIzquierdo(), texto);
            }
            texto+= "Tipo De Dolor = " + paciente->getTipoDolor();
            return definirServicio(paciente, nodoActual->getDerecho(), texto);
        }

    }catch (...) {
        //Si no se logra conseguir un servicio el cual lo pueda atender de buena manera
        //se envia a Medicina General de Defaul
        texto = "Datos inconsistentes \n\nServicio asignado: Medicina General";
        return texto;
    }

    texto = "Datos inconsistentes \n\nServicio asignado: Medicina General";
    return texto;
}

//Metodo generado para atender a los n pacientes solicitados
//Incompleto
string Sistema :: atenderPacientes(int n) {

    //Si no hay pacientes termina
    if (this->colaPacientes->isEmpty()) {
        return "No hay pacientes en la cola";
    }

    //Si se piden más pacientes de los que hay solo se procesas los maximos que hay
    if (n > this->colaPacientes->size()) {
        n = this->colaPacientes->size();
    }

    //Procesar los datos
    string texto = "\n=== ATENDIENDO PACIENTES ===\n\n";

    for (int a = 0; a < n; a++) {

        texto += "-----------------------------------------\n";
        texto+= colaPacientes->front()->toString() + "\n\n";

        string resultado = definirServicio(colaPacientes->front(), this->arbolDeDesicion, "");
        texto += "Ruta: " + resultado + "\n";

        colaPacientes->pop();

    }

    texto += "-----------------------------------------\n";
    return texto;

}

//Destructor
Sistema::~Sistema() {
    delete this->colaPacientes;
    delete this->arbolDeDesicion;
}