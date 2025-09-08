#include <iostream>
#include <stdexcept>
#include <limits>
#include "Calc/operations.h"
#include "Structure/structures.h"
#include "Process/process.h"

using namespace std;

Proceso gestor[TAM_PROCESOS];
int contadorProcesos;

void pedirDatos();
bool validarID(int &id);

int main(){
    int cantidadProcesos;
    cout << "Dame la cantidad de procesos a ingresar: ";
    cin >> cantidadProcesos;
    for(int i = 0; i < cantidadProcesos; i++)
    {   
        pedirDatos();
        system(CLEAR);
    }


    ejecutarProcesos(gestor, cantidadProcesos);
    return 0;
}


void pedirDatos()
{
    string nombre;
    int operacion, tme, tempID;
    float valorA, valorB;
    Calculadora *tempCalc;

    // Nombre
    cout << "Nombre del usuario[" << (contadorProcesos+1) << "]: ";
    cin >> nombre; 
    gestor[contadorProcesos].fijaNombre(nombre);

    tempCalc = &gestor[contadorProcesos].dameCalculadora();
    // Operador
    do {
        cout << tempCalc->mostrarMenuOperaciones();
        while (!(cin >> operacion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Dame un número entre 1 al 6: ";
        }
    } while (operacion < 1 || operacion > 6);
    tempCalc->fijaOperador(operacion);

    // Valores operandos


    cout << "Dame el valor de a = ";
    while (!(cin >> valorA)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Dame un número para a = ";
    }

    if (tempCalc->dameOperador() == RESIDUO || tempCalc->dameOperador() == DIVISION) {
        do {
            cout << "El 0 no es numero valido. Dame el valor de b = ";
            while (!(cin >> valorB)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Dame un número para b = ";
            }
        } while (valorB == 0);
    }
    else if (tempCalc->dameOperador() == POTENCIA) {
        do {
            cout << "Dame el valor de b (debe ser positivo) = ";
            while (!(cin >> valorB)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Dame un número para b = ";
            }
        } while (valorB < 0);
    }
    else {
        cout << "Dame el valor de b = ";
        while (!(cin >> valorB)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Dame un número para b = ";
        }
    }
    tempCalc->fijaValorA(valorA);
    tempCalc->fijaValorB(valorB);

    // TME
    while (true) {
        cout << "Tiempo máximo estimado (TME) proceso[" << (contadorProcesos+1) << "]: ";
        cin >> tme;

        if (cin.fail()) {
            cerr << "Error: no ingresaste un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // vuelve a pedir
        }

        gestor[contadorProcesos].fijaTME(tme);

        if (gestor[contadorProcesos].dameTME() <= 0) {
            cerr << "Error: El TME debe ser mayor a 0." << endl;
            continue;
        }

        break; // si pasa las validaciones, sale del while
    }

    // ID
    while (true) {
        cout << "ID del proceso [" << (contadorProcesos+1) << "]: ";
        cin >> tempID;

        if (cin.fail()) {
            cerr << "Error: no ingresaste un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (!validarID(tempID)) {
            cerr << "Error: El ID ya existe, ingresa otro." << endl;
            continue;
        }

        gestor[contadorProcesos].fijaID(tempID);
        break; // todo bien, salimos
    }


    cout << endl;
    cin.get();
    contadorProcesos++;
}


bool validarID(int &id)
{
    for (int i = 0; i < contadorProcesos; i++)  
    {
        if (id == gestor[i].dameID())
        {
            cout << "Número de identificación repetido" << endl;
            return false; 
        }
    }
    return true; 
}


