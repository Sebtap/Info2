/*
Realizar un programa que detecte la secuencia de caracteres "abcd" ingresadas 
por teclado. Contar cuantas veces aparecio abcd en la entrada. A la tercera 
vez que se detecta imprimir en pantala "ALARMA ACTIVADA" y volver a contar 
desde cero
*/

#include <stdio.h>
#include <ctype.h>

typedef enum {
    S_INIT,
    S_A,
    S_AB,
    S_ABC
} ESTADO;

int main() {
    ESTADO estado = S_INIT;
    char entrada;
    int contador = 0;

    printf("Ingrese caracteres uno a uno ('q' para salir):\n");

    while (1) {
        printf("Caracter: ");
        if (scanf(" %c", &entrada) != 1) break;

        entrada = tolower(entrada);

        if (entrada == 'q') {
            printf("Programa finalizado por el usuario.\n");
            break;
        }

        switch (estado) {
            case S_INIT:
                if (entrada == 'a') estado = S_A;
                break;

            case S_A:
                if (entrada == 'b') estado = S_AB;
                else if (entrada == 'a') estado = S_A;
                else estado = S_INIT;
                break;

            case S_AB:
                if (entrada == 'c') estado = S_ABC;
                else if (entrada == 'a') estado = S_A;
                else estado = S_INIT;
                break;

            case S_ABC:
                if (entrada == 'd') {
                    contador++;
                    printf("-> Secuencia 'abcd' detectada (Ocurrencia: %d/3)\n", contador);

                    if (contador == 3) {
                        printf("\n*************************\n");
                        printf("*   ALARMA ACTIVADA    *\n");
                        printf("*************************\n\n");
                        contador = 0; // Reiniciar el contador de apariciones
                    }

                    estado = S_INIT;
                } else if (entrada == 'a') {
                    estado = S_A;
                } else {
                    estado = S_INIT;
                }
                break;
        }
    }

    return 0;
}