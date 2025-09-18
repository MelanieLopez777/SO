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
        string pendLine = i < pendientes.size() ? pendientes[i] : "";
        string ejecLine = i < ejecucion.size() ? ejecucion[i] : "";
        string resLine = i < resultados.size() ? resultados[i] : "";

        cout << fixed << setprecision(2);
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
    StaticQueue &terminado)
{
    pendientesString = pendientes.toString(PROCESO);
            ejecucionString = (ejecucion == nullptr) ? "" 
                : "ID: " + to_string(ejecucion->dameID()) +"\nOperacion: " + ejecucion->dameCalculadora().operacionToString() +  "\nTME: " + to_string(ejecucion->dameReloj().getEstimatedTimeAmount()) + "\nT.Trans: " + to_string(ejecucion->dameReloj().getElapsedTime()) + "\nTR: " + to_string(ejecucion->dameReloj().getEstimatedTimeAmount() - ejecucion->dameReloj().getElapsedTime());
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
    int colWidth)
{
    actualizarInformacion(pendienteStr, ejecucionStr, resultadoStr, pendientes, ejecucion, terminado);

    cout << fixed << setprecision(2);
    
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
    int tiempoTranscurrido;
    int i, j, procesoActual;
    int ejecucionLoteCompleto;
    const int colWidth = 30; 
    string pendientesString, ejecucionString, resultadoString;
    StaticQueue pendientes, terminado;
    Proceso *ejecucion = nullptr;
    bool pausa = false;

    numLotes = cantidadProcesos / 4;
    if(residuoLoteFinal != 0) numLotes++;
    
    lotesPendientes  = numLotes - 1;
    loteEnEjecucion = numLotes - lotesPendientes;
    
    for(i = 0, procesoActual = 0; i < numLotes; i++)
    {
        loteEnEjecucion = numLotes - lotesPendientes;
        ejecucionLoteCompleto = 0;

        // INICIALIZACION DE LOTE
        if(loteEnEjecucion == numLotes && residuoLoteFinal != 0) {
            tiempoCambioContexto = residuoLoteFinal;
            // LOTES CON MENOS DE 4 PROCESOS
            for (int aux = 0; aux < residuoLoteFinal; aux++, procesoActual++) {
                arregloProcesos[procesoActual].fijaNumeroLote(loteEnEjecucion);
                pendientes.enqueue(&arregloProcesos[procesoActual]);
                ejecucionLoteCompleto += arregloProcesos[procesoActual].dameReloj().getEstimatedTimeAmount();
            }
        } else {
            // LOTES COMPLETOS
            tiempoCambioContexto = 4;
            for (int aux = 0; aux < 4; aux++, procesoActual++) {
                arregloProcesos[procesoActual].fijaNumeroLote(loteEnEjecucion);
                pendientes.enqueue(&arregloProcesos[procesoActual]);
                ejecucionLoteCompleto += arregloProcesos[procesoActual].dameReloj().getEstimatedTimeAmount();
            }
        }

        // EJECUCIÓN DEL LOTE
        for(j = 0, ejecucion = nullptr;
            j < ejecucionLoteCompleto + tiempoCambioContexto; j++) 
        {
            // Captura de teclas
            if(_kbhit()) {
                char tecla = toupper(_getch());
                switch(tecla) {
                    case 'E': // Interrupción E/S
                        if(ejecucion != nullptr) {
                            pendientes.enqueue(ejecucion);
                            ejecucion = nullptr;
                        }
                        break;
                    case 'W': // Error
                        if(ejecucion != nullptr) {
                            ejecucion->dameCalculadora().fijaResultado(numeric_limits<float>::lowest());
                            terminado.enqueue(ejecucion);
                            j += ejecucion->dameReloj().getEstimatedTimeAmount() - ejecucion->dameReloj().getElapsedTime();
                            ejecucion = nullptr;
                        }
                        break;
                    case 'P': // Pausa
                        pausa = true;
                         imprimirTablaResultados(lotesPendientes, loteEnEjecucion, lotesTerminados,
                                    contadorGlobal, pendientesString, ejecucionString,
                                    resultadoString, pendientes, ejecucion,
                                    terminado, colWidth);
                        break;
                    case 'C': // Continuar
                        pausa = false;
                        break;
                }
            }
            // Manejo de pausa
            while(pausa) {
                if(_kbhit()) {
                    char t = toupper(_getch());
                    if(t == 'C') pausa = false;
                }
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            // Calculos
            if(ejecucion != nullptr) {
                ejecucion->dameReloj().setElapsedTime(tiempoTranscurrido++);
            }

            // Imprimir tabla
            imprimirTablaResultados(lotesPendientes, loteEnEjecucion, lotesTerminados,
                                    contadorGlobal, pendientesString, ejecucionString,
                                    resultadoString, pendientes, ejecucion,
                                    terminado, colWidth);

            this_thread::sleep_for(chrono::seconds(1));
            //system(CLEAR);  

            if(ejecucion != nullptr)
                contadorGlobal++;

            // Actualizar ejecución
            if (ejecucion == nullptr && !pendientes.isEmpty()) {
                ejecucion = pendientes.getFront();
                pendientes.dequeue();
                tiempoTranscurrido = 0;
            } else if (ejecucion != nullptr && (ejecucion->dameReloj().getEstimatedTimeAmount() - ejecucion->dameReloj().getElapsedTime()) == 0) {
                terminado.enqueue(ejecucion);
                ejecucion = nullptr;
            }
        }

        if(lotesPendientes != 0) lotesPendientes--;
        lotesTerminados++;
    }

    imprimirTablaResultados(lotesPendientes, loteEnEjecucion, lotesTerminados,
                            contadorGlobal, pendientesString, ejecucionString,
                            resultadoString, pendientes, ejecucion, terminado, 
                            colWidth);

    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

