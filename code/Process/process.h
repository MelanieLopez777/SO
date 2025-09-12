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
    int lotesPendientes, 
    int loteEnEjecucion, 
    int contadorGlobal, 
    string &pendienteStr, 
    string &ejecucionStr, 
    string &resultadoStr, 
    StaticQueue &pendientes, 
    Proceso *ejecucion, 
    StaticQueue &terminado, 
    int tiempoEjecucion, 
    int tiempoRestante, 
    int colWidth);
void actualizarInformacion(
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    StaticQueue &pendientes, 
    Proceso *ejecucion, 
    StaticQueue &terminado, 
    int tiempoEjecucion, 
    int tiempoRestante);
void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos);