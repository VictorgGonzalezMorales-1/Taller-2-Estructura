
#pragma once

#include <string>
using namespace std;

class Paciente {

// Atributos
private:
    int id;
    string nombre;
    int edad;
    double temperatura;
    int presionArterial;
    int dolor;
    string tipoDolor;
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;

public:

    //Constructor
    Paciente(int id, const string& nombre, int edad, double temperatura, int presionArterial,
        int dolor, const string& tipoDolor, bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
        int diasHospitalizacion);

    //Getters
    int getId() const;
    string getNombre() const;
    int getEdad() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    string getTipoDolor() const;
    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;

    //Métodos
    string toString() const;

    //Sobrecarga de Operadores

    bool operator < (const Paciente& comparar) const;
    bool operator > (const Paciente& comparar) const;

    //Destructor
    ~Paciente();

};
