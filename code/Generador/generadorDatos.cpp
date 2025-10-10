#include "generadorDatos.h"

vector<Proceso> gestor;

Proceso generarDatos()
{
    int numeroAleatorio, operandoA, operandoB, operacion;
    Proceso nuevo;

    //Generación de ID aleatorio//
    do{
        numeroAleatorio = MIN_ID + (rand() % (MAX_ID - MIN_ID + 1));

    }while(!validarID(numeroAleatorio)); 
    nuevo.fijaID(numeroAleatorio);

    //Generación de TME aleatorio//

    numeroAleatorio = MIN_TME + (rand() % (MAX_TME - MIN_TME + 1));
    nuevo.dameReloj().setEstimatedTimeAmount(numeroAleatorio);
    nuevo.dameReloj().setElapsedTime(0);

    //Generación de operación aleatoria//
    numeroAleatorio = 1 + (rand() % (6));
    nuevo.dameCalculadora().fijaOperador(numeroAleatorio);
    

    //Generación de operandos para operaciones
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

bool validarID(int& id) {
    for (const auto& proceso : gestor) {
        if (id == proceso.dameID()) {
            cout << "Número de identificación repetido" << endl;
            return false;
        }
    }
    return true;
}

void bubbleSort()
{
    bool swapped;
    for (int i = 0; i < gestor.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < gestor.size() - 1 - i; ++j) {
            if (gestor[j].dameID() > gestor[j + 1].dameID()) {
                swap(gestor[j], gestor[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
