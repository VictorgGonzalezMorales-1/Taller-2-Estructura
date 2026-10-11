
#include "Paciente.h"

//Constructor
Paciente :: Paciente(int id, const string& nombre, int edad, double temperatura, int presionArterial,
        int dolor, const string& tipoDolor, bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
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
int Paciente :: getId() const {return this->id;}
string Paciente :: getNombre() const {return this->nombre;}
int Paciente :: getEdad() const {return this->edad;}
double Paciente :: getTemperatura() const {return this->temperatura;}
int Paciente ::  getPresionArterial() const {return this->presionArterial;}
int Paciente :: getDolor() const {return this->dolor;}
string Paciente :: getTipoDolor() const {return this->tipoDolor;}
bool Paciente :: getTrauma() const {return this->trauma;}
bool Paciente :: getSintomasNeurologicos() const {return this->sintomasNeurologicos;}
bool Paciente :: getRequiereCirugia() const {return this->requiereCirugia;}
int Paciente :: getDiasHospitalizacion() const {return this->diasHospitalizacion;}

//Destructor

Paciente :: ~Paciente() = default;