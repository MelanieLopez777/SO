#include "generadorDatos.h"

Proceso gestor[TAM_PROCESOS];
int contadorProcesos = 0;

void generarDatos()
{
    int numeroAleatorio, operandoA, operandoB, operacion;

    srand(time(0));

    //Generación de ID aleatorio//
    do{
        numeroAleatorio = MIN_ID + (rand() % (MAX_ID - MIN_ID + 1));

    }while(!validarID(numeroAleatorio)); 
    gestor[contadorProcesos].fijaID(numeroAleatorio);

    //Generación de TME aleatorio//

    numeroAleatorio = MIN_TME + (rand() % (MAX_TME - MIN_TME + 1));
    gestor[contadorProcesos].dameReloj().setEstimatedTimeAmount(numeroAleatorio);
    gestor[contadorProcesos].dameReloj().setElapsedTime(0);

    //Generación de operación aleatoria//
    numeroAleatorio = 1 + (rand() % (6));
    gestor[contadorProcesos].dameCalculadora().fijaOperador(numeroAleatorio);
    

    //Generación de operandos para operaciones
    operandoA = RANGO_OPERANDO_MAX + (rand() % (RANGO_OPERANDO_MAX - RANGO_OPERANDO_MIN));
    operacion = gestor[contadorProcesos].dameCalculadora().dameOperador();

    do
    {
      operandoB = RANGO_OPERANDO_MAX + (rand() % (RANGO_OPERANDO_MAX - RANGO_OPERANDO_MIN + 1));
    } while((operacion == DIVISION || operacion == RESIDUO) && operandoB == 0);

    gestor[contadorProcesos].dameCalculadora().fijaValorA(operandoA);
    gestor[contadorProcesos].dameCalculadora().fijaValorB(operandoB);


    contadorProcesos++;
}

bool validarID(int &id)
{
    for (int i = 0; i < contadorProcesos; i++)  
    {
        if (id == gestor[i].dameID())
        {
            cout << "Número de identificación repetido" << endl;
            return false; 
        }
    }
    return true; 
}

// Función para realizar el Bubble Sort
void bubbleSort(int cantidadProcesos)
{
    bool swapped; 
    for (int i = 0; i < cantidadProcesos- 1; ++i) {
        swapped = false;

        for (int j = 0; j < cantidadProcesos - 1 - i; ++j) {
            if (gestor[j].dameID() > gestor[j + 1].dameID()) {

                swap(gestor[j], gestor[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
