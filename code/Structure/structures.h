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

//Definición de los cinco estados del proceso
enum class estadoProceso {
    NUEVO,
    LISTO,
    EJECUCION,
    BLOQUEADO,
    TERMINADO
};

class Proceso {

private:
    Calculadora calculadora;
    Clock reloj;
    estadoProceso estado;
    int numeroLote;
    int id;

public:

    Proceso() : estado(estadoProceso::NUEVO), numeroLote(0), id(-1) {}

    void fijaID(int id);
    void fijaNumeroLote(int numeroLote);
    void fijaEstado (estadoProceso nuevoEstado);
    int dameID() const;
    int dameNumeroLote() const;
    Calculadora& dameCalculadora();
    Clock& dameReloj();
    estadoProceso dameEstado() const;
    std::string toString(estadoProceso etapa) const;
};
