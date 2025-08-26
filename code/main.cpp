#include <iostream>
#include <stdexcept>
#include <limits>
#include "structures.h"
#include "process.cpp"


#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(_unix) || defined(APPLE) || defined(MACH_)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace std;


proceso usuario[TAM_PROCESOS];
int contadorProcesos;

void mostrarMenu();
void pedirDatos();
bool validarID(int &id);

int main(){
    int cantidadProceso;
    cout << "Dame la cantidad de procesos a ingresar: ";
    cin >> cantidadProceso;
    pedirDatos();
    ejecutarProcesos(usuario, cantidadProceso);
    return 0;
}


void pedirDatos(int &cantidadProceso)
{
    if (contadorProcesos >= cantidadProceso) {
        cout << " No se pueden registrar más procesos. Límite alcanzado." << endl;
        return;
    }

    cin.exceptions(ios::failbit | ios::badbit);

    cout << "Nombre del usuario[" << (contadorProcesos+1) << "]: ";
    cin >> usuario[contadorProcesos].nombre;

    mostrarMenu();
    cin >> usuario[contadorProcesos].operacion;

    // Pedir TME
    while (true) {
        try {
            cout << "Tiempo máximo estimado (TME) usuario[" << (contadorProcesos+1) << "]: ";
            cin >> usuario[contadorProcesos].tme;

            if (usuario[contadorProcesos].tme <= 0) {
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

    // Pedir ID
    while (true) {
        try {
            int tempID; // 🔹 variable temporal
            cout << "ID del proceso del usuario[" << (contadorProcesos+1) << "]: ";
            cin >> tempID;

            if (!validarID(tempID)) {
                throw invalid_argument("El ID ya existe, ingresa otro.");
            }

        usuario[contadorProcesos].id = tempID; // ✅ se asigna solo si es válido
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
        if (id == usuario[i].id)
        {
            cout << "Número de identificación repetido" << endl;
            return false; 
        }
    }
    return true; 
}


void mostrarMenu()
{
    //Menú principal;
    cout << "CALCULADORA v1.0" << endl << endl;
    cout << "Elige una de las siguientes opciones:" << endl;
    cout << "1. Operación: Suma"<< endl;
    cout << "2. Operación: Resta"<< endl;
    cout << "3. Operación: Multiplicación"<< endl;
    cout << "4. Operación: División"<< endl;
    cout << "5. Operación: Residuo"<< endl;
    cout << "6. Operación: Potencia"<< endl;
    cout << "7. Salir" << endl;
    cout << "Ingresa el número de la operación a realizar:  ";

}



