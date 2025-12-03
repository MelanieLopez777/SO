#include "../Interface/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scheduler = new Scheduler(this);
    setupUI();

    // Conectar Señales del motor a Slots de la GUI
    connect(scheduler, &Scheduler::simulationUpdated, this, &MainWindow::onSimulationUpdated);
    connect(scheduler, &Scheduler::simulationFinished, this, &MainWindow::onSimulationFinished);
    connect(scheduler, &Scheduler::bcpDataReady, this, &MainWindow::onBcpDataReady);
}

MainWindow::~MainWindow()
{
    // El 'scheduler' es hijo de 'MainWindow', Qt lo borra automáticamente
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    setWindowTitle("Simulador de Planificación Round Robin");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *controlLayout = new QHBoxLayout;
    QGridLayout *processLayout = new QGridLayout;
    QHBoxLayout *interruptLayout = new QHBoxLayout;

    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(processLayout);
    mainLayout->addLayout(interruptLayout);

    initialProcessLabel = new QLabel("Procesos Iniciales:");
    initialProcessSpinBox = new QSpinBox;
    initialProcessSpinBox->setRange(1, 100);
    initialProcessSpinBox->setValue(4);
    
    quantumLabel = new QLabel("Quantum:");
    quantumSpinBox = new QSpinBox;
    quantumSpinBox->setRange(1, 10);
    quantumSpinBox->setValue(3);

    startButton = new QPushButton("Iniciar");
    pauseResumeButton = new QPushButton("Pausar");
    pauseResumeButton->setEnabled(false);

    globalCounterLabel = new QLabel("Tiempo Global: 0");
    globalCounterLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    controlLayout->addWidget(initialProcessLabel);
    controlLayout->addWidget(initialProcessSpinBox);
    controlLayout->addWidget(quantumLabel);
    controlLayout->addWidget(quantumSpinBox);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(pauseResumeButton);
    controlLayout->addStretch();
    controlLayout->addWidget(globalCounterLabel);

    listosTable = new QTableWidget;
    listosTable->setColumnCount(4);
    listosTable->setHorizontalHeaderLabels({"ID", "TME", "TT", "TAM"});
    listosTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    listosTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listosTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    listosTable->setFocusPolicy(Qt::NoFocus);

    bloqueadosTable = new QTableWidget;
    bloqueadosTable->setColumnCount(2);
    bloqueadosTable->setHorizontalHeaderLabels({"ID", "TB"});
    bloqueadosTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    bloqueadosTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bloqueadosTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    bloqueadosTable->setFocusPolicy(Qt::NoFocus);

    terminadosTable = new QTableWidget;
    terminadosTable->setColumnCount(3);
    terminadosTable->setHorizontalHeaderLabels({"ID", "Operación", "Resultado"});
    terminadosTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ejecucionText = new QTextEdit;
    ejecucionText->setReadOnly(true);
    ejecucionText->setPlaceholderText("Proceso en Ejecución...");

    terminadosTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    terminadosTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    terminadosTable->setFocusPolicy(Qt::NoFocus);

    memoriaTable = new QTableWidget;
    memoriaTable->setColumnCount(6); 
    memoriaTable->setHorizontalHeaderLabels({"Marco", "Estado", "Uso", "Marco", "Estado", "Uso"});
    
    memoriaTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memoriaTable->verticalHeader()->setVisible(false);
    memoriaTable->setSelectionMode(QAbstractItemView::NoSelection);
    memoriaTable->setMinimumWidth(410); 
    memoriaTable->setMinimumHeight(755);
    memoriaTable->setColumnWidth(0, 50); // Marco ID
    memoriaTable->setColumnWidth(1, 90); // Estado
    memoriaTable->setColumnWidth(2, 40); // Uso
    memoriaTable->setColumnWidth(3, 50); // Marco ID
    memoriaTable->setColumnWidth(4, 90); // Estado
    memoriaTable->setColumnWidth(5, 40); // Uso
    
    nuevosLabel = new QLabel("Procesos Nuevos: 0");
    suspendidosLabel = new QLabel("Procesos suspendidos: 0");
    framesLabel = new QLabel("Marcos Libres: 44/44");
    framesLabel->setStyleSheet("font-weight: bold; color: darkgreen;");

    processLayout->addWidget(new QLabel("Listos"), 0, 0);
    processLayout->addWidget(listosTable, 1, 0);
    processLayout->addWidget(new QLabel("Bloqueados"), 0, 1);
    processLayout->addWidget(bloqueadosTable, 1, 1);
    processLayout->addWidget(new QLabel("Terminados"), 2, 0);
    processLayout->addWidget(terminadosTable, 3, 0);
    processLayout->addWidget(new QLabel("En Ejecución"), 2, 1);
    processLayout->addWidget(ejecucionText, 3, 1);
    processLayout->addWidget(nuevosLabel, 4, 0);
    processLayout->addWidget(suspendidosLabel, 4, 1);
    processLayout->addWidget(new QLabel("Mapa de Memoria (Paginación)"), 0, 2, 1, 2);
    processLayout->addWidget(memoriaTable, 1, 2, 4, 2);
    processLayout->addWidget(framesLabel, 5, 2);
    
    injectButton = new QPushButton("Crear Proceso (N)");
    interruptButton = new QPushButton("Bloquear (E)");
    errorButton = new QPushButton("Error (W)");
    showBcpButton = new QPushButton("Mostrar BCP (B)");

    injectButton->setShortcut(QKeySequence(Qt::Key_N));
    interruptButton->setShortcut(QKeySequence(Qt::Key_E));
    errorButton->setShortcut(QKeySequence(Qt::Key_W));
    showBcpButton->setShortcut(QKeySequence(Qt::Key_B));

    interruptLayout->addWidget(injectButton);
    interruptLayout->addWidget(interruptButton);
    interruptLayout->addWidget(errorButton);
    interruptLayout->addWidget(showBcpButton);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(pauseResumeButton, &QPushButton::clicked, this, &MainWindow::onPauseResumeClicked);
    connect(injectButton, &QPushButton::clicked, this, &MainWindow::onInjectClicked);
    connect(interruptButton, &QPushButton::clicked, this, &MainWindow::onInterruptClicked);
    connect(errorButton, &QPushButton::clicked, this, &MainWindow::onErrorClicked);
    connect(showBcpButton, &QPushButton::clicked, this, &MainWindow::onShowBcpClicked);
}


