/*
Ejercicio: La Cuenta Regresiva
Enunciado:

Escribir un programa en C con una función recursiva llamada 
cuenta_regresiva(int n) que reciba un número entero n e imprima los 
números desde n hasta 1, y al llegar a 0 imprima "¡Despegue!".
*/

/*
Una funcion recursiva es una función que se llama a sí misma para resolver un problema.
Para que la recursión funcione correctamente, es importante definir un caso base que detenga la recursión y un caso recursivo que reduzca el problema en cada llamada.
En este caso, el caso base es cuando n es igual a 0, momento en el cual se imprime "¡Despegue!" y la función deja de llamarse a sí misma. El caso recursivo es cuando n es mayor que 0, en cuyo caso se imprime el valor actual de n y luego se llama a la función con n-1.
*/

#include <stdio.h>

// Función recursiva para la cuenta regresiva
void cuenta_regresiva(int n) {
    // Caso base: Si n es 0, imprimimos "¡Despegue!" y terminamos la recursión
    if (n == 0) {
        printf("¡Despegue!\n");
        return;
    }

    // Caso recursivo: Imprimimos el número actual y llamamos a la función con n-1
    printf("%d\n", n);
    cuenta_regresiva(n - 1);


}


int main(){
    int numero;

    printf("=== CUENTA REGRESIVA ===\n");
    printf("Ingrese un numero entero positivo para iniciar la cuenta regresiva: ");
    
    // Validación de entrada de datos
    if (scanf("%d", &numero) != 1 || numero < 0) {
        printf("[ERROR] Debe ingresar un numero entero positivo.\n");
        return 1;
    }

    // Llamada a la función recursiva
    cuenta_regresiva(numero);

    return 0;
}