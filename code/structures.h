#pragma once
#include <string>

#define TAM_PROCESOS 16

typedef struct {

    std::string nombre;
    int id;
    int tme;
    int resultado;
    int operacion;

} proceso;