void MainWindow::onSimulationUpdated()
{
    // Actualiza el contador global
    globalCounterLabel->setText(QString("Tiempo Global: %1").arg(scheduler->getContadorGlobal()));
    // Actualiza el contador de procesos nuevos
    int nuevosCount = scheduler->getNuevosQueue().size();
    nuevosLabel->setText(QString("Procesos Nuevos: %1").arg(nuevosCount));
    // Actualiza la información del proceso en ejecución
    updateProcessInExecution();
    // Actualiza todas las tablas (Listos, Bloqueados, Terminados)
    updateProcessLists();
    // Actualiza tabla de paginación
    updateMemoryTable();
}

void MainWindow::onSimulationFinished()
{
    QMessageBox::information(this, "Simulación Terminada", "Todos los procesos han finalizado.");
    pauseResumeButton->setText("Pausar");
    pauseResumeButton->setEnabled(false);
    startButton->setEnabled(true);
}

void MainWindow::onBcpDataReady(const deque<Proceso>& procesos)
{
    QMessageBox::information(this, "BCP", "Aquí se mostraría la tabla BCP (ver consola de depuración).");
    qDebug() << "TABLA BCP";
    for (const Proceso& p : procesos) {
         qDebug() << "ID:" << p.dameID() << "Estado:" << (int)p.dameEstado();
    }
}

void MainWindow::onStartClicked()
{
    int numProcesos = initialProcessSpinBox->value();
    int quantum = quantumSpinBox->value();
    
    scheduler->startSimulation(numProcesos, quantum);
    updateMemoryTable();
    
    startButton->setEnabled(false);
    pauseResumeButton->setEnabled(true);
    pauseResumeButton->setText("Pausar");
}

