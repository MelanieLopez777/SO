#include "structures.h"
#include <string>


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
    switch (etapa)
    {
    case PROCESO:
        return "ID: " + std::to_string(id) + " TME: " + std::to_string(reloj.getEstimatedTimeAmount()) + " T.Trans: " + std::to_string(reloj.getElapsedTime()) +"\n";
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
        ", tme: " + std::to_string(reloj.getEstimatedTimeAmount()) +
        ", resultado: " + calculadora.operacionToString() + " = " + std::to_string(calculadora.dameResultado());
        break;
    }
}