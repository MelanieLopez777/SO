#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(_unix) || defined(APPLE) || defined(MACH_)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace std;

#define TAM_PROCESOS 4
enum {SUMA=1, RESTA, MULTIPLICACION, DIVISION, RESIDUO, POTENCIA, SALIR};

typedef struct {

    string nombre;
    int id;
    int tme;
    int resultado;
    int operacion;

} proceso;

proceso usuario[TAM_PROCESOS];
int contadorProcesos;

void mostrarMenu();
void pedirDatos();
void pedirValores(int &num1, int &num2);
void pedirOperador();
void pedirValorN();
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
int modulo (int num1, int num2);
int potencia(int num1, int n);
bool validarID(int &id);

int main(){

    //Variables para entrada de datos;
    int opcionValida, operador;

    opcionValida=1;
    do{
        pedirDatos();
        mostrarMenu();
        opcionValida=1;
        cin >> operador;

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
                case POTENCIA:
                    resultadoPotencia();
                    break;

                case SALIR: //Salida del programa.
                    opcionValida=0;
                    break;

                default:
                    cout << "No hay un resultado calculable" << endl;
                    opcionValida=0;
                    break;
            }
        
        if (opcionValida==1)
        {
            cout << "Presionar entrar para continuar...";
            cin.ignore();
            cin.get();
            system(CLEAR);
        }
        else
        {
            system(CLEAR);
        }
    } while(opcionValida==1);

    return 0;
}


void pedirDatos()
{
    cout << "Nombre del usuario[" <<(contadorProcesos+1)<< "]: " ;
    cin >> usuario[contadorProcesos].nombre;
    do{
        usuario[contadorProcesos].tme=5;
        cout << "Tiempo máximo estimado (TME) usuario[" <<(contadorProcesos+1)<< "]: ";
        cin >> usuario[contadorProcesos].tme;
    }while(usuario[contadorProcesos].tme <= 0);

    do{
        cout << "ID del proceso del usuario["<<(contadorProcesos+1)<<"]: ";
        cin >> usuario[contadorProcesos].id;
    }while(validarID(usuario[contadorProcesos].id)==false);
    cout << endl;
    contadorProcesos++;
}

bool validarID(int &id)
{
    for (int i = 0; i < contadorProcesos; i++)
    {
        if (id == usuario[i].id)
        {
            cout << "Número de identificación repetido" << endl;
            return false;
        }
        else
        {
            return true;
        }
    }
    return true;
}

void mostrarMenu()
{
    //Menú principal;
    cout << "CALCULADORA v1.0" << endl << endl;
    cout << "Elige una de las siguientes opciones:" << endl;
    cout << "1. Operación: Suma"<< endl;
    cout << "2. Operación: Resta"<< endl;
    cout << "3. Operación: Multiplicación"<< endl;
    cout << "4. Operación: División"<< endl;
    cout << "5. Operación: Residuo"<< endl;
    cout << "6. Operación: Potencia"<< endl;
    cout << "7. Salir" << endl;
    cout << "Ingresa el número de la operación a realizar:  ";

}

void pedirValores (int &num1, int &num2)
{
    cout << "Dame el valor de a= ";
    cin >> num1;
    cout << "Dame el valor de b= ";
    cin >> num2;
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
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    if (b==0){
        resultado=0;
    }
    else{
        resultado=dividir(a,b);
    }
    cout << a << " / " << b << " = " << resultado << endl;
}

void resultadoMultiplicacion ()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=multiplicar(a,b);
    cout << a << " * " << b << " = " << resultado << endl;
}

void resultadoModulo()
{
    //Variables para entrada de datos;
    int a, b, resultado;
    pedirValores(a,b);
    resultado=modulo(a,b);
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
    int resultadoDivision;
    resultadoDivision = num1/num2;
    return resultadoDivision;
}

int multiplicar(int num1, int num2)
{
    int resultadoMultiplicacion;
    resultadoMultiplicacion = num1*num2;
    return resultadoMultiplicacion;
}

int modulo(int num1, int num2)
{
    int resultadoModulo;
    resultadoModulo = num1%num2;
    return resultadoModulo;
}

int potencia(int num1, int n)
{
    for(int i=0; i < n; i++)
    {
        num1*=num1;
    }

    return num1;
}

