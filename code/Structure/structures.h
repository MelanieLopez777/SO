#pragma once
#include <string>
#include "../Calc/operations.h"

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
    int tme;
    int tiempoTotal;
    Calculadora calculadora;
    int numeroLote;

public:
    void fijaID(int id);
    void fijaTME(int tme);
    void fijaTT(int tiempoTotal);
    void fijaNumeroLote(int numeroLote);
    int dameID() const;
    int dameTME() const;
    int dameTT() const;
    int dameNumeroLote() const;
    Calculadora& dameCalculadora();
    std::string toString(int etapa) const;
};
