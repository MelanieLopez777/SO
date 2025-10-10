#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include "../Structure/structures.h"

#define MIN_ID 1
#define MAX_ID 1000
#define MIN_TME 6
#define MAX_TME 12 
#define RANGO_OPERANDO_MAX 100
#define RANGO_OPERANDO_MIN 0

extern vector<Proceso> gestor;

bool validarID (int &id);
Proceso generarDatos();
void bubbleSort();
