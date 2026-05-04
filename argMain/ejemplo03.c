#include <stdio.h>
#include <stdlib.h>
/*Realizar un programa que muestre todas las variables de 
"environment" del sistema.*/

// El main puede recibir argc, argv y también envp (environment pointer)
//envp es un array de strings que contiene las variables de entorno, cada string tiene el formato "NOMBRE=VALOR". El último elemento de envp es NULL para indicar el final del array.
//envp puede que no este soportado en todos los sistemas o compiladores, pero es común en sistemas tipo Unix/Linux. En otros sistemas, las variables de entorno se pueden acceder a través de funciones específicas como getenv().
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