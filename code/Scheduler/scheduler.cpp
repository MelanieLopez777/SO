#include "../Scheduler/scheduler.h"

Scheduler::Scheduler(QObject *parent)
    : QObject(parent),
      contadorGlobal(0),
      quantum(0),
      contadorQuantum(0),
      isPaused(true),
      ejecucion(nullptr)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Scheduler::tick);
    inicializarMemoria();
}

Scheduler::~Scheduler()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void Scheduler::inicializarMemoria() {
    for (int i = 0; i < 48; i++) {
        if (i < 4) { 
            memoria[i].idProceso = -2; // SO
            memoria[i].libre = false;
            memoria[i].numeroPagina = -1;
            memoria[i].espacioOcupado = 5;
        } else {
            memoria[i].idProceso = -1;
            memoria[i].libre = true;
            memoria[i].numeroPagina = -1;
            memoria[i].espacioOcupado = 0;
        }
    }
    marcosLibres = 44;
}

bool Scheduler::hayEspacioPara(int tamanio) {
    int paginasNecesarias = (tamanio + 4) / 5; 
    return marcosLibres >= paginasNecesarias;
}

void Scheduler::asignarMemoria(Proceso* p) {
    int tamTotal = p->dameTamanio();
    int paginasNecesarias = (tamTotal + 4) / 5;
    int paginasAsignadas = 0;

    for (int i = 4; i < 48 && paginasAsignadas < paginasNecesarias; i++) {
        if (memoria[i].libre) {
            memoria[i].libre = false;
            memoria[i].idProceso = p->dameID();
            memoria[i].numeroPagina = paginasAsignadas;
            if (paginasAsignadas == paginasNecesarias - 1) {
                int residuo = tamTotal % 5;
                memoria[i].espacioOcupado = (residuo == 0) ? 5 : residuo;
            } else {
                memoria[i].espacioOcupado = 5;
            }
            paginasAsignadas++;
            marcosLibres--;
        }
    }
}

void Scheduler::liberarMemoria(Proceso* p) {
    for (int i = 4; i < 48; i++) {
        if (memoria[i].idProceso == p->dameID()) {
            memoria[i].libre = true;
            memoria[i].idProceso = -1;
            memoria[i].numeroPagina = -1;
            memoria[i].espacioOcupado = 0;
            marcosLibres++;
        }
    }
}

void Scheduler::startSimulation(int initialProcesses, int quantum)
{
    this->quantum = quantum;
    this->contadorGlobal = 0;
    this->contadorQuantum = 0;
    this->ejecucion = nullptr;

    inicializarMemoria();

    gestorProcesos.clear();
    nuevos = StaticQueue<Proceso>();
    pendientes = StaticQueue<Proceso>();
    bloqueado = StaticQueue<Proceso>();
    terminado = StaticQueue<Proceso>();

    for(int i = 0; i < initialProcesses; i++) {   
        Proceso p = generarDatos(gestorProcesos);
        gestorProcesos.push_back(p);
    }
    
    bubbleSort(gestorProcesos);

    for(Proceso& p : gestorProcesos) {
        p.fijaEstado(estadoProceso::NUEVO);
        p.dameReloj().setArriveTime(0);
        nuevos.enqueue(&p);
    }

    isPaused = false;
    timer->start(1000);
}

void Scheduler::pauseSimulation()
{
    isPaused = true;
    timer->stop();
    emit simulationUpdated();
}

void Scheduler::resumeSimulation()
{
    isPaused = false;
    timer->start(1000);
}

void Scheduler::injectProcess()
{
    Proceso p = generarDatos(gestorProcesos);
    gestorProcesos.push_back(p);
    Proceso* p_ptr = &gestorProcesos.back();
    if (hayEspacioPara(p_ptr->dameTamanio())) {
        asignarMemoria(p_ptr);
        p_ptr->fijaEstado(estadoProceso::LISTO);
        if(p_ptr->dameReloj().getArriveTime() == -1)
             p_ptr->dameReloj().setArriveTime(contadorGlobal);
             
        pendientes.enqueue(p_ptr);
    } 
    else {
        p_ptr->fijaEstado(estadoProceso::NUEVO);
        nuevos.enqueue(p_ptr);
    }
}

void Scheduler::interruptProcess()
{
    if (ejecucion != nullptr) {
        qDebug() << "Bloqueo de Proceso ID: " << ejecucion->dameID();
        ejecucion->fijaEstado(estadoProceso::BLOQUEADO);
        ejecucion->dameReloj().setBlockedTime(8);
        bloqueado.enqueue(ejecucion);
        ejecucion = nullptr;
        contadorQuantum = 0;
        emit simulationUpdated();
    }
}

void Scheduler::errorProcess()
{
    if (ejecucion != nullptr) {
        qDebug() << "Error en Proceso ID: " << ejecucion->dameID();
        ejecucion->fijaEstado(estadoProceso::TERMINADO);
        ejecucion->dameCalculadora().fijaResultado(std::numeric_limits<float>::quiet_NaN());
        ejecucion->dameReloj().setEndTime(contadorGlobal);
        ejecucion->dameReloj().calcReturnTime();
        liberarMemoria(ejecucion);
        terminado.enqueue(ejecucion);
        ejecucion = nullptr;
        contadorQuantum = 0;
        emit simulationUpdated();
    }
}

void Scheduler::tick()
{
    if (isPaused) return;

    manejarProcesosBloqueados();
    cargarNuevosAListos();
    manejarProcesoEnEjecucion();
    
    contadorGlobal++;
    emit simulationUpdated();
    
    // 7. Checar parada
    if (nuevos.isEmpty() && pendientes.isEmpty() && bloqueado.isEmpty() && ejecucion == nullptr) {
        timer->stop();
        emit simulationFinished();
    }
}

void Scheduler::cargarNuevosAListos()
{
    while (!nuevos.isEmpty() && hayEspacioPara(nuevos.getFront()->dameTamanio())) {
        Proceso* p = nuevos.getFront();
        nuevos.dequeue();
        
        asignarMemoria(p);
        p->fijaEstado(estadoProceso::LISTO);
        p->dameReloj().setArriveTime(contadorGlobal);
        pendientes.enqueue(p);
    }
}

void Scheduler::manejarProcesoEnEjecucion()
{
    if (!pendientes.isEmpty()) {
        const deque<Proceso*>& listaListos = pendientes.getData();
        for (Proceso* p : listaListos) {
            int esperaActual = p->dameReloj().getWaitingTime();
            p->dameReloj().setWaitingTime(esperaActual + 1);
        }
    }

    if (ejecucion == nullptr && !pendientes.isEmpty()) {
        ejecucion = pendientes.getFront();
        pendientes.dequeue();
        ejecucion->fijaEstado(estadoProceso::EJECUCION);
        contadorQuantum = 0;

        if (ejecucion->dameReloj().getResponseTime() == -1) {
            int tiempoLlegada = ejecucion->dameReloj().getArriveTime();
            ejecucion->dameReloj().setResponseTime(contadorGlobal - tiempoLlegada);
        }
    }

    if (ejecucion != nullptr) {
        ejecucion->dameReloj().calcElapsedTime();
        ejecucion->dameReloj().calcServiceTime();
        contadorQuantum++;

        int tiempoTranscurrido = ejecucion->dameReloj().getElapsedTime();
        int tiempoEstimado = ejecucion->dameReloj().getEstimatedTimeAmount();

        if (tiempoTranscurrido >= tiempoEstimado) {
            ejecucion->fijaEstado(estadoProceso::TERMINADO);
            ejecucion->dameCalculadora().operar();
            ejecucion->dameReloj().setEndTime(contadorGlobal); 
            ejecucion->dameReloj().calcReturnTime();
            
            liberarMemoria(ejecucion);
            terminado.enqueue(ejecucion);
            ejecucion = nullptr;
            contadorQuantum = 0;
        }
        else if (contadorQuantum >= quantum) {
            ejecucion->fijaEstado(estadoProceso::LISTO);
            pendientes.enqueue(ejecucion);
            ejecucion = nullptr;
            contadorQuantum = 0;
        }
    }
}

void Scheduler::manejarProcesosBloqueados()
{
    int nBloqueados = bloqueado.size();
    for (int i = 0; i < nBloqueados; i++) {
        Proceso* proc = bloqueado.getFront();
        bloqueado.dequeue();
        
        int tiempoRestante = proc->dameReloj().decreaseBlockedTime();

        if (tiempoRestante <= 0) {
            proc->fijaEstado(estadoProceso::LISTO);
            pendientes.enqueue(proc);
        } else {
            bloqueado.enqueue(proc);
        }
    }
}

int Scheduler::getContadorGlobal() const { return contadorGlobal; }
Proceso* Scheduler::getProcesoEnEjecucion() const { return ejecucion; }
StaticQueue<Proceso>& Scheduler::getNuevosQueue() { return nuevos; }
StaticQueue<Proceso>& Scheduler::getListosQueue() { return pendientes; }
StaticQueue<Proceso>& Scheduler::getBloqueadosQueue() { return bloqueado; }
StaticQueue<Proceso>& Scheduler::getTerminadosQueue() { return terminado; }
const deque<Proceso>& Scheduler::getGestorProcesos() const { return gestorProcesos; }