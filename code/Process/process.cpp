#include "process.h"


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
        cout << "|"
             << left << setw(colWidth) << (i < pendientes.size() ? pendientes[i] : "")
             << "|"
             << left << setw(colWidth) << (i < ejecucion.size() ? ejecucion[i] : "")
             << "|"
             << left << setw(colWidth) << (i < resultados.size() ? resultados[i] : "")
             << "|" << endl;
    }
}


void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos)
{
    int numLotes, lotesPendientes, loteEnEjecucion, lotesTerminados, contadorGlobal;
    int i, j, aux2;
    int tiempoEjecucion, tiempoRestante;
    int ejecucionLoteCompleto;
    const int colWidth = 30; 
    string ejecucionString;
    StaticQueue pendientes, terminado;
    Proceso *ejecucion;
    
    numLotes = cantidadProcesos / 4;
    if((cantidadProcesos % 4) != 0)
    {
        numLotes++;
    }
    lotesPendientes = numLotes - 1;
    loteEnEjecucion = numLotes - lotesPendientes;
    contadorGlobal = 0;
    ejecucionLoteCompleto = 0;
    i = 0, aux2 = 0;
    while(i < cantidadProcesos){
        loteEnEjecucion = numLotes - lotesPendientes;

        
        for (int aux = 0; aux < 4; aux++, aux2++) {
            pendientes.enqueue(&arregloProcesos[aux2]);
            ejecucionLoteCompleto += arregloProcesos[aux2].dameTME();
        }
        tiempoEjecucion = 0;
        tiempoRestante = 0;
        ejecucion = nullptr;
        j = 0;
        while(j < ejecucionLoteCompleto) {
         // Encabezado
            cout << "Numero de lotes pendientes: " << lotesPendientes << endl;
            cout << "Lote en ejecucion #" << loteEnEjecucion << ":" << endl;
        // Línea superior
            cout << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') << "+" << endl;

            // Títulos
            cout << "|" << left << setw(colWidth) << "Pendientes"
                << "|" << left << setw(colWidth) << "En ejecucion"
                << "|" << left << setw(colWidth) << "Resultados" << "|" << endl;

            // Línea divisoria
            cout << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') << "+" << endl;

            // Calculos        
            tiempoEjecucion++;
            tiempoRestante = (ejecucion != nullptr) ? (ejecucion->dameTME() - tiempoEjecucion) : 0;

            // Preparar strings
            string pendientesString = pendientes.toString(PROCESO);
            string ejecucionString = (ejecucion == nullptr) ? "" 
                : ejecucion->dameNombre() + "\nOperacion: " + ejecucion->dameCalculadora().operacionToString(ejecucion->dameOperacion()) + "\nID: " + to_string(ejecucion->dameID()) + "\nTME: " + to_string(ejecucion->dameTME()) + "\nTE: " + to_string(tiempoEjecucion) + "\nTR: " + to_string(tiempoRestante);
            if(ejecucion != nullptr)
            {
                ejecucion->dameCalculadora().operar(ejecucion->dameOperacion());
            }
            string resultadoString = terminado.toString(TERMINADO);

            // Imprimir fila alineada
            printTableRow(pendientesString, ejecucionString, resultadoString, colWidth);

            // Línea final
            cout << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') 
                << "+" << string(colWidth, '-') << "+" << endl;

            // Contador
            cout << "Contador Global: " << contadorGlobal << endl;

            // Actualización
            this_thread::sleep_for(chrono::seconds(1));
            system(CLEAR);
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

            j++;
        }
        lotesPendientes--;
        lotesTerminados++;
        
        i++;
    }
}
