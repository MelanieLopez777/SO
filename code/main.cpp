#include <iostream>
#include <stdexcept>
#include <limits>
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
    }
    ejecutarProcesos(gestor, cantidadProcesos);
    return 0;
}


void pedirDatos()
{
    string nombre;
    int operacion, tme, tempID;
    cin.exceptions(ios::failbit | ios::badbit);

    // Nombre
    cout << "Nombre del usuario[" << (contadorProcesos+1) << "]: ";
    cin >> nombre; 
    gestor[contadorProcesos].fijaNombre(nombre);

    // Operador
    cout << gestor[contadorProcesos].dameCalculadora().mostrarMenuOperaciones();
    cin >> operacion; 
    gestor[contadorProcesos].fijaOperacion(operacion);

    // Valores operandos
    gestor[contadorProcesos].dameCalculadora().pedirValores();

    // TME
    while (true) {
        try {
            cout << "Tiempo máximo estimado (TME) proceso[" << (contadorProcesos+1) << "]: ";
            cin >> tme;
            gestor[contadorProcesos].fijaTME(tme);

            if (gestor[contadorProcesos].dameTME() <= 0) {
                throw invalid_argument("El TME debe ser mayor a 0.");
            }
            break; 
        } catch (const ios_base::failure &e) {
            cerr << "Error: no ingresaste un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const invalid_argument &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    // ID
    while (true) {
        try {
            
            cout << "ID del proceso [" << (contadorProcesos+1) << "]: ";
            cin >> tempID;

            if (!validarID(tempID)) {
                throw invalid_argument("El ID ya existe, ingresa otro.");
            }

        gestor[contadorProcesos].fijaID(tempID);
        break; 
    } catch (const ios_base::failure &e) {
        cerr << "Error: no ingresaste un número válido." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } catch (const invalid_argument &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

    cout << endl;
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


