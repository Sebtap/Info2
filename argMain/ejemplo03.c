#include <stdio.h>
#include <stdlib.h>
/*Realizar un programa que muestre todas las variables de 
"environment" del sistema.*/

// El main puede recibir argc, argv y también envp (environment pointer)
//envp es un array de strings que contiene las variables de entorno, cada string tiene el formato "NOMBRE=VALOR". El último elemento de envp es NULL para indicar el final del array.
//envp puede que no este soportado en todos los sistemas o compiladores, pero es común en sistemas tipo Unix/Linux. En otros sistemas, las variables de entorno se pueden acceder a través de funciones específicas como getenv().

/*Las variables de entorno son pares de nombre y valor que están disponibles para los programas en ejecución. Se utilizan para almacenar información sobre el entorno del sistema, como la ruta del directorio actual, el idioma, etc. 
Configuracion ya existente en el sistema que mantiene el so o la shell y que se herendan por los procesos hijos
procesos hijos son los programas que se crean a partir de otro programa, y heredan las variables de entorno del programa padre.*/

//Las variables de entorno se acceden a traves de funciones expecificas como getenv() o a traves del tercer argumento del main (envp) que es un array de strings con el formato "NOMBRE=VALOR". El último elemento de envp es NULL para indicar el final del array. En este programa, se recorre envp directamente para mostrar todas las variables de entorno disponibles.

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