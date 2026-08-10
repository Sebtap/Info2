#include <stdio.h>

// Se especifica (int n) de forma explícita
long factorial(int n) {
    // Caso base: evita la recursión infinita si 'n' es 0, 1 o negativo
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int num;
    printf("Ingrese un numero para calcular el factorial: ");
    scanf("%d", &num);

    // Validar que el número no sea negativo
    if (num < 0) {
        printf("Error: No existe el factorial de un numero negativo.\n");
        return 1;
    }

    long resultado = factorial(num);
    printf("El resultado factorial del numero es %ld\n", resultado);

    return 0;
}