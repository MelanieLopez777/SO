#include <iostream>

#include "Calc/operations.h"
#include "Process/process.h"
#include "Generador/generadorDatos.h"

using namespace std;


int main(){
    int cantidadProcesos;
    cout << "Dame la cantidad de procesos a ingresar: ";
    cin >> cantidadProcesos;
    for(int i = 0; i < cantidadProcesos; i++)
    {   
        generarDatos();
        system(CLEAR);
    }

    bubbleSort(cantidadProcesos);
    ejecutarProcesos(gestor, cantidadProcesos);
    return 0;
}
