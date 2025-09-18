#pragma once
#include <string>
#include "../Calc/operations.h"
#include "../Clock/clock.h"

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(_unix) || defined(APPLE) || defined(MACH_)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

#define TAM_PROCESOS 16

enum etapasEnum {PROCESO, TERMINADO};

class Proceso {

private:
    int id;
    Calculadora calculadora;
    Clock reloj;
    int numeroLote;

public:
    void fijaID(int id);
    void fijaNumeroLote(int numeroLote);
    int dameID() const;
    int dameNumeroLote() const;
    Calculadora& dameCalculadora();
    Clock& dameReloj();
    std::string toString(int etapa) const;
};
