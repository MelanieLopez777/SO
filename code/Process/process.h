#pragma once
#include <limits>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "../Structure/structures.h"
#include "../Calc/operations.h"
#include "../Queue/queue.h"

using namespace std;

vector<string> splitLines(const string &s);
void printTableRow(const string &pendienteStr, const string &ejecucionStr, const string &resultadoStr, int colWidth);
void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos);