#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <deque>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../Structure/structures.h"
#include "../Queue/queue.h"
#include "../Generador/generadorDatos.h"

using namespace std;

struct Marco {
    int idProceso = -1;
    int numeroPagina = -1;
    int espacioOcupado = 0;
    bool libre = true;
    string estadoStr = "N/A";
};

class Scheduler : public QObject
{
    Q_OBJECT

public:
    explicit Scheduler(QObject *parent = nullptr);
    ~Scheduler();

    // Getters para la GUI
    int getContadorGlobal() const;
    Proceso* getProcesoEnEjecucion() const;
    StaticQueue<Proceso>& getNuevosQueue();
    StaticQueue<Proceso>& getListosQueue();
    StaticQueue<Proceso>& getBloqueadosQueue();
    StaticQueue<Proceso>& getSuspendidosQueue();
    StaticQueue<Proceso>& getTerminadosQueue();
    const deque<Proceso>& getGestorProcesos() const;
    const Marco* getMemoria() const { return memoria; }
    int getMarcosLibres() const { return marcosLibres; }

public slots:
    // Control de Simulación (Llamados por la GUI)
    void startSimulation(int initialProcesses, int quantum);
    void pauseSimulation();
    void resumeSimulation();
    
    // Interrupciones (Llamadas por la GUI)
    void injectProcess();
    void interruptProcess();
    void errorProcess();

    void suspendProcess();
    void returnProcess();

signals:
    // Notificaciones a la GUI
    void simulationUpdated();
    void simulationFinished();
    void bcpDataReady(const deque<Proceso>& procesos);

private slots:
    void tick();

private:
    QTimer *timer;
    int contadorGlobal;
    int quantum;
    int contadorQuantum;
    bool isPaused;

    Marco memoria[48]; 
    int marcosLibres;

    deque<Proceso> gestorProcesos;
    StaticQueue<Proceso> nuevos;
    StaticQueue<Proceso> pendientes;
    StaticQueue<Proceso> bloqueado;
    StaticQueue<Proceso> suspendidos;
    StaticQueue<Proceso> terminado;
    Proceso *ejecucion;

    void inicializarMemoria();
    void actualizarEstadoEnMarcos(int id, string nuevoEstado);
    bool hayEspacioPara(int tamanio);
    void asignarMemoria(Proceso* p);
    void liberarMemoria(Proceso* p);
    void guardarArchivoSuspendidos();

    void cargarNuevosAListos();
    void manejarProcesoEnEjecucion();
    void manejarProcesosBloqueados();
};