#include <iostream>

#include "Calc/operations.h"
#include "Process/process.h"
#include "Generador/generadorDatos.h"

using namespace std;


int main(){
    int cantidadProcesos;

    srand(time(0));

    cout << "Dame la cantidad de procesos inicial: ";
    cin >> cantidadProcesos;
    for(int i = 0; i < cantidadProcesos; i++)
    {   
        gestor.push_back(generarDatos());
        system(CLEAR);
    }

    bubbleSort();
    ejecutarProcesos(gestor, cantidadProcesos);
    return 0;
}
