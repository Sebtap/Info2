#include <stdio.h>

// Función recursiva para imprimir un número en binario
void binario(int n) {
    // Caso base: se detiene cuando n llega a 0
    if (n == 0) {
        return;
    }

    // Paso recursivo: primero divide y apila las llamadas
    binario(n / 2);

    // Al regresar (desapilar), imprime el resto de la división
    printf("%d", n % 2);
}

int main() {
    int num;

    printf("Ingrese un numero decimal: ");
    if (scanf("%d", &num) != 1 || num < 0) {
        printf("Error: Ingrese un numero entero mayor o igual a 0.\n");
        return 1;
    }

    printf("El numero %d en binario es: ", num);

    // Manejo especial para el número 0
    if (num == 0) {
        printf("0");
    } else {
        binario(num);
    }

    printf("\n");
    return 0;
}