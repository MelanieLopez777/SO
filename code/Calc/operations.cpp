#include "operations.h"

using namespace std;

void Calculadora::operar(int operador) {
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

string Calculadora::operacionToString(int operador) const {
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

int Calculadora::dameResultado() const{
    return resultado;
}

void Calculadora::pedirValores() {
    while (true) {
        try {
            cout << "Dame el valor de a= ";
            cin >> this->valorA;
            break;
        } catch (const ios_base::failure &) {
            cerr << "Error: debes ingresar un número entero válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        try {
            cout << "Dame el valor de b= ";
            cin >> this->valorB;
            break;
        } catch (const ios_base::failure &) {
            cerr << "Error: debes ingresar un número entero válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
// --- Métodos de cálculo ---

int Calculadora::sumar(int num1, int num2) { return num1 + num2; }

int Calculadora::restar(int num1, int num2) { return num1 - num2; }

int Calculadora::multiplicar(int num1, int num2) { return num1 * num2; }

int Calculadora::dividir(int num1, int num2) {
    if (num2 == 0) {
        throw invalid_argument("Error: división entre cero.");
    }
    return num1 / num2;
}

int Calculadora::residuo(int num1, int num2) { return num1 % num2; }

int Calculadora::potencia(int num1, int n) {
    int resultado = 1;
    for (int i = 0; i < n; i++) {
        resultado *= num1;
    }
    return resultado;
}