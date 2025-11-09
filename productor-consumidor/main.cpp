#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Constants/constants.h"

using namespace std;

vector<char> buffer(BUFFER_SIZE, '_');

int in = 0;
int out = 0;
int countBuffer = 0;

mutex mtx;
condition_variable not_full;
condition_variable not_empty;

bool stopSimulation = false;

string estadoProductor = "Inactivo";
string estadoConsumidor = "Inactivo";

void mostrarPantalla() {
    system(CLEAR);
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

    cout << "Productor: " << estadoProductor << endl;
    cout << "Consumidor: " << estadoConsumidor << endl;
    cout << "Elementos actuales en el buffer: " << countBuffer << "/" << BUFFER_SIZE << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Presiona ESC para detener la simulación..." << endl;
}

void productor() {
    while (!stopSimulation) {
        int sleepTime = 500 + rand() % 1000;
        estadoProductor = "Durmiendo (" + to_string(sleepTime) + " ms)";

        this_thread::sleep_for(chrono::milliseconds(sleepTime));
        unique_lock<mutex> lock(mtx);
        estadoProductor = "Intentando entrar al contenedor...";
        not_full.wait(lock, [] { return countBuffer < BUFFER_SIZE || stopSimulation; });
        if (stopSimulation) {
            estadoProductor = "Terminado (ESC)";
            mostrarPantalla();
            return;
        }

        int itemsToProduce = 3 + rand() % 4;
        estadoProductor = "Produciendo " + to_string(itemsToProduce) + " elementos...";

        for (int i = 0; i < itemsToProduce && countBuffer < BUFFER_SIZE && !stopSimulation; i++) {
            char item = 'A' + rand() % 26;
            buffer[in] = item;
            in = (in + 1) % BUFFER_SIZE;
            countBuffer++;

            mostrarPantalla();
            this_thread::sleep_for(chrono::milliseconds(400));
        }

        estadoProductor = "Terminó de producir (" + to_string(itemsToProduce) + ")";
        mostrarPantalla();

        lock.unlock();
        not_empty.notify_one();
    }
    estadoProductor = "Terminado (ESC)";
    mostrarPantalla();
}

void consumidor() {
    while (!stopSimulation) {
        int sleepTime = 700 + rand() % 1100;
        estadoConsumidor = "Durmiendo (" + to_string(sleepTime) + " ms)";

        this_thread::sleep_for(chrono::milliseconds(sleepTime));
        unique_lock<mutex> lock(mtx);
        estadoConsumidor = "Intentando entrar al contenedor";
        not_empty.wait(lock, [] { return countBuffer > 0 || stopSimulation; });

        if (stopSimulation) {
            estadoConsumidor = "Terminado (ESC)";
            mostrarPantalla();
            return;
        }

        int itemsToConsume = 3 + rand() % 4;
        estadoConsumidor = "Consumiendo " + to_string(itemsToConsume) + " elementos";
        for (int i = 0; i < itemsToConsume && countBuffer > 0 && !stopSimulation; i++) {
            buffer[out] = '_';
            out = (out + 1) % BUFFER_SIZE;
            countBuffer--;
            mostrarPantalla();
            this_thread::sleep_for(chrono::milliseconds(400));
        }
        estadoConsumidor = "Terminó de consumir (" + to_string(itemsToConsume) + ")";
        mostrarPantalla();
        lock.unlock();
        not_full.notify_one();
    }
    estadoConsumidor = "Terminado (ESC)";
    mostrarPantalla();
}


int main() {
    srand(time(nullptr));
    thread prod(productor);
    thread cons(consumidor);
    while (!stopSimulation) {
        this_thread::sleep_for(chrono::milliseconds(100));

        if (_kbhit()) {
            int key = _getch();

            if (key == 27) {
                stopSimulation = true;
                not_full.notify_all();
                not_empty.notify_all();
            }
        }
    }
    prod.join();
    cons.join();
    system(CLEAR);
    cout << "\nSimulación detenida por el usuario (ESC)." << endl;
    return 0;
}