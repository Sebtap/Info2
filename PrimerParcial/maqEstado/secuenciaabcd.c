/*
Realizar un programa que detecte la secuencia de caracteres "abcd" ingresadas
por teclado. Utilizar maquinas de estado
*/

#include <stdio.h>
#include <ctype.h>

typedef enum {
    ESTADO_INICIO,
    ESTADO_A,
    ESTADO_AB,
    ESTADO_ABC
} ESTADO;

int main() {
    ESTADO estado = ESTADO_INICIO;
    char entrada;

    printf("Ingresá caracteres uno a uno (o 'q' para salir):\n");

    while (1) {
        printf("Caracter: ");
        if (scanf(" %c", &entrada) != 1) break;
        
        entrada = tolower(entrada);

        // Condicion de salida manual por teclado
        if (entrada == 'q') {
            printf("Programa finalizado por el usuario.\n");
            break;
        }

        switch (estado) {
            case ESTADO_INICIO:
                if (entrada == 'a') estado = ESTADO_A;
                break;

            case ESTADO_A:
                if (entrada == 'b') estado = ESTADO_AB;
                else if (entrada == 'a') estado = ESTADO_A;
                else estado = ESTADO_INICIO;
                break;

            case ESTADO_AB:
                if (entrada == 'c') estado = ESTADO_ABC;
                else if (entrada == 'a') estado = ESTADO_A;
                else estado = ESTADO_INICIO;
                break;

            case ESTADO_ABC:
                if (entrada == 'd') {
                    printf("\n>>> ¡Secuencia 'abcd' detectada con exito! <<<\n");
                    return 0; // Termina el programa inmediatamente al encontrarla
                } else if (entrada == 'a') {
                    estado = ESTADO_A;
                } else {
                    estado = ESTADO_INICIO;
                }
                break;
        }
    }

    return 0;
}