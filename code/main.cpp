#include <iostream>
#include <stdexcept>
#include <limits>  


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
int residuo (int num1, int num2);
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
                
                case RESIDUO:
                    resultadoResiduo();
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
    if (contadorProcesos >= TAM_PROCESOS) {
        cout << " No se pueden registrar más usuarios. Límite alcanzado." << endl;
        return;
    }

    cin.exceptions(ios::failbit | ios::badbit);

    cout << "Nombre del usuario[" << (contadorProcesos+1) << "]: ";
    cin >> usuario[contadorProcesos].nombre;

    // Pedir TME
    while (true) {
        try {
            cout << "Tiempo máximo estimado (TME) usuario[" << (contadorProcesos+1) << "]: ";
            cin >> usuario[contadorProcesos].tme;

            if (usuario[contadorProcesos].tme <= 0) {
                throw invalid_argument("El TME debe ser mayor a 0.");
            }
            break; 
        } catch (const ios_base::failure &e) {
            cerr << "Error: no ingresaste un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const invalid_argument &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    // Pedir ID
    while (true) {
        try {
            int tempID; // 🔹 variable temporal
            cout << "ID del proceso del usuario[" << (contadorProcesos+1) << "]: ";
            cin >> tempID;

            if (!validarID(tempID)) {
                throw invalid_argument("El ID ya existe, ingresa otro.");
            }

        usuario[contadorProcesos].id = tempID; // ✅ se asigna solo si es válido
        break; 
    } catch (const ios_base::failure &e) {
        cerr << "Error: no ingresaste un número válido." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } catch (const invalid_argument &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

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
            cin.clear(); // limpiar flags de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar lo malo
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
        resultado = dividir(a, b); // 🔹 puede lanzar excepción
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

