#include "operations.h"

using namespace std;

void Calculadora::operar() {
    switch (operador) {
        case SUMA: this->resultado = sumar(this->valorA, this->valorB); break;
        case RESTA: this->resultado = restar(this->valorA, this->valorB); break;
        case DIVISION: this->resultado = dividir(this->valorA, this->valorB); break;
        case MULTIPLICACION: this->resultado = multiplicar(this->valorA, this->valorB); break;
        case RESIDUO: this->resultado = residuo(this->valorA, this->valorB); break;
        case POTENCIA: this->resultado = potencia(this->valorA, this->valorB); break;
        default:
            cout << "No hay un resultado calculable" << endl;
            break;
    }
}

string Calculadora::operacionToString() const {
    ostringstream oss;
    switch (operador) {
        case SUMA: oss << this->valorA << " + " << this->valorB; break;
        case RESTA: oss << this->valorA << " - " << this->valorB; break;
        case DIVISION: oss << this->valorA << " / " << this->valorB; break;
        case MULTIPLICACION: oss << this->valorA << " * " << this->valorB; break;
        case RESIDUO: oss << this->valorA << " % " << this->valorB; break;
        case POTENCIA: oss << this->valorA << " ^ " << this->valorB; break;
        default:
            oss << "No existe la operación, error" << endl;
            break;
    }
    return oss.str();
}

string Calculadora::mostrarMenuOperaciones() const {
    ostringstream oss;
    oss << "Elige una de las siguientes opciones:" << endl << 
            "1. Operación: Suma" << endl << 
            "2. Operación: Resta" << endl << 
            "3. Operación: Multiplicación" << endl << 
            "4. Operación: División" << endl << 
            "5. Operación: Residuo" << endl << 
            "6. Operación: Potencia" << endl << 
            "Ingresa el número de la operación a realizar:  ";
    return oss.str();
}

float Calculadora::dameResultado() const{
    return resultado;
}

void Calculadora::fijaOperador(int operador)
{
    this->operador = operador;
}

void Calculadora::fijaValorA(float valorA)
{
    this->valorA = valorA;
}

void Calculadora::fijaValorB(float valorB)
{
    this->valorB = valorB;
}

int Calculadora::dameOperador() const
{
    return this->operador;
}

float Calculadora::dameValorA() const
{
    return this->valorA;
}

float Calculadora::dameValorB () const
{
    return this->valorB;
}
// --- Métodos de cálculo ---

float Calculadora::sumar(float num1, float num2) { return num1 + num2; }

float Calculadora::restar(float num1, float num2) { return num1 - num2; }

float Calculadora::multiplicar(float num1, float num2) { return num1 * num2; }

float Calculadora::dividir(float num1, float num2) 
{
    return num1 / num2;
}

float Calculadora::residuo(float num1, float num2) 
{ 
    float r = fmod(num1, num2);
    return (r < 0) ? r + fabs(num2) : r;
}

float Calculadora::potencia(float num1, float n) {
    return pow(num1, n);
}