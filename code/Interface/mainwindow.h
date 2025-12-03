#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QTableWidget>
#include <QTextEdit>
#include <QSpinBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include "../Scheduler/scheduler.h"
#include "../TablaBCP/bcpwindow.h"
#include "../TablaMemoria/memorywindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    
private slots:
    // Slots para actualizar la UI
    void onSimulationUpdated();
    void onSimulationFinished();
    void onBcpDataReady(const deque<Proceso>& procesos);

    // Slots para los botones 
    void onStartClicked();
    void onPauseResumeClicked();
    void onInjectClicked();
    void onInterruptClicked();
    void onErrorClicked();
    void onShowBcpClicked();


private:
    void setupUI();
    void updateProcessLists();
    void updateProcessInExecution();
    void updateMemoryTable();

    Scheduler *scheduler;

    QWidget *centralWidget;
    // Controles
    QLabel *quantumLabel;
    QSpinBox *quantumSpinBox;
    QLabel *initialProcessLabel;
    QSpinBox *initialProcessSpinBox;
    QPushButton *startButton;
    QPushButton *pauseResumeButton;
    QLabel *globalCounterLabel;
    
    // Botones de Interrupción
    QPushButton *injectButton;
    QPushButton *interruptButton;
    QPushButton *errorButton;
    QPushButton *showBcpButton;
    
    // Vistas de Procesos
    QTableWidget *listosTable;
    QTableWidget *bloqueadosTable;
    QTableWidget *terminadosTable;
    QTableWidget *memoriaTable;
    QTextEdit *ejecucionText;
    QLabel *nuevosLabel;
    QLabel *suspendidosLabel;
    QLabel *framesLabel;
};