void MainWindow::onPauseResumeClicked()
{
    if (pauseResumeButton->text() == "Pausar") {
        scheduler->pauseSimulation();
        pauseResumeButton->setText("Reanudar");
    } else {
        scheduler->resumeSimulation();
        pauseResumeButton->setText("Pausar");
    }
}

void MainWindow::onInjectClicked() { scheduler->injectProcess(); }
void MainWindow::onInterruptClicked() { scheduler->interruptProcess(); }
void MainWindow::onErrorClicked() { scheduler->errorProcess(); }
void MainWindow::onShowBcpClicked()
{
    scheduler->pauseSimulation();
    const deque<Proceso>& todosLosProcesos = scheduler->getGestorProcesos();
    BCPWindow bcpVentana(todosLosProcesos, this);
    bcpVentana.exec();
    pauseResumeButton->setText("Reanudar");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!scheduler || !pauseResumeButton->isEnabled()) {
        QWidget::keyPressEvent(event); 
        return;
    }

    switch (event->key()) {
        case Qt::Key_P:
            scheduler->pauseSimulation();
            pauseResumeButton->setText("Reanudar");
            break;

        case Qt::Key_C:
            scheduler->resumeSimulation();
            pauseResumeButton->setText("Pausar");
            break;

        case Qt::Key_T:
        {
            scheduler->pauseSimulation();
            pauseResumeButton->setText("Reanudar");
            const Marco* memoriaActual = scheduler->getMemoria();
            int libres = scheduler->getMarcosLibres();
            MemoryWindow memWin(memoriaActual, libres, this);
            memWin.exec(); 
            break;
        }
    
        case Qt::Key_S:
            scheduler->suspendProcess();
            if (!scheduler->getSuspendidosQueue().isEmpty())
            {
                // Obtenemos el puntero al proceso siguiente (el del frente)
                Proceso* siguiente = scheduler->getSuspendidosQueue().getFront();

                suspendidosLabel->setText(
                    "Procesos Suspendidos: " + QString::number(scheduler->getSuspendidosQueue().size()) + "\n" +
                    "Proceso Siguiente: ID " + QString::number(siguiente->dameID())  + " | Tam " + QString::number(siguiente->dameTamanio())
                );
            }
            else
            {
                suspendidosLabel->setText("Procesos Suspendidos: " + QString::number(scheduler->getSuspendidosQueue().size()));
            }
            break;
            
        case Qt::Key_R:
            scheduler->returnProcess();
            if (!scheduler->getSuspendidosQueue().isEmpty())
            {
                // Obtenemos el puntero al proceso siguiente (el del frente)
                Proceso* siguiente = scheduler->getSuspendidosQueue().getFront();

                suspendidosLabel->setText(
                    "Procesos Suspendidos: " + QString::number(scheduler->getSuspendidosQueue().size()) + "\n" +
                    "Proceso Siguiente (ID): " + QString::number(siguiente->dameID()) + " | Tam " + QString::number(siguiente->dameTamanio())
                );
            }
            else
            {
                suspendidosLabel->setText("Procesos Suspendidos: " + QString::number(scheduler->getSuspendidosQueue().size()));
            }
            break;

        default:
            QWidget::keyPressEvent(event);
    }
}

void MainWindow::updateProcessInExecution()
{
    Proceso* p = scheduler->getProcesoEnEjecucion();
    if (p != nullptr) {
        ejecucionText->setText(QString::fromStdString(p->toString(estadoProceso::EJECUCION)));
    } else {
        ejecucionText->setText("");
    }
}

