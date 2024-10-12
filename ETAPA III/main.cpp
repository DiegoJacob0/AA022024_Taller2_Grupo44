#include <iostream>
#include <fstream>
#include <iomanip> //libreria permite insertar el simbolo de dolar

using namespace std;

// Algoritmo utilizado max-heap
void heapify(double arr[], int n, int i) {
    int mayor = i; 
    int izq = 2 * i + 1; 
    int der = 2 * i + 2; 

    if (izq < n && arr[izq] > arr[mayor])
        mayor = izq;

    if (der < n && arr[der] > arr[mayor])
        mayor = der;

    if (mayor != i) {
        swap(arr[i], arr[mayor]); 

        // Recursivamente hacer heapify en el subárbol afectado
        heapify(arr, n, mayor);
    }
}

// HeapSort en orden ascendente
void heapSort(double arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer uno por uno los elementos del heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  
        heapify(arr, i, 0);    
    }

    // Orden descendente
    for (int i = 0; i < n / 2; i++) {
        swap(arr[i], arr[n - i - 1]);
    }
}

//Mostrar el simbolo de dolar
void printArray(double arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ". $" << fixed << setprecision(2) << arr[i] << "\n"; 
    }
}

//Obtiene la informacion del archivo donde se encuentran los datos
double* leerSalariosDesdeArchivo(const string& nombreArchivo, int& n) {
    ifstream archivo(nombreArchivo);  // Abrir archivo
    string linea;
    n = 0;  

    // Enumera cada salario existente, lee linea por linea
    while (getline(archivo, linea)) {
        n++;
    }

    archivo.clear();  
    archivo.seekg(0);

    // Arreglo nuevo para guardar los nuevos salarios ingresados
    double* salarios = new double[n];

int index=0;
double salario;
while (archivo >> salario) { //Lee directamente el archivo de salarios
    salarios [index++] = salario;
}

    //Cierra el archivo
    archivo.close();  
    return salarios;
}

// Funcion agregar nuevo salario
double* agregarSalario(double* arr, int& n, double nuevoSalario) {
    double* nuevoArr = new double[n + 1];  //nuevo arreglo donde se guardará el nuevo slario
    for (int i = 0; i < n; i++) {
        nuevoArr[i] = arr[i];  //se colocan los salarios ya obtenidos
    }
    nuevoArr[n] = nuevoSalario;  // Agrega como tal el nuevo salario
    n++;  
    delete[] arr;  
    return nuevoArr;
}

// Función para eliminar un salario
double* eliminarSalario(double* arr, int& n, int index) {
    if (index < 0 || index >= n) {
        cout << "Índice inválido.\n";
        return arr;
    }

    double* nuevoArr = new double[n - 1];  // Crear un nuevo arreglo con tamaño reducido
    for (int i = 0, j = 0; i < n; i++) {
        if (i != index) {
            nuevoArr[j++] = arr[i];  // Copiar los elementos, omitiendo el que se va a eliminar
        }
    }
    n--;  
    delete[] arr;  // Liberar la memoria del arreglo antiguo
    return nuevoArr;
}


// Funcion para buscar un salario
void buscarSalario(double*arr, int n, int index){
    if (index < 0 || index >= n) {
        cout << "Índice inválido.\n";
    } else{
         cout << "El salario " << (index + 1) << " es: $" << fixed << setprecision(2) << arr[index] << ".\n";
    }
}


int main() {
    int n = 0;
    double* salarios = nullptr;  

    // Llama al archivo donde se encuentran los salarios
    salarios = leerSalariosDesdeArchivo("salarios.txt", n);
    
    // Ordenar los salarios de forma descendente
    heapSort(salarios, n);

    int opcion;
    do {
        cout << "\n** Registro de Salarios **\n";
        cout << "1. Agregar un salario\n";
        cout << "2. Eliminar un salario\n";
        cout << "3. Buscar un salario\n";
        cout << "4. Ver salarios\n";
        cout << "5. Salir\n";
        cout << "Elija una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double nuevoSalario;
                cout << "Ingrese el nuevo salario: ";
                cin >> nuevoSalario;
                salarios = agregarSalario(salarios, n, nuevoSalario);
                heapSort(salarios, n);  // Ordena el salario agregado al archivo
                cout << "Salario agregado.\n";
                break;
            }
            case 2: {
                int indice;
                cout << "Ingrese el índice del salario a eliminar (1 a " << n << "): ";
                cin >> indice;
                salarios = eliminarSalario(salarios, n, indice - 1);
                heapSort(salarios, n);  // Ordenar después de eliminar el salario
                cout << "Salario eliminado. \n";
                break;
            }
            case 3: {  
                int indice;
                cout << "Ingrese el índice del salario a buscar (1 a " << n << "): ";
                cin >> indice;
                buscarSalario(salarios, n, indice- 1);  
                break;
            }
            case 4: {
                if (n > 0) {
                    cout << "** Salarios de los empleados ** \n";
                    printArray(salarios, n);
                } else {
                    cout << "No hay salarios para mostrar.\n";
                }
                break;
            }
            case 5: {
                cout << "Cerrar\n";
                break;
            }
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 5);

    // Libera la memoria
    delete[] salarios;

    return 0;
}
