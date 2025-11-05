#include <iostream>                 
#include <thread>                   
#include <mutex>                    
#include <condition_variable>       
#include <vector>                   
#include <chrono>                   
#include <cstdlib>                  
#include <ctime>                    
#include "Constants/constants.h"    // Debe definir BUFFER_SIZE y CLEAR (ejemplo: #define CLEAR "cls" o "clear")

using namespace std;

// ==========================================================
// CONFIGURACIÓN DEL PROGRAMA
// ==========================================================
vector<char> buffer(BUFFER_SIZE, '_');   // Buffer circular de 18 posiciones

int in = 0;                              // Índice de inserción del productor
int out = 0;                             // Índice de extracción del consumidor
int countBuffer = 0;                     // Elementos actualmente en el buffer

mutex mtx;                               // Mutex para proteger el acceso compartido
condition_variable not_full;             // Variable de condición (buffer no lleno)
condition_variable not_empty;            // Variable de condición (buffer no vacío)

bool stopSimulation = false;             // Señal para detener la simulación

// Estados actuales del productor y consumidor
string estadoProductor = "Inactivo";
string estadoConsumidor = "Inactivo";

// ==========================================================
// FUNCIÓN: mostrarPantalla()
// Limpia la consola y muestra TODO el estado del sistema:
// - Contenedor (con índices)
// - Estado del productor y consumidor
// ==========================================================
void mostrarPantalla() {
    system(CLEAR);  // Se mantiene el requisito de limpiar la pantalla
    // Mostrar el contenedor
    cout << endl << "Contenedor:  ";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        cout << buffer[i];
        if (i >= 9) {
            cout << "   ";
        }
        else {
            cout << "  ";
        }
    }
    cout << endl;
    cout << "             ";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        cout << i + 1 << "  ";
    }
    cout << endl;
    cout << "\n------------------------------------------------------" << endl;

    // Mostrar estados
    cout << "Productor: " << estadoProductor << endl;
    cout << "Consumidor: " << estadoConsumidor << endl;
    cout << "Elementos actuales en el buffer: " << countBuffer << "/" << BUFFER_SIZE << endl;
    cout << "------------------------------------------------------" << endl;
}

// ==========================================================
// FUNCIÓN: productor()
// Produce entre 3 y 6 elementos con pausas aleatorias
// ==========================================================
void productor() {
    while (!stopSimulation) {
        // 1️⃣ Dormir entre 500 y 1500 ms
        int sleepTime = 500 + rand() % 1000;
        estadoProductor = "Durmiendo (" + to_string(sleepTime) + " ms)";

        this_thread::sleep_for(chrono::milliseconds(sleepTime));

        // 2️⃣ Intentar entrar al contenedor
        unique_lock<mutex> lock(mtx);
        estadoProductor = "Intentando entrar al contenedor...";


        // 3️⃣ Esperar si está lleno
        not_full.wait(lock, [] { return countBuffer < BUFFER_SIZE; });

        // 4️⃣ Determinar cuántos elementos producir
        int itemsToProduce = 3 + rand() % 4;
        estadoProductor = "Produciendo " + to_string(itemsToProduce) + " elementos...";

        // 5️⃣ Producir
        for (int i = 0; i < itemsToProduce && countBuffer < BUFFER_SIZE; i++) {
            char item = 'A' + rand() % 26;
            buffer[in] = item;
            in = (in + 1) % BUFFER_SIZE;
            countBuffer++;

            mostrarPantalla();  // Redibuja todo el estado
            this_thread::sleep_for(chrono::milliseconds(400)); // Simula tiempo de producción
        }

        // 6️⃣ Terminar
        estadoProductor = "Terminó de producir (" + to_string(itemsToProduce) + ")";
        mostrarPantalla();

        lock.unlock();
        not_empty.notify_one();
    }
}

// ==========================================================
// FUNCIÓN: consumidor()
// Consume entre 3 y 6 elementos con pausas aleatorias
// ==========================================================
void consumidor() {
    while (!stopSimulation) {
        // 1️⃣ Dormir entre 700 y 1800 ms
        int sleepTime = 700 + rand() % 1100;
        estadoConsumidor = "Durmiendo (" + to_string(sleepTime) + " ms)";

        this_thread::sleep_for(chrono::milliseconds(sleepTime));

        // 2️⃣ Intentar acceder al buffer
        unique_lock<mutex> lock(mtx);
        estadoConsumidor = "Intentando entrar al contenedor";


        // 3️⃣ Esperar si está vacío
        not_empty.wait(lock, [] { return countBuffer > 0; });

        // 4️⃣ Determinar cuántos elementos consumir
        int itemsToConsume = 3 + rand() % 4;
        estadoConsumidor = "Consumiendo " + to_string(itemsToConsume) + " elementos";


        // 5️⃣ Consumir
        for (int i = 0; i < itemsToConsume && countBuffer > 0; i++) {
            buffer[out] = '_';
            out = (out + 1) % BUFFER_SIZE;
            countBuffer--;

            mostrarPantalla();  // Redibuja todo el sistema
            this_thread::sleep_for(chrono::milliseconds(400)); // Simula tiempo de consumo
        }

        // 6️⃣ Terminar
        estadoConsumidor = "Terminó de consumir (" + to_string(itemsToConsume) + ")";
        mostrarPantalla();

        lock.unlock();
        not_full.notify_one();
    }
}

// ==========================================================
// FUNCIÓN PRINCIPAL
// ==========================================================
int main() {
    srand(time(nullptr));
    // Crear los hilos
    thread prod(productor);
    thread cons(consumidor);

    // Ejecutar la simulación por 25 segundos
    this_thread::sleep_for(chrono::seconds(25));
    stopSimulation = true;

    // Esperar que ambos terminen
    prod.join();
    cons.join();

    system(CLEAR);
    return 0;
}
