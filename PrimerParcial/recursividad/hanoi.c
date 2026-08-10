#include <stdio.h>

// Función recursiva para resolver Torres de Hanói
void hanoi(int n, char origen, char auxiliar, char destino) {
    // Caso base: Si solo queda 1 disco, se mueve directamente de Origen a Destino
    if (n == 1) {
        printf("Mover disco 1 de la torre %c a la torre %c\n", origen, destino);
        return;
    }

    // Paso 1: Mover N-1 discos de Origen a Auxiliar (usando Destino como apoyo)
    hanoi(n - 1, origen, destino, auxiliar);

    // Paso 2: Mover el disco N (el más grande) de Origen a Destino
    printf("Mover disco %d de la torre %c a la torre %c\n", n, origen, destino);

    // Paso 3: Mover los N-1 discos de Auxiliar a Destino (usando Origen como apoyo)
    hanoi(n - 1, auxiliar, origen, destino);
}

int main() {
    int discos;

    printf("Ingrese la cantidad de discos: ");
    if (scanf("%d", &discos) != 1 || discos <= 0) {
        printf("Error: Ingrese un numero entero mayor a 0.\n");
        return 1;
    }

    printf("\n--- Pasos para resolver Torres de Hanoi (%d discos) ---\n", discos);
    // 'A': Origen, 'B': Auxiliar, 'C': Destino
    hanoi(discos, 'A', 'B', 'C');

    return 0;
}