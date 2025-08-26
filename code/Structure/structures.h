#pragma once
#include <string>
#include "../Calc/operations.h"

#define TAM_PROCESOS 16

class Proceso {

private:
    std::string nombre;
    int id;
    int tme;
    int operacion;
    Calculadora calculadora;

public:
    void fijaNombre(string nombre);
    void fijaID(int id);
    void fijaTME(int tme);
    void fijaOperacion(int operacion);
    std::string dameNombre() const;
    int dameID() const;
    int dameTME() const;
    int dameOperacion();
    Calculadora& dameCalculadora();
    std::string toString() const;
};
