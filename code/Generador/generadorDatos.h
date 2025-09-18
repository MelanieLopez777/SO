#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdlib> 
#include <ctime>  
#include "../Structure/structures.h"

#define MIN_ID 1
#define MAX_ID 1000
#define MIN_TME 6
#define MAX_TME 12 
#define RANGO_OPERANDO_MAX 10000
#define RANGO_OPERANDO_MIN 0

// 🔹 Declaraciones (no definen memoria aquí)
extern Proceso gestor[TAM_PROCESOS];
extern int contadorProcesos;

bool validarID (int &id);
void generarDatos();
void bubbleSort(int cantidadProcesos);
