#include "structures.h"

void Proceso::fijaNombre(string nombre) {
    this->nombre = nombre;
}

void Proceso::fijaID(int id) {
    this->id = id;
}

void Proceso::fijaTME(int tme) {
    this->tme = tme;
}


std::string Proceso::dameNombre() const{
    return nombre;
}

int Proceso::dameID() const{
    return id;
}

int Proceso::dameTME() const{
    return tme;
}

Calculadora& Proceso::dameCalculadora() {
    return calculadora;
}


std::string Proceso::toString(int etapa) const {
    switch (etapa)
    {
    case PROCESO:
        return "Nombre: " + nombre + "    TME: " + std::to_string(tme) + "\n";
        break;
    case TERMINADO:
        return "ID: " + std::to_string(id) + "\nOperación: " + calculadora.operacionToString() + "\nResultado: " + std::to_string(calculadora.dameResultado()) + "\n\n";
    default:
        return "{nombre: " + nombre +
        ", id: " + std::to_string(id) +
        ", tme: " + std::to_string(tme) +
        ", resultado: " + calculadora.operacionToString() + " = " + std::to_string(calculadora.dameResultado());
        break;
    }
}