#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include "../Scheduler/scheduler.h"

class MemoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryWindow(const Marco* memoria, int marcosLibres, QWidget *parent = nullptr);

private:
    QTableWidget *tableWidget;
    QLabel *framesLabel;
    
    void configurarTabla();
    void cargarDatos(const Marco* memoria);
};