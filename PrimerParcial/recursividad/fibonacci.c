#include <stdio.h>

// Función recursiva para calcular el n-ésimo término
long long fibonacci(int n) {
    // Caso base 1: F(0) = 0
    if (n == 0) {
        return 0;
    }
    // Caso base 2: F(1) = 1
    if (n == 1) {
        return 1;
    }
    // Paso recursivo: Suma de las dos llamadas anteriores apiladas en la memoria
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    int n;

    printf("Ingrese la posicion (n) a calcular: ");
    
    // Validar que la entrada sea un entero válido no negativo
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Error: Debe ingresar un numero entero mayor o igual a 0.\n");
        return 1;
    }

    // Impresión del término solicitado
    printf("El termino F(%d) es: %lld\n\n", n, fibonacci(n));

    // Bucle para mostrar la secuencia completa desde F(0) hasta F(n)
    printf("Secuencia de Fibonacci hasta F(%d):\n", n);
    for (int i = 0; i <= n; i++) {
        printf("%lld ", fibonacci(i));
    }
    printf("\n");

    return 0;
}