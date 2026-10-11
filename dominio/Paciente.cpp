
#include "Paciente.h"

//Constructor
Paciente :: Paciente(string id, string nombre, int edad, double temperatura, int presionArterial,
        int dolor, string tipoDolor, bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
        int diasHospitalizacion) {

        this->id = id;
        this->nombre = nombre;
        this->edad = edad;
        this->temperatura = temperatura;
        this->presionArterial = presionArterial;
        this->dolor = dolor;
        this->tipoDolor = tipoDolor;
        this->trauma = trauma;
        this->sintomasNeurologicos = sintomasNeurologicos;
        this->requiereCirugia = requiereCirugia;
        this->diasHospitalizacion = diasHospitalizacion;
}

//Getters
string Paciente :: getId() {return this->id;}
string Paciente :: getNombre(){return this->nombre;}
int Paciente :: getEdad(){return this->edad;}
double Paciente :: getTemperatura(){return this->temperatura;}
int Paciente ::  getPresionArterial(){return this->presionArterial;}
int Paciente :: getDolor(){return this->dolor;}
string Paciente :: getTipoDolor(){return this->tipoDolor;}
bool Paciente :: getTrauma(){return this->trauma;}
bool Paciente :: getSintomasNeurologicos(){return this->sintomasNeurologicos;}
bool Paciente :: getRequiereCirugia(){return this->requiereCirugia;}
int Paciente :: getDiasHospitalizacion(){return this->diasHospitalizacion;}

//Destructor

Paciente :: ~Paciente(){};