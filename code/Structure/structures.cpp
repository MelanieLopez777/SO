#include "structures.h"
#include <string>


void Proceso::fijaID(int id) {
    this->id = id;
}

void Proceso::fijaTME(int tme) {
    this->tme = tme;
}

void Proceso::fijaTT(int tiempoTotal) {
    this->tiempoTotal = tiempoTotal;
}

void Proceso::fijaNumeroLote(int numeroLote)
{
    this->numeroLote = numeroLote;
}

int Proceso::dameID() const{
    return id;
}

int Proceso::dameTME() const{
    return tme;
}

int Proceso::dameTT() const{
    return tiempoTotal;
}

int Proceso::dameNumeroLote() const
{
    return this->numeroLote;
}

Calculadora& Proceso::dameCalculadora() {
    return calculadora;
}


std::string Proceso::toString(int etapa) const {
    switch (etapa)
    {
    case PROCESO:
        return "ID: " + std::to_string(id) + " TME: " + std::to_string(tme) + "\n";
        break;
    case TERMINADO:
       return "ID: " + std::to_string(id) +
       "\nOperación: " + calculadora.operacionToString() +
       "\nResultado: " + ((calculadora.dameResultado() == std::numeric_limits<float>::lowest())
                          ? "ERROR"
                          : std::to_string(calculadora.dameResultado())) +
       "\n#Lote: " + std::to_string(dameNumeroLote()) + "\n\n";

    default:
        return "{id: " + std::to_string(id) +
        ", tme: " + std::to_string(tme) +
        ", resultado: " + calculadora.operacionToString() + " = " + std::to_string(calculadora.dameResultado());
        break;
    }
}