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
#include "../Generador/generadorDatos.h"
#include "../Structure/structures.h"
#include "../Calc/operations.h"
#include "../Queue/queue.h"

using namespace std;

vector<string> splitLines(const string &s);
void printTableRow(const string &pendienteStr, const string &ejecucionStr, const string &resultadoStr, int colWidth);
void actualizarInformacion(
    string &nuevosString,
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    string &bloqueadosString,
    StaticQueue<Proceso> &nuevos,
    StaticQueue<Proceso> &pendientes, 
    Proceso *ejecucion, 
    StaticQueue<Proceso> &terminado,
    StaticQueue<Proceso> &bloqueados);
void imprimirTablaResultados(
    int contadorGlobal,
    string &nuevosStr,
    string &pendienteStr,
    string &ejecucionStr,
    string &resultadoStr,
    string &bloqueadosStr,
    StaticQueue<Proceso> &nuevos,
    StaticQueue<Proceso> &pendientes,
    Proceso *ejecucion,
    StaticQueue<Proceso> &terminado,
    StaticQueue<Proceso> &bloqueados,
    int colWidth);

void imprimirTablaBCP(vector<Proceso>& arregloProcesos, int cantidadProcesos);
void ejecutarProcesos(vector<Proceso>& arregloProcesos, int cantidadProcesos);