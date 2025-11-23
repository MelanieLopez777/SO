#include "structures.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

void Proceso::fijaID(int id) {
    this->id = id;
}

void Proceso::fijaNumeroLote(int numeroLote) {
    this->numeroLote = numeroLote;
}


void Proceso::fijaEstado(estadoProceso nuevoEstado) {
    this->estado = nuevoEstado; 
}

int Proceso::dameID() const {
    return id;
}

void Proceso::fijaTamanio(int tamanio) {
    this->tamanio = tamanio; 
}

int Proceso::dameNumeroLote() const {
    return this->numeroLote;
}

Calculadora& Proceso::dameCalculadora() {
    return calculadora;
}

Clock& Proceso::dameReloj() {
    return reloj;
}

int Proceso::dameTamanio() const {
    return tamanio;
}

estadoProceso Proceso::dameEstado() const { 
    return estado; 
}

std::string Proceso::toString(estadoProceso etapa) const {
    std::ostringstream oss;

    switch (etapa) {
    case estadoProceso::NUEVO:
        oss << "ID: " << this->id;
        break;

    case estadoProceso::LISTO:
        oss << "ID: " << this->id << "   "
            << "TME: " << this->reloj.getEstimatedTimeAmount() << "   "
            << "TT: " << this->reloj.getElapsedTime();
        break;

    case estadoProceso::EJECUCION:
        oss << "ID: " << this->id <<"\n"
            << "Op: " << this->calculadora.operacionToString() << "\n"
            << "TME: " << this->reloj.getEstimatedTimeAmount() << "\n"
            << "TT: " << this->reloj.getElapsedTime() <<"\n"
            << "TR: " << (this->reloj.getEstimatedTimeAmount() - this->reloj.getElapsedTime());
        break;

    case estadoProceso::BLOQUEADO:
        oss << "ID: " << this->id <<"     ";
        oss << "TB: " <<this->reloj.getBlockedTime();
        break;

    case estadoProceso::TERMINADO:
        oss << "ID: " << this->id << "  "
            << "Op: " << this->calculadora.operacionToString() << "  "
            << "Res: "
            << ((this->calculadora.dameResultado() == std::numeric_limits<float>::lowest())
                ? "ERROR"
                : std::to_string(this->calculadora.dameResultado()));
        break;
    }
    return oss.str();
}