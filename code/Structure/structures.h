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
    std::string nombre;
    int id;
    int tme;
    Calculadora calculadora;
    int numeroLote;

public:
    void fijaNombre(string nombre);
    void fijaID(int id);
    void fijaTME(int tme);
    void fijaNumeroLote(int numeroLote);
    std::string dameNombre() const;
    int dameID() const;
    int dameTME() const;
    int dameNumeroLote() const;
    Calculadora& dameCalculadora();
    std::string toString(int etapa) const;
};
