#include "memorywindow.h"

MemoryWindow::MemoryWindow(const Marco* memoria, int marcosLibres, QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("Tabla de Paginación");
    this->resize(740, 855);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Mapa de Memoria (48 Marcos)");
    title->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);

    framesLabel = new QLabel(QString("Marcos Libres: %1/44").arg(marcosLibres));
    framesLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: darkgreen; margin-top: 5px;");
    framesLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(framesLabel);

    configurarTabla();
    cargarDatos(memoria);
}

void MemoryWindow::configurarTabla()
{
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels({"Marco", "Proceso", "Estado", "Uso", "Marco", "Proceso", "Estado", "Uso"});
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    int anchoMarco = 60;
    int anchoProceso = 120;
    int anchoEstado = 120;
    int anchoPag = 50;

    tableWidget->setColumnWidth(0, anchoMarco);
    tableWidget->setColumnWidth(1, anchoProceso);
    tableWidget->setColumnWidth(2, anchoEstado);
    tableWidget->setColumnWidth(3, anchoPag);
    tableWidget->setColumnWidth(4, anchoMarco);
    tableWidget->setColumnWidth(5, anchoProceso);
    tableWidget->setColumnWidth(6, anchoEstado);
    tableWidget->setColumnWidth(7, anchoPag);

    tableWidget->verticalHeader()->setDefaultSectionSize(30);
}

void MemoryWindow::cargarDatos(const Marco* memoria)
{
    tableWidget->setRowCount(24); // 24 filas x 2 columnas = 48 marcos

    auto llenarCelda = [&](int fila, int colOffset, int indexMemoria) {
        
        // 1. MARCO ID
        QTableWidgetItem* itemMarco = new QTableWidgetItem(QString::number(indexMemoria));
        itemMarco->setForeground(Qt::white);
        itemMarco->setBackground(QColor(50, 50, 50)); 
        itemMarco->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(fila, colOffset + 0, itemMarco);

        // Datos
        QString procesoStr;
        QString estadoStr;
        QString usoStr = "-";
        QColor colorFondo;
        const Marco& m = memoria[indexMemoria];

        if (m.idProceso == -2) { // SO
            procesoStr = "S.O.";
            colorFondo = QColor(200, 200, 200);
            estadoStr = "N/A";
            usoStr = "5/5";
        } else if (m.libre) { // Libre
            procesoStr = "Libre";
            colorFondo = QColor(200, 255, 200);
            estadoStr = "N/A";
        } else { // Ocupado
            procesoStr = QString("P%1").arg(m.idProceso);
            usoStr = QString("%1/5").arg(m.espacioOcupado);
            estadoStr = QString::fromStdString(m.estadoStr);
            colorFondo = QColor(100, 180, 255);
        }

        QTableWidgetItem* itemProceso = new QTableWidgetItem(procesoStr);
        itemProceso->setBackground(colorFondo);
        itemProceso->setForeground(Qt::black);
        itemProceso->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(fila, colOffset + 1, itemProceso);

        QTableWidgetItem* itemEstado = new QTableWidgetItem(estadoStr);
        itemEstado->setBackground(colorFondo);
        itemEstado->setForeground(Qt::black);
        itemEstado->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(fila, colOffset + 2, itemEstado);

        QTableWidgetItem* itemUso = new QTableWidgetItem(usoStr);
        itemUso->setBackground(colorFondo);
        itemUso->setForeground(Qt::black);
        itemUso->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(fila, colOffset + 3, itemUso);
    };

    for (int i = 0; i < 24; ++i) {
        llenarCelda(i, 0, i);      // Izquierda
        llenarCelda(i, 4, i + 24); // Derecha
    }
}