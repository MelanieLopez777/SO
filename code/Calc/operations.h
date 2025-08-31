#pragma once
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

enum Operacion { SUMA = 1, RESTA, MULTIPLICACION, DIVISION, RESIDUO, POTENCIA };

class Calculadora {
public:
    void operar();
    void pedirValores();
    string operacionToString() const;
    string mostrarMenuOperaciones() const;
    int dameResultado() const;
    void fijaOperador(int operador);
    int dameOperador() const;

private:
    int resultado;
    int valorA;
    int valorB;
    int operador;
    int sumar(int num1, int num2);
    int restar(int num1, int num2);
    int multiplicar(int num1, int num2);
    int dividir(int num1, int num2);
    int residuo(int num1, int num2);
    int potencia(int num1, int n);
};
