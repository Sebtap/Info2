#include <stdio.h>

// Función recursiva para Búsqueda Binaria
int busquedaBinaria(int vec[], int izquierda, int derecha, int objetivo) {
    // Caso base 1: No se encuentra el objetivo (rango inválido)
    if (izquierda > derecha) {
        return -1;
    }

    // Calcular el punto medio
    int medio = (izquierda + derecha) / 2;

    // Caso base 2: Se encuentra el objetivo
    if (vec[medio] == objetivo) {
        return medio; // Retorna el índice encontrado
    }

    // Paso recursivo 1: El objetivo es menor que el valor medio
    if (objetivo < vec[medio]) {
        return busquedaBinaria(vec, izquierda, medio - 1, objetivo);
    }

    // Paso recursivo 2: El objetivo es mayor que el valor medio
    return busquedaBinaria(vec, medio + 1, derecha, objetivo);
}

int main() {
    int vec[] = {1, 3, 5, 7, 9, 11, 13};
    int n = sizeof(vec) / sizeof(vec[0]); // n = 7
    int objetivo = 11;

    // Búsqueda inicial entre índice 0 e índice (n - 1)
    int resultado = busquedaBinaria(vec, 0, n - 1, objetivo);

    if (resultado != -1) {
        printf("El elemento %d se encuentra en el indice: %d\n", objetivo, resultado);
    } else {
        printf("El elemento %d no se encuentra en el vector.\n", objetivo);
    }

    return 0;
}