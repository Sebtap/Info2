#include <stdio.h>
#include <stdlib.h>
/*Realizar un programa que muestre todas las variables de 
"environment" del sistema.*/

// El main puede recibir argc, argv y también envp (environment pointer)
int main(int argc, char *argv[], char *envp[]) {
    int i = 0;

    printf("--- Listado de Variables de Entorno ---\n\n");

    // Recorremos envp directamente
    while (envp[i] != NULL) {
        printf("[%d]: %s\n", i, envp[i]);
        i++;
    }

    printf("\nTotal de variables: %d\n", i);
    return 0;
}