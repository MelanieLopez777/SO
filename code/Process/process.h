#pragma once
#include <iostream>
#include <iomanip>
#include "../Structure/structures.h"
#include "../Calc/operations.h"
#include "../Queue/queue.h"

using namespace std;

void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos);