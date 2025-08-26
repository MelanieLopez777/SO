#include "process.h"

void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos)
{
    int numLotes, lotesPendientes, lotesTerminados, contadorGlobal;
    int aux;
    StaticQueue pendientes, ejecucion, terminado;

    numLotes = cantidadProcesos / 4;
    if((cantidadProcesos % 4) != 0)
    {
        numLotes++;
    }
    lotesPendientes = numLotes - 1;

    contadorGlobal = 0;
    for (int i = contadorGlobal; i < 4; i++) {
        pendientes.enqueue(arregloProcesos[i]);
        cout << "Proceso #" << i << ": " << arregloProcesos[i].toString() << endl;
    }

    cout << "Numero de lotes pendientes: " << lotesPendientes << endl;
    cout << "Lote en ejecución: " << endl;    
    cout << left << setfill('-') << setw(10) << "Pendientes" << setw(10) << "En ejecucion" << setw(10) << "Resultados" << endl;
    aux = 4;
    for(int i = 0; i < aux; i++)
    {
        cout << left << setfill('-') << setw(10) << pendientes.getFront().dameNombre() << pendientes.getFront().dameTME();
        pendientes.dequeue();
    }
    cout << "Contador Gobal: " << contadorGlobal << endl;

}