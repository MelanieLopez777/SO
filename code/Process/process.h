#pragma once
#include <limits>
#include <iomanip>
#include <vector>
#include <sstream>
#include <iostream>
#include <conio.h> 
#include <thread>
#include <chrono>
#include <algorithm>
#include "../Structure/structures.h"
#include "../Calc/operations.h"
#include "../Queue/queue.h"

using namespace std;

vector<string> splitLines(const string &s);
void printTableRow(const string &pendienteStr, const string &ejecucionStr, const string &resultadoStr, int colWidth);
void imprimirTablaResultados(
    int contadorGlobal,
    string &nuevosStr,
    string &pendienteStr,
    string &ejecucionStr,
    string &resultadoStr,
    string &bloqueadosStr,
    StaticQueue &nuevos,
    StaticQueue &pendientes,
    Proceso *ejecucion,
    StaticQueue &terminado,
    StaticQueue &bloqueados,
    int colWidth);
void actualizarInformacion(
    string &nuevosString,
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    string &bloqueadosString,
    StaticQueue &nuevos,
    StaticQueue &pendientes, 
    Proceso *ejecucion, 
    StaticQueue &terminado,
    StaticQueue &bloqueados);
void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos);