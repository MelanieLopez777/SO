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

void actualizarInformacion(
    string &nuevosString,
    string &pendientesString, 
    string &ejecucionString, 
    string &resultadoString, 
    string &bloqueadosString,
    StaticQueue<Proceso> &nuevos,
    StaticQueue<Proceso> &pendientes, 
    Proceso *ejecucion, 
    StaticQueue<Proceso> &terminado,
    StaticQueue<Proceso> &bloqueados)
{
    nuevosString     = nuevos.toString();
    pendientesString = pendientes.toString();

    ejecucionString = (ejecucion == nullptr) ? "" 
        : ejecucion->toString(estadoProceso::EJECUCION);

    if (ejecucion != nullptr) {
        ejecucion->dameCalculadora().operar();
    }

    resultadoString  = terminado.toString();
    bloqueadosString = bloqueados.toString();
}

void printTableRow(const string &nuevosStr,
                   const string &pendientesStr,
                   const string &ejecucionStr,
                   const string &terminadosStr,
                   int colWidth)
{
    vector<string> nuevos = splitLines(nuevosStr);
    vector<string> pendientes = splitLines(pendientesStr);
    vector<string> ejecucion = splitLines(ejecucionStr);
    vector<string> terminados = splitLines(terminadosStr);

    // Determina la cantidad máxima de líneas
    size_t maxLines = max({nuevos.size(), pendientes.size(), ejecucion.size(), terminados.size()});

    for (size_t i = 0; i < maxLines; ++i) {
        string nuevoLine = (i < nuevos.size()) ? nuevos[i] : "";
        string pendLine  = (i < pendientes.size()) ? pendientes[i] : "";
        string ejecLine  = (i < ejecucion.size()) ? ejecucion[i] : "";
        string termLine  = (i < terminados.size()) ? terminados[i] : "";

        cout << "| " << left << setw(colWidth - 20) << nuevoLine
             << "| " << left << setw(colWidth - 9) << pendLine
             << "| " << left << setw(colWidth - 15) << ejecLine
             << "| " << left << setw(colWidth + 10) << termLine << "|" << endl;
    }
}


void imprimirTablaResultados(
    int contadorGlobal,
    string &nuevosStr,
    string &pendienteStr,
    string &ejecucionStr,
    string &resultadoStr,
    string &bloqueadosStr,
    StaticQueue<Proceso> &nuevos,
    StaticQueue<Proceso> &pendientes,
    Proceso *ejecucion,
    StaticQueue<Proceso> &terminado,
    StaticQueue<Proceso> &bloqueados,
    int colWidth)
{
    system(CLEAR);
    actualizarInformacion(nuevosStr, pendienteStr, ejecucionStr, resultadoStr, bloqueadosStr,
                          nuevos, pendientes, ejecucion, terminado, bloqueados);

    cout << fixed << setprecision(2);

    // --- Calcular ancho total ---
    string separador = "+" + string(colWidth - 19, '-')
                         + "+" + string(colWidth - 8, '-')
                         + "+" + string(colWidth - 14, '-')
                         + "+" + string(colWidth + 11, '-') + "+";

    // --- Encabezado ---
    cout << separador << endl;
    cout << "| " << left << setw(colWidth - 20) << "Nuevos"
         << "| " << left << setw(colWidth - 9) << "Listos"
         << "| " << left << setw(colWidth - 15) << "En Ejecución"
         << "| " << left << setw(colWidth + 10) << "Terminados" << "|" << endl;
    cout << separador << endl;

    // --- Contenido ---
    printTableRow(nuevosStr, pendienteStr, ejecucionStr, resultadoStr, colWidth);
    cout << separador << endl;

    // --- Bloqueados ---
    cout << "\nProcesos Bloqueados:" << endl;
    string sepBloq = "+" + string(colWidth + 1, '-') + "+";
    cout << sepBloq << endl;
    cout << "| " << left << setw(colWidth) << "Bloqueados" << "|" << endl;
    cout << sepBloq << endl;

    vector<string> vBloqueados = splitLines(bloqueadosStr);
    if (vBloqueados.empty())
        cout << "| " << left << setw(colWidth) << " " << "|" << endl;
    else
        for (auto &line : vBloqueados)
            cout << "| " << left << setw(colWidth) << line << "|" << endl;
    cout << sepBloq << endl;

    // --- Contador global ---
    cout << "\nContador Global: " << contadorGlobal << endl;
}



