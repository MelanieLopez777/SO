#include "generadorDatos.h"

Proceso generarDatos(const deque<Proceso>& gestor)
{
    int numeroAleatorio, operandoA, operandoB, operacion;
    Proceso nuevo;

    do{
        numeroAleatorio = MIN_ID + (rand() % (MAX_ID - MIN_ID + 1));

    }while(!validarID(numeroAleatorio, gestor));
    nuevo.fijaID(numeroAleatorio);

    numeroAleatorio = MIN_TAM_PROCESS + (rand() % (MAX_TAM_PROCESS - MIN_TAM_PROCESS + 1));
    nuevo.fijaTamanio(numeroAleatorio);
    numeroAleatorio = MIN_TME + (rand() % (MAX_TME - MIN_TME + 1));
    nuevo.dameReloj().setEstimatedTimeAmount(numeroAleatorio);
    nuevo.dameReloj().setElapsedTime(0);
    numeroAleatorio = 1 + (rand() % (6));
    nuevo.dameCalculadora().fijaOperador(numeroAleatorio);
    operandoA = RANGO_OPERANDO_MAX + (rand() % (RANGO_OPERANDO_MAX - RANGO_OPERANDO_MIN));
    operacion = nuevo.dameCalculadora().dameOperador();
    do
    {
      operandoB = RANGO_OPERANDO_MAX + (rand() % (RANGO_OPERANDO_MAX - RANGO_OPERANDO_MIN + 1));
    } while((operacion == DIVISION || operacion == RESIDUO) && operandoB == 0);
    nuevo.dameCalculadora().fijaValorA(operandoA);
    nuevo.dameCalculadora().fijaValorB(operandoB);

    return nuevo;
}

bool validarID(int id, const deque<Proceso>& gestor) {
    for (const auto& proceso : gestor) {
        if (id == proceso.dameID()) {
            qDebug() << "Intento de ID repetido: " << id;
            return false;
        }
    }
    return true;
}

void bubbleSort(deque<Proceso>& gestor)
{
    bool swapped;
    for (size_t i = 0; i < gestor.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < gestor.size() - i - 1; j++) {
            if (gestor[j].dameReloj().getEstimatedTimeAmount() > gestor[j + 1].dameReloj().getEstimatedTimeAmount()) {
                swap(gestor[j], gestor[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}