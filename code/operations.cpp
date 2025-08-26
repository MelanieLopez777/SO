#include <iostream>
#include <limits>

enum {SUMA=1, RESTA, MULTIPLICACION, DIVISION, RESIDUO, POTENCIA};

using namespace std;

void resultadoSuma();
void resultadoResta();
void resultadoDivision();
void resultadoPotencia();
void resultadoResiduo();
void resultadoMultiplicacion();
int sumar(int num1, int num2);
int restar(int num1,int num2);
int multiplicar(int num1,int num2);
int dividir(int num1,int num2);
int residuo (int num1, int num2);
int potencia(int num1, int n);
void pedirValores(int &num1, int &num2);
void operar(int operador);


void operar(int operador)
{
    switch(operador){
        case SUMA:
            resultadoSuma();
            break;

        case RESTA:
            resultadoResta();
            break;

        case DIVISION:
            resultadoDivision();
            break;

        case MULTIPLICACION:
            resultadoMultiplicacion();
            break;
        
        case RESIDUO:
            resultadoResiduo();
            break;

        case POTENCIA:
            resultadoPotencia();
            break;

        default:
            cout << "No hay un resultado calculable" << endl;
            break;
    }
}

void pedirValores(int &num1, int &num2)
{
    cin.exceptions(ios::failbit | ios::badbit);

    // Pedir primer valor
    while (true) {
        try {
            cout << "Dame el valor de a= ";
            cin >> num1;
            break; 
        } catch (const ios_base::failure &e) {
            cerr << "Error: debes ingresar un número entero válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Pedir segundo valor
    while (true) {
        try {
            cout << "Dame el valor de b= ";
            cin >> num2;
            break;
        } catch (const ios_base::failure &e) {
            cerr << "Error: debes ingresar un número entero válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void resultadoSuma()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=sumar(a,b);
    cout << a << " + " << b << " = " << resultado << endl;
}

void resultadoResta()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=restar(a,b);
    cout << a << " - " << b << " = " << resultado << endl;
}

void resultadoDivision()
{
    int a, b, resultado;

    try {
        pedirValores(a, b);
        resultado = dividir(a, b);
        cout << a << " / " << b << " = " << resultado << endl;
    }
    catch (const invalid_argument &e) {
        cerr << e.what() << endl; 
    }
}


void resultadoMultiplicacion ()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=multiplicar(a,b);
    cout << a << " * " << b << " = " << resultado << endl;
}

void resultadoResiduo()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=residuo(a,b);
    cout << a << " % " << b << " = " << resultado << endl;
}

void resultadoPotencia()
{
    //Variables para entrada de datos;
    int a, n, resultado;
    cout << "Dame el valor de a= ";
    cin >> a;
    cout << "Dame el valor de n= ";
    cin >> n;
    resultado=potencia(a, n);
    cout << a << " ^ " << n << " = " << resultado << endl;
}

//Realización de operaciones;

int sumar(int num1, int num2)
{
    int resultadoSuma;
    resultadoSuma = num1 + num2;
    return resultadoSuma;
}

int restar(int num1, int num2)
{
    int resultadoResta;
    resultadoResta = num1 - num2;
    return resultadoResta;
}

int dividir(int num1, int num2)
{
    if (num2 == 0) {
        throw invalid_argument("Error: división entre cero.");
    }
    return num1 / num2;
}

int multiplicar(int num1, int num2)
{
    int resultadoMultiplicacion;
    resultadoMultiplicacion = num1*num2;
    return resultadoMultiplicacion;
}

int residuo(int num1, int num2)
{
    int resultadoResiduo;
    resultadoResiduo = num1%num2;
    return resultadoResiduo;
}

int potencia(int num1, int n)
{
    for(int i=0; i < n; i++)
    {
        num1+=num1;
    }

    return num1;
}