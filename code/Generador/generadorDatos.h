#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <deque>
#include <QDebug>
#include "../Structure/structures.h"

#define MIN_ID 1
#define MAX_ID 1000
#define MIN_TME 6
#define MAX_TME 12
#define MIN_TAM_PROCESS 6
#define MAX_TAM_PROCESS 30
#define RANGO_OPERANDO_MAX 100
#define RANGO_OPERANDO_MIN 0

bool validarID (int id, const deque<Proceso>& gestor);
Proceso generarDatos(const deque<Proceso>& gestor);
void bubbleSort(deque<Proceso>& gestor);