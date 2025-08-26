#include <iomanip>
#include <iostream>
#include <iomanip>
#include "structures.h"
#include "operations.cpp"
#include "queue/queue.h"

using namespace std;

void ejecutarProcesos(proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos)
{
    int numLotes, lotesPendientes, lotesTerminados, contadorGlobal;
    StaticQueue pendientes, ejecucion, terminado;
    initialize(&pendientes);
    initialize(&ejecucion);
    initialize(&terminado);

    numLotes = cantidadProcesos / 4;
    if((cantidadProcesos % 4) != 0)
    {
        numLotes++;
    }
    lotesPendientes = numLotes - 1;

    for (int i = contadorGlobal; i < 4; i++) {
        enqueue(&pendientes, arregloProcesos[i]);
    }

    cout << "Numero de lotes pendientes: " << lotesPendientes << endl;
    cout << "Lote en ejecución: " << endl;    
    cout << left << setfill('-') << setw(10) << "Pendientes" << setw(10) << "En ejecucion" << setw(10) << "Resultados" << endl;
    for()
    {
        cout << left << setfill('-') << setw(10) << front(&pendientes).nombre << front(&pendientes).tme;
    }
    cout << "Contador Gobal: " << contadorGlobal << endl;

}