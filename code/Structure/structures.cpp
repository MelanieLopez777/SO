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


std::string Proceso::toString(int etapa) const {
    switch (etapa)
    {
    case PROCESO:
        return "Nombre: " + nombre + "    TME: " + std::to_string(tme);
        break;
    case TERMINADO:
        return "ID " + std::to_string(id) + "\nOperación: " + calculadora.operacionToString(operacion) + "\nResultado: " + std::to_string(calculadora.dameResultado()) + "\n";
    default:
        return "{nombre: " + nombre +
        ", id: " + std::to_string(id) +
        ", tme: " + std::to_string(tme) +
        ", operacion: " + std::to_string(operacion) +
        ", resultado: " + calculadora.operacionToString(operacion) + " = " + std::to_string(calculadora.dameResultado());
        break;
    }
}

// g++ main.cpp Structure\structures.cpp Calc\operations.cpp Process\process.cpp Queue\queue.cpp -o ejecutable.exe