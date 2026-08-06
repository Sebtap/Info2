/*
Enunciado:Escribir un programa con una función recursiva llamada 
sumar(int n) que reciba un entero positive N y calcule la suma de todos 
los enteros desde 1 hasta N.
Ejemplo: Si N = 4, la respuesta debe ser 4 + 3 + 2 + 1 = 10.
*/

/*
Caso base y caso recursivo:
- Caso base: Si n es igual a 1, la suma es 1.
- Caso recursivo: Para cualquier n > 1, la suma es n + sumar(n - 1).
*/

#include <stdio.h>

// Función recursiva para calcular la suma de enteros desde 1 hasta n
int sumar(int n) {
    // Caso base: Si n es 1, la suma es 1
    if (n == 1) {
        return 1;
    }

    // Caso recursivo: La suma es n más la suma de los números anteriores
    return n + sumar(n - 1);
}

int main() {
    int numero;

    printf("=== CALCULADORA DE SUMA RECURSIVA ===\n");
    printf("Ingrese un numero entero positivo: ");

    // Validación de entrada de datos
    if (scanf("%d", &numero) != 1 || numero < 1) {
        printf("[ERROR] Debe ingresar un numero entero positivo.\n");
        return 1;
    }

    // Llamada a la función recursiva
    int resultado = sumar(numero);

    printf("La suma de los enteros desde 1 hasta %d es: %d\n", numero, resultado);

    return 0;
}