#include "process.h"
#include <cstdlib>
#include <iostream>


using namespace std;

vector<string> splitLines(const string &s) {
    vector<string> lines;
    istringstream iss(s);
    string line;
    while (getline(iss, line)) {
        lines.push_back(line);
    }
    return lines;
}

void printTableRow(const string &pendienteStr, const string &ejecucionStr, const string &resultadoStr, int colWidth) {
    vector<string> pendientes = splitLines(pendienteStr);
    vector<string> ejecucion = splitLines(ejecucionStr);
    vector<string> resultados = splitLines(resultadoStr);

    size_t maxLines = max({pendientes.size(), ejecucion.size(), resultados.size()});

    for (size_t i = 0; i < maxLines; i++) {
        string pendLine = i < pendientes.size() ? pendientes[i] : "";
        string ejecLine = i < ejecucion.size() ? ejecucion[i] : "";
        string resLine = i < resultados.size() ? resultados[i] : "";

        cout << "|"
             << left << setw(colWidth) << pendLine << "|"
             << left << setw(colWidth) << ejecLine << "|"
             << left << setw(colWidth) << resLine << "|" << endl;
    }
}

void actualizarInformacion(
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    StaticQueue &pendientes, 
    Proceso *ejecucion, 
    StaticQueue &terminado, 
    int tiempoEjecucion, 
    int tiempoRestante)
{
    pendientesString = pendientes.toString(PROCESO);
            ejecucionString = (ejecucion == nullptr) ? "" 
                : ejecucion->dameNombre() + "\nOperacion: " + ejecucion->dameCalculadora().operacionToString() + "\nID: " + to_string(ejecucion->dameID()) + "\nTME: " + to_string(ejecucion->dameTME()) + "\nTE: " + to_string(tiempoEjecucion) + "\nTR: " + to_string(tiempoRestante);
            if(ejecucion != nullptr)
            {
                ejecucion->dameCalculadora().operar();
            }
            resultadoString = terminado.toString(TERMINADO);
}

void imprimirTablaResultados(
    int lotesPendientes,
    int loteEnEjecucion,
    int lotesTerminados,
    int contadorGlobal,
    string &pendienteStr,
    string &ejecucionStr,
    string &resultadoStr,
    StaticQueue &pendientes,
    Proceso *ejecucion,
    StaticQueue &terminado,
    int tiempoEjecucion,
    int tiempoRestante,
    int colWidth)
{
    actualizarInformacion(pendienteStr, ejecucionStr, resultadoStr, pendientes, ejecucion, terminado, tiempoEjecucion, tiempoRestante);
    
    // Encabezado
    cout << "Numero de lotes pendientes: " << lotesPendientes << endl;
    cout << "Lote en ejecucion #" << loteEnEjecucion << ":" << endl;
    
    // Línea superior
    cout << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-') << "+" << endl;
    
    // Títulos - Reescritos para evitar espacios extra
    cout << "|" << left << setw(colWidth) << "Pendientes"
         << "|" << left << setw(colWidth) << "En ejecucion"
         << "|" << left << setw(colWidth) << "Resultados" << "|" << endl;
    
    // Línea divisoria
    cout << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-') << "+" << endl;
    
    // Imprimir fila alineada
    printTableRow(pendienteStr, ejecucionStr, resultadoStr, colWidth);
    
    // Línea final
    cout << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-')
         << "+" << string(colWidth, '-') << "+" << endl;
    
    // Contador
    cout << "Contador Global: " << contadorGlobal << endl;
    cout << "Lotes terminados: " << lotesTerminados << endl;
}


void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos)
{
    int numLotes;
    int lotesPendientes;
    int loteEnEjecucion;
    int lotesTerminados = 0;
    int contadorGlobal = 0;
    int residuoLoteFinal = cantidadProcesos % 4;
    int tiempoCambioContexto;
    int i, j, procesoActual;
    int tiempoEjecucion, tiempoRestante;
    int ejecucionLoteCompleto;
    const int colWidth = 30; 
    string pendientesString, ejecucionString, resultadoString;
    StaticQueue pendientes, terminado;
    Proceso *ejecucion;
    
    numLotes = cantidadProcesos / 4;
    if(residuoLoteFinal != 0)
    {
        numLotes++;
    }
    lotesPendientes  = numLotes - 1;
    loteEnEjecucion = numLotes - lotesPendientes;
    
    for(i = 0, procesoActual = 0; i < numLotes; i++)
    {
        cout << "i = " << i << endl;
        cout << "Procesos = " << cantidadProcesos << endl;
        loteEnEjecucion = numLotes - lotesPendientes;
        ejecucionLoteCompleto = 0;
        // Agregar procesos a la cola de pendientes
        if(loteEnEjecucion == numLotes && residuoLoteFinal != 0)
        {
            tiempoCambioContexto = residuoLoteFinal;
            for (int aux = 0; aux < residuoLoteFinal; aux++, procesoActual++) {
                pendientes.enqueue(&arregloProcesos[procesoActual]);
                ejecucionLoteCompleto += arregloProcesos[procesoActual].dameTME();
            }
        }
        else {
        {
            tiempoCambioContexto = 4;
            for (int aux = 0; aux < 4; aux++, procesoActual++) {
                pendientes.enqueue(&arregloProcesos[procesoActual]);
                ejecucionLoteCompleto += arregloProcesos[procesoActual].dameTME();
            }
        }
        }  
        for(j = 0, ejecucion = nullptr, tiempoEjecucion = 0, tiempoRestante = 0; j < ejecucionLoteCompleto + tiempoCambioContexto; j++) 
        {
            // Calculos        
            tiempoEjecucion++;
            tiempoRestante = (ejecucion != nullptr) ? (ejecucion->dameTME() - tiempoEjecucion) : 0;
            
            // Imprimir Tabla
            imprimirTablaResultados(lotesPendientes, loteEnEjecucion, lotesTerminados, contadorGlobal, pendientesString, ejecucionString, resultadoString, pendientes, ejecucion, terminado, tiempoEjecucion, tiempoRestante, colWidth);

            // Actualización
            this_thread::sleep_for(chrono::seconds(1));
            system(CLEAR);
            
            if(ejecucion != nullptr)
                contadorGlobal++;
        
            // Actualizar ejecución y pendientes
            if (ejecucion == nullptr && !pendientes.isEmpty()) {
                // Cargar un nuevo proceso si no hay ejecución
                ejecucion = pendientes.getFront();
                pendientes.dequeue();
                tiempoEjecucion = 0;
            } else if (ejecucion != nullptr && tiempoRestante == 0) {
                // Proceso terminó, pasa a terminados
                terminado.enqueue(ejecucion);
                ejecucion = nullptr;
            }
        }
        lotesPendientes--;
        lotesTerminados++;
        cout << endl;
        }
    imprimirTablaResultados(lotesPendientes, loteEnEjecucion, lotesTerminados, contadorGlobal, pendientesString, ejecucionString, resultadoString, pendientes, ejecucion, terminado, tiempoEjecucion, tiempoRestante, colWidth);
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system(CLEAR);
}