void imprimirTablaBCP(vector<Proceso>& arregloProcesos, int cantidadProcesos) {
    cout << "\n=== TABLA BCP (Bloque de Control de Procesos) ===\n";

    const int idWidth = 6, estadoWidth = 14, opWidth = 15;
    const int tWidth = 10, resWidth = 12;

    cout << "+" << string(idWidth, '-')
         << "+" << string(estadoWidth, '-')
         << "+" << string(opWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(resWidth, '-') << "+" << endl;

    cout << "|" << left << setw(idWidth) << "ID"
         << "|" << left << setw(estadoWidth) << "Estado"
         << "|" << left << setw(opWidth) << "Operacion"
         << "|" << left << setw(tWidth) << "T.Lleg"
         << "|" << left << setw(tWidth) << "T.Fin"
         << "|" << left << setw(tWidth) << "T.Ret"
         << "|" << left << setw(tWidth) << "T.Esp"
         << "|" << left << setw(tWidth) << "T.Serv"
         << "|" << left << setw(tWidth) << "T.Rest"
         << "|" << left << setw(tWidth) << "T.Resp"
         << "|" << left << setw(resWidth) << "Resultado" << "|" << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(estadoWidth, '-')
         << "+" << string(opWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(resWidth, '-') << "+" << endl;

    for (auto it = arregloProcesos.begin(); it != arregloProcesos.end(); ++it) {
        Clock &clk = it->dameReloj();
        Calculadora &calc = it->dameCalculadora();

        string estado;
        switch (it->dameEstado()) {
            case estadoProceso::NUEVO: estado = "Nuevo"; break;
            case estadoProceso::LISTO: estado = "Listo"; break;
            case estadoProceso::EJECUCION: estado = "Ejecucion"; break;
            case estadoProceso::BLOQUEADO: estado = "Bloqueado (" + to_string(clk.getBlockedTime()) + ")"; break;
            case estadoProceso::TERMINADO:
                if (calc.dameResultado() == numeric_limits<float>::lowest())
                    estado = "Error";
                else
                    estado = "Terminado (OK)";
                break;
        }

        auto valOrNA = [](int v) { return (v >= 0) ? to_string(v) : string("N/A"); };
        auto resOrNA = [&](float r) {
            if (it->dameEstado() == estadoProceso::TERMINADO)
                return (r == numeric_limits<float>::lowest()) ? string("Error") : to_string(r);
            return string("N/A");
        };

        cout << "|" << right << setw(idWidth) << it->dameID()
             << "|" << left << setw(estadoWidth) << estado
             << "|" << left << setw(opWidth) << calc.operacionToString()
             << "|" << right << setw(tWidth) << valOrNA(clk.getArriveTime())
             << "|" << right << setw(tWidth) << valOrNA(clk.getEndTime())
             << "|" << right << setw(tWidth) << valOrNA(clk.getReturnTime())
             << "|" << right << setw(tWidth) << valOrNA(clk.getWaitingTime())
             << "|" << right << setw(tWidth) << clk.getServiceTime()
             << "|" << right << setw(tWidth) << (it->dameEstado() == estadoProceso::TERMINADO ? string("0") : to_string(max(0, clk.getEstimatedTimeAmount() - clk.getElapsedTime())))
             << "|" << right << setw(tWidth) << valOrNA(clk.getResponseTime())
             << "|" << left << setw(resWidth) << resOrNA(calc.dameResultado())
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-')
         << "+" << string(estadoWidth, '-')
         << "+" << string(opWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(tWidth, '-')
         << "+" << string(tWidth, '-') << "+" << string(resWidth, '-') << "+" << endl;
}


void ejecutarProcesos(vector<Proceso>& arregloProcesos, int cantidadProcesos)
{
    const int colWidth = 35; 
    int contadorGlobal = 0;
    const int tiempoBloqueo = 8;
    string nuevoString, pendientesString, ejecucionString, resultadoString, bloqueadoString;

    // Colas por valor
    StaticQueue<Proceso> nuevos, pendientes, bloqueado, terminado;
    
    Proceso ejecucion;
    bool hayEjecucion = false;
    bool pausa = false;

    cout << "Iniciando ejecución con " << cantidadProcesos << " procesos" << endl;

    // Inicializar cola de nuevos
    for (auto &p : arregloProcesos) {
        p.fijaEstado(estadoProceso::NUEVO);
        nuevos.enqueue(p);
    }

    auto contarEnMemoria = [&]() {
        int enMemoria = pendientes.size() + bloqueado.size(); 
        if (hayEjecucion) enMemoria++;
        return enMemoria;
    };
        
    // EJECUCIÓN PROGRAMA
    while(!nuevos.isEmpty() || !pendientes.isEmpty() || hayEjecucion || !bloqueado.isEmpty()) 
    {
        // Captura de teclas
        if(_kbhit()) {
            char tecla = toupper(_getch());
            switch(tecla) {
                case 'E': // Interrupción E/S
                    if (hayEjecucion) { 
                        ejecucion.fijaEstado(estadoProceso::BLOQUEADO);
                        ejecucion.dameReloj().setBlockedTime(tiempoBloqueo);
                        bloqueado.enqueue(ejecucion);
                        hayEjecucion = false;
                    }
                    break;
                case 'W': // Error
                    if (hayEjecucion) {
                        ejecucion.dameReloj().setEndTime(contadorGlobal + 1);

                        int tRetorno = ejecucion.dameReloj().getEndTime() - ejecucion.dameReloj().getArriveTime();
                        int tEspera  = tRetorno - ejecucion.dameReloj().getServiceTime();

                        ejecucion.dameReloj().setReturnTime(tRetorno);
                        ejecucion.dameReloj().setWaitingTime(tEspera);

                        ejecucion.dameCalculadora().fijaResultado(numeric_limits<float>::lowest());
                        ejecucion.fijaEstado(estadoProceso::TERMINADO);
                        terminado.enqueue(ejecucion);
                        hayEjecucion = false;
                    }
                    break;
                case 'N': // Nuevo proceso generado
                    nuevos.enqueue(generarDatos());
                    arregloProcesos.push_back(generarDatos());
                    break;
                case 'B': // Mostrar BCP y pausar
                    pausa = true;
                    system(CLEAR);
                    imprimirTablaBCP(arregloProcesos, cantidadProcesos);
                    cout << "\nPresiona 'C' para continuar la simulación..." << endl;
                    while (pausa) {
                        if (_kbhit()) {
                            char t = toupper(_getch());
                            if (t == 'C') pausa = false;
                        }
                        this_thread::sleep_for(chrono::milliseconds(100));
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

        if(pausa) {
            imprimirTablaResultados(
                contadorGlobal, nuevoString, pendientesString, ejecucionString,
                resultadoString, bloqueadoString, nuevos, pendientes, hayEjecucion ? &ejecucion : nullptr,
                terminado, bloqueado, colWidth);

            while(pausa) {
                if(_kbhit()) {
                    char t = toupper(_getch());
                    if(t == 'C') pausa = false;
                }
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            continue; 
        }

        // Mover procesos de nuevos a listos si hay espacio
        while (!nuevos.isEmpty() && contarEnMemoria() < 4) {
            Proceso p = nuevos.getFront();
            if (p.dameReloj().getArriveTime() == -1) {
                p.dameReloj().setArriveTime(contadorGlobal);
            }
            nuevos.dequeue();
            p.fijaEstado(estadoProceso::LISTO);
            pendientes.enqueue(p);
        }

        // Si no hay proceso en ejecución, tomar uno de pendientes
        if (!hayEjecucion && !pendientes.isEmpty()) {
            ejecucion = pendientes.getFront();
            pendientes.dequeue();
            ejecucion.fijaEstado(estadoProceso::EJECUCION);

            if (ejecucion.dameReloj().getResponseTime() == -1) {
                 ejecucion.dameReloj().calcResponseTime(contadorGlobal);
            }
            hayEjecucion = true;
        }

        // Procesar ejecución actual
        if (hayEjecucion) {
            int nuevoElapsed = ejecucion.dameReloj().getElapsedTime() + 1;
            ejecucion.dameReloj().setElapsedTime(nuevoElapsed);
            ejecucion.dameReloj().setServiceTime(ejecucion.dameReloj().getServiceTime() + 1);
            ejecucion.dameCalculadora().operar();

            if (nuevoElapsed >= ejecucion.dameReloj().getEstimatedTimeAmount()) {
                ejecucion.dameReloj().setEndTime(contadorGlobal + 1);

                // Calcular tiempos derivados
                ejecucion.dameReloj().calcReturnTime();   // T. retorno = fin - llegada
                ejecucion.dameReloj().calcWaitingTime();  // T. espera = retorno - servicio
                ejecucion.dameReloj().calcServiceTime();  // T. servicio = retorno - espera

                ejecucion.fijaEstado(estadoProceso::TERMINADO);
                terminado.enqueue(ejecucion);
                hayEjecucion = false;
            }
        }

        // Desbloquear procesos
        int nBloq = bloqueado.size();
        for (int b = 0; b < nBloq; b++) {
            Proceso proc = bloqueado.getFront();
            bloqueado.dequeue();

            int tiempoRestante = proc.dameReloj().decreaseBlockedTime();

            if (tiempoRestante <= 0 && contarEnMemoria() < 4) {
                proc.fijaEstado(estadoProceso::LISTO);
                pendientes.enqueue(proc);
            } else {
                bloqueado.enqueue(proc);
            }
        }

        contadorGlobal++;

        // Imprimir tabla
        imprimirTablaResultados(
            contadorGlobal, nuevoString, pendientesString, ejecucionString,
            resultadoString, bloqueadoString, nuevos, pendientes, hayEjecucion ? &ejecucion : nullptr,
            terminado, bloqueado, colWidth);

        this_thread::sleep_for(chrono::seconds(1));
    }

    // Impresión final
    imprimirTablaResultados(
        contadorGlobal, nuevoString, pendientesString, ejecucionString,
        resultadoString, bloqueadoString, nuevos, pendientes, hayEjecucion ? &ejecucion : nullptr,
        terminado, bloqueado, colWidth);

    imprimirTablaBCP(arregloProcesos, cantidadProcesos);

    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

