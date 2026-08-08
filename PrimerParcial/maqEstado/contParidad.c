/*
Realizar un programa que permita ingresar por teclado cualquier secuencia de 
0 y 1. En pantalla se debe mostrar si la cantidad de 1 ingresados es PAR o
IMPAR. Utilizar maquinas de estado finito.
*/

#include <stdio.h>

typedef enum {
    PAR,
    IMPAR
} ESTADO;

int main() {
    ESTADO estado = PAR; // Estado inicial: 0 unos es PAR
    char secuencia[101]; // Capacidad para 100 caracteres + '\0'

    printf("Ingrese una secuencia de 0 y 1: ");
    if (scanf("%100s", secuencia) != 1) {
        fprintf(stderr, "Error al leer la entrada.\n");
        return 1;
    }

    int i = 0;
    // Recorremos la cadena hasta el final ('\0')
    while (secuencia[i] != '\0') {
        
        switch (estado) {
            case PAR:
                if (secuencia[i] == '1') {
                    estado = IMPAR;
                }
                break;

            case IMPAR:
                if (secuencia[i] == '1') {
                    estado = PAR;
                }
                break;
        }

        i++; // Pasamos al siguiente caracter
    }

    // Salida final segun el estado
    if (estado == PAR) {
        printf("La cantidad de unos es PAR.\n");
    } else {
        printf("La cantidad de unos es IMPAR.\n");
    }

    return 0;
}