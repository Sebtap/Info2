#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necesaria para strcmp (comparar texto)

/*Realizar un programa que funcione como una calculadora 
por argumentos del main. Asi: calc operacion numero1 
numero2 ...  */

int main(int argc, char *argv[]) {
    // Verificamos que el usuario pase: programa + operacion + num1 + num2 (total 4)
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <operacion> <num1> <num2>\n", argv[0]);
        return 1;
    }

    // Guardamos la operacion en un puntero a char para mayor claridad
    char *op = argv[1];

    // Convertimos los strings de los argumentos a numeros long
    long n1 = strtol(argv[2], NULL, 10);
    long n2 = strtol(argv[3], NULL, 10);
    long resultado = 0;

    // Comparamos el string 'op' con las operaciones permitidas
    if (strcmp(op, "suma") == 0) {
        resultado = n1 + n2;
    } else if (strcmp(op, "resta") == 0) {
        resultado = n1 - n2;
    } else if (strcmp(op, "mult") == 0) {
        resultado = n1 * n2;
    } else {
        // Si no coincide con ninguna, mandamos error por stderr
        fprintf(stderr, "Error: Operacion '%s' no reconocida.\n", op);
        return 1;
    }

    // Si todo salio bien, imprimimos el resultado por stdout
    fprintf(stdout, "Resultado: %ld\n", resultado);
    return 0;
}