#include <stdio.h>
#include <stdlib.h>
//Ejercicio 6: Suma por código de retorno (Return)

int main(int argc, char *argv[]) {
    // Validamos que tengamos los dos numeros para sumar
    if (argc < 3) {
        fprintf(stderr, "Error: Faltan numeros para sumar.\n");
        return 0; // Retornamos 0 segun la consigna
    }

    // Convertimos los argumentos a enteros simples
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    int suma = n1 + n2;

    // IMPORTANTE: Aqui no hay printf. 
    // El valor de 'suma' se envia directamente a la terminal.
    return suma; 
}