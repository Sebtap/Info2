#include <stdio.h>
#include <stdlib.h>
//Ejercicio 6: Suma por código de retorno (Return)

int main(int argc, char *argv[]) {
    // Validamos que tengamos los dos numeros para sumar
    if (argc < 3) {
        fprintf(stderr, "Error: Faltan numeros para sumar.\n");
        return 0; // Retornamos 0 segun la consigna
    }

    // Convertimos los argumentos a enteros simples, a diferencia de strtol, atoi no tiene validacion de errores, si el argumento no es un numero, retorna 0.
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    int suma = n1 + n2;

    //Atof convierte un string a un numero de punto flotante, si el argumento no es un numero, retorna 0.0
    // float n1 = atof(argv[1]); // Si el argumento no es un numero, retorna 0.0
    //float n2 = atof(argv[2]);
    //float suma_float = n1 + n2;
    //printf("Suma: %.2f\n", suma_float);

    // IMPORTANTE: Aqui no hay printf. 
    // El valor de 'suma' se envia directamente a la terminal.
    return suma;  //%errorlevel% aca queda guardado el valor de 'suma' para ser usado en el shell o terminal despues de ejecutar el programa.
}