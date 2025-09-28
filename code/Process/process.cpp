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
    string &nuevosString,
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    string &bloqueadosString,
    StaticQueue &nuevos,
    StaticQueue &pendientes, 
    Proceso *ejecucion, 
    StaticQueue &terminado,
    StaticQueue &bloqueados)
{
    nuevosString     = nuevos.toString(estadoProceso::NUEVO);
    pendientesString = pendientes.toString(estadoProceso::LISTO);

    ejecucionString = (ejecucion == nullptr) ? "" 
        : ejecucion->toString(estadoProceso::EJECUCION);

    if (ejecucion != nullptr) {
        ejecucion->dameCalculadora().operar();
    }

    resultadoString  = terminado.toString(estadoProceso::TERMINADO);
    bloqueadosString = bloqueados.toString(estadoProceso::BLOQUEADO);
}


void imprimirTablaResultados(
    int contadorGlobal,
    string &nuevosStr,
    string &pendienteStr,
    string &ejecucionStr,
    string &resultadoStr,
    string &bloqueadosStr,
    StaticQueue &nuevos,
    StaticQueue &pendientes,
    Proceso *ejecucion,
    StaticQueue &terminado,
    StaticQueue &bloqueados,
    int colWidth)
{
    // Limpiar pantalla antes de imprimir nueva información
    system(CLEAR);
    
    actualizarInformacion(nuevosStr, pendienteStr, ejecucionStr, resultadoStr, bloqueadosStr,
                          nuevos, pendientes, ejecucion, terminado, bloqueados);

    cout << fixed << setprecision(2);

    //Encabezado
    cout << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth - 10, '-') 
         << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth, '-') << "+" << endl;

    cout << "|" << left << setw(colWidth - 20) << "Nuevos"
         << "|" << left << setw(colWidth - 10) << "Listos"
         << "|" << left << setw(colWidth - 20) << "En ejecucion"
         << "|" << left << setw(colWidth) << "Terminados" << "|" << endl;

    cout << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth - 10, '-') 
         << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth, '-') << "+" << endl;

    // Imprimir filas alineadas
    vector<string> vNuevos     = splitLines(nuevosStr);
    vector<string> vListos     = splitLines(pendienteStr);
    vector<string> vEjecucion  = splitLines(ejecucionStr);
    vector<string> vTerminados = splitLines(resultadoStr);

    size_t maxLines = max({vNuevos.size(), vListos.size(), vEjecucion.size(), vTerminados.size()});

    for (size_t i = 0; i < maxLines; i++) {
        string c1 = i < vNuevos.size()     ? vNuevos[i]     : "";
        string c2 = i < vListos.size()     ? vListos[i]     : "";
        string c3 = i < vEjecucion.size()  ? vEjecucion[i]  : "";
        string c4 = i < vTerminados.size() ? vTerminados[i] : "";

        cout << "|" << left << setw(colWidth - 20) << c1
             << "|" << left << setw(colWidth - 10) << c2
             << "|" << left << setw(colWidth - 20) << c3
             << "|" << left << setw(colWidth) << c4 << "|" << endl;
    }

    cout << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth - 10, '-') 
         << "+" << string(colWidth - 20, '-') 
         << "+" << string(colWidth, '-') << "+" << endl;

    //Tabla: Bloqueados
    cout << "\nProcesos Bloqueados:" << endl;
    cout << "+" << string(colWidth, '-') << "+" << endl;
    cout << "|" << left << setw(colWidth) << "Bloqueados" << "|" << endl;
    cout << "+" << string(colWidth, '-') << "+" << endl;

    vector<string> vBloqueados = splitLines(bloqueadosStr);
    for (auto &line : vBloqueados) {
        cout << "|" << left << setw(colWidth) << line << "|" << endl;
    }
    cout << "+" << string(colWidth, '-') << "+" << endl;

    //Contadores
    cout << "Contador Global: " << contadorGlobal << endl;
}

