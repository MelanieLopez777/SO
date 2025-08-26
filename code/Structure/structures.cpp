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


void Proceso::fijaOperacion(int operacion) {
    this->operacion = operacion;
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


int Proceso::dameOperacion() {
    return operacion;
}

Calculadora& Proceso::dameCalculadora() {
    return calculadora;
}


std::string Proceso::toString() const {
return "{nombre: " + nombre +
        ", id: " + std::to_string(id) +
        ", tme: " + std::to_string(tme) +
        ", operacion: " + std::to_string(operacion) +
        ", resultado: " + calculadora.operacionToString(operacion) + " = " + std::to_string(calculadora.dameResultado());
}