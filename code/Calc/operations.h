#pragma once
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

enum Operacion { SUMA = 1, RESTA, MULTIPLICACION, DIVISION, RESIDUO, POTENCIA };

class Calculadora {
public:
    void operar();
    string operacionToString() const;
    string mostrarMenuOperaciones() const;
    float dameResultado() const;
    void fijaResultado(float resultado);
    void fijaOperador(int operador);
    void fijaValorA(float valorA);
    void fijaValorB(float valorB);
    int dameOperador() const;
    float dameValorA() const;
    float dameValorB() const;

private:
    float resultado;
    float valorA;
    float valorB;
    int operador;
    float sumar(float num1, float num2);
    float restar(float num1, float num2);
    float multiplicar(float num1, float num2);
    float dividir(float num1, float num2);
    float residuo(float num1, float num2);
    float potencia(float num1, float n);
};