void imprimirTablaBCP(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos, int contadorGlobal) {
    cout << "\n=== TABLA BCP (Bloque de Control de Procesos) ===\n";

    // Definir anchos de columna
    const int idWidth = 6;
    const int opWidth = 12;
    const int timeWidth = 12;
    const int standardWidth = 12;

    // Línea superior
    cout << "+" << string(idWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') << "+" << endl;

    // Encabezados
    cout << "|" << left << setw(idWidth) << "ID"
         << "|" << left << setw(opWidth) << "Operacion"
         << "|" << setw(opWidth) << "Contador"
         << "|" << setw(timeWidth) << "TME"
         << "|" << setw(timeWidth) << "T.Lle" << "|"
         << setw(timeWidth) << "T.Fin" << "|"
         << setw(standardWidth) << "T.Esp" << "|"
         << setw(standardWidth) << "T.Res" << "|"
         << setw(standardWidth) << "T.Ret" << "|"
         << setw(standardWidth) << "T.Ser" << "|" << endl;

    // Línea separadora
    cout << "+" << string(idWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') << "+" << endl;

    for (int i = 0; i < cantidadProcesos; i++) {
        Clock &clk = arregloProcesos[i].dameReloj();
        Calculadora &calc = arregloProcesos[i].dameCalculadora();

        // Función auxiliar para formatear tiempos
        auto formatTime = [](int time) -> string {
            return (time >= 0) ? to_string(time) : "N/A";
        };

        // Imprimir fila con alineación adecuada
        cout << "|" << right << setw(idWidth) << arregloProcesos[i].dameID()
             << "|" << right << setw(opWidth) << calc.operacionToString()
             << "|" << right << setw(opWidth) << contadorGlobal
             << "|" << right << setw(timeWidth) << formatTime(clk.getEstimatedTimeAmount())
             << "|" << right << setw(timeWidth) << formatTime(clk.getArriveTime())
             << "|" << right << setw(timeWidth) << formatTime(clk.getEndTime())
             << "|" << right << setw(standardWidth) << formatTime(clk.getWaitingTime())
             << "|" << right << setw(standardWidth) << formatTime(clk.getResponseTime())
             << "|" << right << setw(standardWidth) << formatTime(clk.getReturnTime())
             << "|" << right << setw(standardWidth) << clk.getServiceTime() << "|" << endl;
    }

    // Línea inferior
    cout << "+" << string(idWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(opWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') 
         << "+" << string(standardWidth, '-') << "+" << endl;
}

void ejecutarProcesos(Proceso (&arregloProcesos)[TAM_PROCESOS], int cantidadProcesos)
{
    int i, j, procesoActual = 0;
    const int colWidth = 41; 
    int contadorGlobal = 0, tiempoTranscurrido;
    const int tiempoBloqueo = 8;
    string nuevoString, pendientesString, ejecucionString, resultadoString, bloqueadoString;

    //Colas
    StaticQueue nuevos, pendientes, bloqueado, terminado;
    
    Proceso *ejecucion = nullptr;
    bool pausa = false;

    cout << "Iniciando ejecución con " << cantidadProcesos << " procesos" << endl;
    cout << "Tamaño de cola nuevos: " << nuevos.size() << endl;    
    
        // INIZIALIZACION COLA NUEVOS
        for (int i = 0; i < cantidadProcesos; i++) 
        {
            arregloProcesos[i].fijaEstado(estadoProceso::NUEVO);
            nuevos.enqueue(&arregloProcesos[i]);
        }
        
        auto contarEnMemoria = [&]() {
            int enMemoria = pendientes.size() + bloqueado.size(); 
            if (ejecucion != nullptr) enMemoria++;
            return enMemoria;
        };
        
        
        // EJECUCIÓN PROGRAMA
        
        while(!nuevos.isEmpty() || !pendientes.isEmpty() || ejecucion != nullptr || !bloqueado.isEmpty()) 
        {
            // Captura de teclas
            if(_kbhit()) {
                char tecla = toupper(_getch());
                switch(tecla) {
                    case 'E': // Interrupción E/S
                        if (ejecucion != nullptr) { 
                            ejecucion->fijaEstado(estadoProceso::BLOQUEADO);
                            ejecucion->dameReloj().setBlockedTime(8);
                            bloqueado.enqueue(ejecucion);
                            ejecucion = nullptr;
                        }
                        break;
                    case 'W': // Error
                    if (ejecucion != nullptr) {
                        ejecucion->dameReloj().setEndTime(contadorGlobal + 1);
                        ejecucion->dameCalculadora().fijaResultado(numeric_limits<float>::lowest());
                        ejecucion->fijaEstado(estadoProceso::TERMINADO);
                        terminado.enqueue(ejecucion);
                        ejecucion = nullptr;
                    }
                    break;
                    case 'P': // Pausa
                        pausa = true;
                        break;
                    case 'C': // Continuar
                        pausa = false;
                        break;
                }
            }

            // Manejo de pausa
            if(pausa) {
                        imprimirTablaResultados(
                            contadorGlobal, nuevoString, pendientesString, ejecucionString,
                            resultadoString, bloqueadoString, nuevos, pendientes, ejecucion,
                            terminado, bloqueado, colWidth);
                cout << "Presiona C para continuar..." << endl;
                
                while(pausa) {
                    if(_kbhit()) {
                        char t = toupper(_getch());
                        if(t == 'C') pausa = false;
                    }
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
                continue; 
            }

        // Mover procesos de nuevos a listos si hay espacio en memoria
        while (!nuevos.isEmpty() && contarEnMemoria() < 4) {
            Proceso* p = nuevos.getFront();
            if (p->dameReloj().getArriveTime() == -1) {
                p->dameReloj().setArriveTime(contadorGlobal);
            }
            nuevos.dequeue();
            p->fijaEstado(estadoProceso::LISTO);
            pendientes.enqueue(p);
        }

        // Si no hay proceso en ejecucion, tomar uno de listos
        if (ejecucion == nullptr && !pendientes.isEmpty()) {
            ejecucion = pendientes.getFront();
            pendientes.dequeue();
            ejecucion->fijaEstado(estadoProceso::EJECUCION);
            
            //Establecer tiempo de respuesta solo cuando entra por primera vez a ejecución
            if (ejecucion->dameReloj().getResponseTime() == -1) {
                ejecucion->dameReloj().setResponseTime(contadorGlobal);
            }
        }

        //Procesar ejecución actual
        if (ejecucion != nullptr) {
            int nuevoElapsed = ejecucion->dameReloj().getElapsedTime() + 1;
            ejecucion->dameReloj().setElapsedTime(nuevoElapsed);
            
            ejecucion->dameReloj().setServiceTime(ejecucion->dameReloj().getServiceTime() + 1);
            
            // Operar la calculadora
            ejecucion->dameCalculadora().operar();

            // Si terminó su tiempo estimado
            if (nuevoElapsed >= ejecucion->dameReloj().getEstimatedTimeAmount()) {
                ejecucion->dameReloj().setEndTime(contadorGlobal + 1); 
                
                ejecucion->dameReloj().setReturnTime(
                    ejecucion->dameReloj().getEndTime() - ejecucion->dameReloj().getArriveTime()
                );
                
                ejecucion->dameReloj().setWaitingTime(
                    ejecucion->dameReloj().getReturnTime() - ejecucion->dameReloj().getServiceTime()
                );
                
                ejecucion->fijaEstado(estadoProceso::TERMINADO);
                terminado.enqueue(ejecucion);
                ejecucion = nullptr;
            }
        }

        // Desbloquear procesos
        int nBloq = bloqueado.size();
        for (int b = 0; b < nBloq; b++) {
            Proceso* proc = bloqueado.getFront();
            bloqueado.dequeue();
            
            int tiempoRestante = proc->dameReloj().decreaseBlockedTime();

            if (tiempoRestante <= 0 && contarEnMemoria() < 4) {
                proc->fijaEstado(estadoProceso::LISTO);
                pendientes.enqueue(proc);
            } else {
                bloqueado.enqueue(proc); // sigue bloqueado
            }
        }

        contadorGlobal++;
            
        // Imprimir tabla actualizada
        imprimirTablaResultados(
                            contadorGlobal, nuevoString, pendientesString, ejecucionString,
                            resultadoString, bloqueadoString, nuevos, pendientes, ejecucion,
                            terminado, bloqueado, colWidth);

        // Esperar antes de la siguiente iteración
        this_thread::sleep_for(chrono::seconds(1));
        }   

    // Impresión final
    imprimirTablaResultados(
                          contadorGlobal, nuevoString, pendientesString, ejecucionString,
                          resultadoString, bloqueadoString, nuevos, pendientes, ejecucion,
                          terminado, bloqueado, colWidth);
    
    imprimirTablaBCP(arregloProcesos, cantidadProcesos, contadorGlobal);

    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
