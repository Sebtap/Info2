//2. Implementar una función recursiva para la búsqueda 
//de un elemento (**Búsqueda Binaria**).


int main() {
    // Supongamos que tenemos este vector de temperaturas desordenado
    float temperaturas[] = {80.5, 12.0, 75.0, 23.5, 45.2, 15.3};
    int n = 6;
    float buscar = 75.0; // Queremos buscar si existe la temperatura 75.0°C

    printf("--- PASO 1: ORDENAMIENTO (QuickSort) ---\n");
    quickSort(temperaturas, 0, n - 1);

    printf("Vector ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%.1f ", temperaturas[i]);
    }
    printf("\n\n");

    printf("--- PASO 2: BÚSQUEDA BINARIA ---\n");
    int resultado = busquedaBinaria(temperaturas, 0, n - 1, buscar);

    if (resultado != -1) {
        printf("¡Encontrado! La temperatura %.1f *C esta en el indice %d del arreglo.\n", buscar, resultado);
    } else {
        printf("La temperatura %.1f *C no se encuentra registrada.\n", buscar);
    }

    return 0;
}

#include <stdio.h>

int busquedaBinaria(float arr[], int bajo, int alto, float objetivo) {
    // 1. CASO BASE 1: No se encontró el número
    if (bajo > alto) {
        return -1; // -1 indica que el valor no existe en el arreglo
    }

    // 2. Calculamos el índice medio
    int medio = bajo + (alto - bajo) / 2;

    // 3. CASO BASE 2: Encontramos el número
    if (arr[medio] == objetivo) {
        return medio; // Retornamos la posición donde está el elemento
    }

    // 4. CASO RECURSIVO: Buscar en la mitad izquierda
    if (arr[medio] > objetivo) {
        return busquedaBinaria(arr, bajo, medio - 1, objetivo);
    }

    // 5. CASO RECURSIVO: Buscar en la mitad derecha
    return busquedaBinaria(arr, medio + 1, alto, objetivo);
}

void quickSort(float temperaturas[], int bajo, int alto) {
    // CASO BASE: Si el sub-arreglo tiene 1 o 0 elementos (bajo >= alto), no hace nada.
    if (bajo < alto) {
        
        // 1. Acomodamos el pivote y guardamos su posición final
        int pos_pivote = particion(temperaturas, bajo, alto);

        // 2. CASO RECURSIVO: Acomodamos la mitad izquierda y la mitad derecha
        quickSort(temperaturas, bajo, pos_pivote - 1); // Lado izquierdo (menores)
        quickSort(temperaturas, pos_pivote + 1, alto); // Lado derecho (mayores)
    }
}