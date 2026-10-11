
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
    Paciente(int id, string nombre, int edad, double temperatura, int presionArterial,
        int dolor, string tipoDolor, bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
        int diasHospitalizacion);

    //Getters
    int getId();
    string getNombre();
    int getEdad();
    double getTemperatura();
    int getPresionArterial();
    int getDolor();
    string getTipoDolor();
    bool getTrauma();
    bool getSintomasNeurologicos();
    bool getRequiereCirugia();
    int getDiasHospitalizacion();

    //Destructor
    ~Paciente();

};
