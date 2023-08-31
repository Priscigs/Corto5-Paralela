#include <iostream>
#include <fstream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time() y clock()
#include <vector>
#include <algorithm> // Para sort()
#include <omp.h>     // Para OpenMP
using namespace std;

int main() {
    srand(time(0));

    int numCount;
    cout << "Ingrese la cantidad de números aleatorios que desea generar: ";
    cin >> numCount;

    // Generar números aleatorios en paralelo y escribirlos en un archivo
    vector<int> numeros(numCount);

    #pragma omp parallel for
    for (int i = 0; i < numCount; i++) {
        numeros[i] = rand() % 1000; // Generar números entre 0 y 999
    }

    ofstream outFile("numerosParalelo.csv");

    if (!outFile) {
        cerr << "Error. No se puede abrir el archivo." << endl;
        return 1;
    }

    for (int i = 0; i < numCount; i++) {
        outFile << numeros[i];

        // Separar con comas el archivo generado
        if (i < numCount - 1) {
            outFile << ",";
        }
    }

    outFile.close();

    // Medir el tiempo antes de comenzar a ordenar
    double startTime = omp_get_wtime();

    // Clasificar los números en paralelo usando sort() de la STL
    #pragma omp parallel
    {
        #pragma omp single
        sort(numeros.begin(), numeros.end());
    }

    // Medir el tiempo después de ordenar
    double endTime = omp_get_wtime();
    double totalTime = endTime - startTime;

    cout << "Tiempo transcurrido para ordenar: " << totalTime << " segundos." << endl;

    // Almacenar los números clasificados en un segundo archivo
    ofstream sortedFile("numeros_clasificados_paralelo.csv");

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

    return 0;
}
