#include "bcpwindow.h"

BCPWindow::BCPWindow(const std::deque<Proceso>& procesos, QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("BCP - Bloque de Control de Procesos");
    this->resize(1100, 500); 

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);

    configurarTabla();
    cargarDatos(procesos);
}

void BCPWindow::configurarTabla()
{
    QStringList headers;
    headers << "ID" << "Estado" << "Operación" << "Resultado" << "TME" 
            << "T. Llegada" << "T. Fin" << "T. Retorno" 
            << "T. Respuesta" << "T. Espera" << "T. Servicio";

    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void BCPWindow::cargarDatos(const std::deque<Proceso>& procesos)
{
    tableWidget->setRowCount(procesos.size());

    for (size_t i = 0; i < procesos.size(); ++i) {
        Proceso p = procesos[i]; 
        Clock clk = p.dameReloj();
        Calculadora calc = p.dameCalculadora();
        estadoProceso estado = p.dameEstado();

        QString estadoStr = QString::fromStdString(p.estadoToString());

        QString resultadoStr = "N/A";
        if (estado == estadoProceso::TERMINADO) {
             if (calc.dameResultado() == std::numeric_limits<float>::lowest()) 
                resultadoStr = "ERROR";
             else
                resultadoStr = QString::number(calc.dameResultado());
        }

        auto formatTime = [](int val) -> QString {
            return (val == -1) ? "N/A" : QString::number(val);
        };

        int col = 0;
        tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(p.dameID())));
        tableWidget->setItem(i, col++, new QTableWidgetItem(estadoStr));
        tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromStdString(calc.operacionToString())));
        tableWidget->setItem(i, col++, new QTableWidgetItem(resultadoStr));
        tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(clk.getEstimatedTimeAmount())));
        tableWidget->setItem(i, col++, new QTableWidgetItem(formatTime(clk.getArriveTime())));
        tableWidget->setItem(i, col++, new QTableWidgetItem(formatTime(clk.getEndTime())));
        tableWidget->setItem(i, col++, new QTableWidgetItem(formatTime(clk.getReturnTime()))); // T. Retorno
        tableWidget->setItem(i, col++, new QTableWidgetItem(formatTime(clk.getResponseTime()))); // T. Respuesta
        tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(clk.getWaitingTime()))); // T. Espera
        tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(clk.getElapsedTime()))); // T. Servicio
    }
}