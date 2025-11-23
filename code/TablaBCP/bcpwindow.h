#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <deque>
#include <string>
#include <limits>
#include "../Structure/structures.h"

class BCPWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BCPWindow(const std::deque<Proceso>& procesos, QWidget *parent = nullptr);

private:
    QTableWidget *tableWidget;
    void configurarTabla();
    void cargarDatos(const std::deque<Proceso>& procesos);
};