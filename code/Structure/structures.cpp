#include "structures.h"
#include <string>
#include <iomanip>

void Proceso::fijaID(int id) 
{
        this->id = id;
}

void Proceso::fijaNumeroLote(int numeroLote)
{
    this->numeroLote = numeroLote;
}

int Proceso::dameID() const
{
    return id;
}

int Proceso::dameNumeroLote() const
{
    return this->numeroLote;
}

Calculadora& Proceso::dameCalculadora()
{
    return calculadora;
}

Clock& Proceso::dameReloj()
{
    return reloj;
}

std::string Proceso::toString(int etapa) const {
    std::ostringstream oss; 

    switch (etapa) {
    case PROCESO:
        oss << "ID: " << std::setw(4) << std::left << id   
            << "TME: " << std::setw(4) << std::left << reloj.getEstimatedTimeAmount()
            << "T.Trans: " << std::setw(4) << std::left << reloj.getElapsedTime()
            << "\n";
        return oss.str();

    case TERMINADO:
        oss << "ID: " << id
            << "\nOperación: " << calculadora.operacionToString()
            << "\nResultado: "
            << ((calculadora.dameResultado() == std::numeric_limits<float>::lowest())
                ? "ERROR"
                : std::to_string(calculadora.dameResultado()))
            << "\n#Lote: " << dameNumeroLote() << "\n\n";
        return oss.str();

    default:
        oss << "{id: " << id
            << ", tme: " << reloj.getEstimatedTimeAmount()
            << ", resultado: " << calculadora.operacionToString()
            << " = " << calculadora.dameResultado();
        return oss.str();
    }
}
