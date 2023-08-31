#include <iostream>
#include <fstream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time() y clock()
using namespace std;

// Usando parte del algoritmo que se proporcionó en el archivo qsort.c
void par_qsort(int *data, int lo, int hi) {
    if (lo >= hi) return;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2];

    while (l <= h) {
        while (data[l] < p) l++;
        while (data[h] > p) h--;
        if (l <= h) {
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++;
            h--;
        }
    }

    par_qsort(data, lo, h);
    par_qsort(data, l, hi);
}

int main() {
    srand(time(0));

    int numCount;
    cout << "Ingrese la cantidad de números aleatorios que desea generar: ";
    cin >> numCount;

    // Generar números aleatorios y escribirlos en un archivo
    ofstream outFile("numerosSecuencial.csv");

    if (!outFile) {
        cerr << "Error. No se puede abrir el archivo." << endl;
        return 1;
    }

    for (int i = 0; i < numCount; i++) {
        int randomNumber = rand() % 1000; // Generar números entre 0 y 999
        outFile << randomNumber;

        // Separar con comas el archivo generado
        if (i < numCount - 1) {
            outFile << ",";
        }
    }

    outFile.close();

    // Medir el tiempo antes de comenzar a ordenar
    clock_t startTime = clock();

    // Se almacenan en memoria local los números
    ifstream inFile("numerosSecuencial.csv");

    if (!inFile) {
        cerr << "Error. No se puede abrir el archivo." << endl;
        return 1;
    }

    int *numeros = new int[numCount];

    for (int i = 0; i < numCount; i++) {
        char comma;
        inFile >> numeros[i];

        // Leer la coma
        if (i < numCount - 1) {
            inFile >> comma;
        }
    }

    inFile.close();

    // Clasificar los números usando QuickSort proporcionado en el archivo qsort.c
    par_qsort(numeros, 0, numCount - 1);

    // Medir el tiempo después de ordenar
    clock_t endTime = clock();
    double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Tiempo transcurrido para ordenar: " << totalTime << " segundos." << endl;

    // Almacenar los números clasificados en un segundo archivo
    ofstream sortedFile("numeros_clasificados_secuencial.csv");

    if (!sortedFile) {
        cerr << "Error. No se puede abrir el archivo." << endl;
        return 1;
    }

    for (int i = 0; i < numCount; i++) {
        sortedFile << numeros[i];

        // Separar con comas, excepto el último número
        if (i < numCount - 1) {
            sortedFile << ",";
        }
    }

    sortedFile.close();

    // Liberar la memoria del Heap
    delete[] numeros;

    return 0;
}
