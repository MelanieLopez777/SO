#include <iostream>

#include "Calc/operations.h"
#include "Process/process.h"
#include "Generador/generadorDatos.h"

using namespace std;


int main(){
    int cantidadProcesos, quantum;

    srand(time(0));

    cout << "Dame la cantidad de procesos inicial: ";
    cin >> cantidadProcesos;
    cout << endl << "Dame el tamanio del quantum: ";
    cin >> quantum;
    for(int i = 0; i < cantidadProcesos; i++)
    {   
        gestor.push_back(generarDatos());
        system(CLEAR);
    }

    bubbleSort();
    ejecutarProcesos(gestor, cantidadProcesos, quantum);
    return 0;
}