void MainWindow::updateProcessLists()
{
    // Actualizar Tabla de LISTOS
    StaticQueue<Proceso>& listos = scheduler->getListosQueue();
    listosTable->setRowCount(listos.size());
    const auto& listosData = listos.getData();
    for (int i = 0; i < listosData.size(); ++i) {
        Proceso* p = listosData[i];
        listosTable->setItem(i, 0, new QTableWidgetItem(QString::number(p->dameID())));
        listosTable->setItem(i, 1, new QTableWidgetItem(QString::number(p->dameReloj().getEstimatedTimeAmount())));
        listosTable->setItem(i, 2, new QTableWidgetItem(QString::number(p->dameReloj().getElapsedTime())));
        listosTable->setItem(i, 3, new QTableWidgetItem(QString::number(p->dameTamanio())));
    }

    // Actualizar Tabla de BLOQUEADOS
    StaticQueue<Proceso>& bloqueados = scheduler->getBloqueadosQueue();
    bloqueadosTable->setRowCount(bloqueados.size());
    const auto& bloqueadosData = bloqueados.getData();
    for (int i = 0; i < bloqueadosData.size(); ++i) {
        Proceso* p = bloqueadosData[i];
        bloqueadosTable->setItem(i, 0, new QTableWidgetItem(QString::number(p->dameID())));
        bloqueadosTable->setItem(i, 1, new QTableWidgetItem(QString::number(p->dameReloj().getBlockedTime())));
    }

    // Actualizar Tabla de TERMINADOS
    StaticQueue<Proceso>& terminados = scheduler->getTerminadosQueue();
    terminadosTable->setRowCount(terminados.size());
    const auto& terminadosData = terminados.getData();
    for (int i = 0; i < terminadosData.size(); ++i) {
        Proceso* p = terminadosData[i];
        terminadosTable->setItem(i, 0, new QTableWidgetItem(QString::number(p->dameID())));
        terminadosTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p->dameCalculadora().operacionToString())));
        
        float res = p->dameCalculadora().dameResultado();
        QString resStr = std::isnan(res) ? "ERROR" : QString::number(res);
        terminadosTable->setItem(i, 2, new QTableWidgetItem(resStr));
    }
}

void MainWindow::updateMemoryTable()
{
    const Marco* memoria = scheduler->getMemoria();
    memoriaTable->setRowCount(24);

    auto llenarCelda = [&](int fila, int colOffset, int indexMemoria) {
        
        QTableWidgetItem* itemMarco = new QTableWidgetItem(QString::number(indexMemoria));
        itemMarco->setForeground(Qt::white);
        itemMarco->setBackground(QColor(50, 50, 50));
        itemMarco->setTextAlignment(Qt::AlignCenter);
        memoriaTable->setItem(fila, colOffset + 0, itemMarco);

        QString estadoStr;
        QString paginaStr = "-";
        QColor colorFondo;
        
        const Marco& m = memoria[indexMemoria];

        if (m.idProceso == -2) { // S.O. Gris
            estadoStr = "S.O.";
            colorFondo = QColor(200, 200, 200);
        } 
        else if (m.libre) { // Libre Verde
            estadoStr = "Libre";
            colorFondo = QColor(200, 255, 200);
        } 
        else { // Proceso Azul
            estadoStr = QString("P%1").arg(m.idProceso);
            paginaStr = QString::number(m.numeroPagina);
            colorFondo = QColor(100, 180, 255);
        }

        QTableWidgetItem* itemEstado = new QTableWidgetItem(estadoStr);
        itemEstado->setBackground(colorFondo);
        itemEstado->setForeground(Qt::black);
        itemEstado->setTextAlignment(Qt::AlignCenter);
        memoriaTable->setItem(fila, colOffset + 1, itemEstado);

        QString usoStr = "-";
    
        if (m.idProceso == -2) { // SO
            usoStr = "5/5";
        }
        else if (!m.libre) { // Proceso
            usoStr = QString("%1/5").arg(m.espacioOcupado);
        }

        QTableWidgetItem* itemUso = new QTableWidgetItem(usoStr);
        itemUso->setBackground(colorFondo);
        itemUso->setForeground(Qt::black);
        itemUso->setTextAlignment(Qt::AlignCenter);
        memoriaTable->setItem(fila, colOffset + 2, itemUso);
    };

    for (int i = 0; i < 24; ++i) {
        // Lado Izquierdo (Marcos 0-23) -> Columnas 0, 1, 2
        llenarCelda(i, 0, i);
        // Lado Derecho (Marcos 24-47) -> Columnas 3, 4, 5
        llenarCelda(i, 3, i + 24);
    }
    
    int libres = scheduler->getMarcosLibres();
    framesLabel->setText(QString("Marcos Libres: %1/44").arg(libres));
}