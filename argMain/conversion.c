#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Un único puntero en una dirección fija de la RAM (ej: 0x2222)
    char *fin; 

    // Empezamos en 1 para saltear el nombre del programa (argv[0])
    for (int i = 1; i < argc; i++) {
        
        // En cada vuelta, strtol borra lo anterior y escribe el nuevo freno en 0x2222
        long valor = strtol(argv[i], &fin, 10); //argv[i]: dirección del string que queremos convertir. fin: dirección del freno. 10: base decimal (podría ser 16 para hexadecimal, o 2 para binario).

        if (*fin != '\0') {
            printf("Arg %d ('%s') NO es un entero limpio. Fallo en: '%s'\n", i, argv[i], fin); //para ver el contenido del puntero fin, el programa lo imprime como una cadena de caracteres (usando %s) y no como un número (usando %ld o %d), porque fin es un puntero a char, es decir, apunta a una dirección de memoria donde hay un char. Entonces, al usar %s, el programa va a imprimir los caracteres que hay a partir de esa dirección hasta que encuentre un '\0' (fin de cadena). Si usáramos %ld o %d, el programa intentaría interpretar la dirección de memoria como un número entero, lo cual no tiene sentido en este contexto y probablemente imprimiría un valor basura o causaría un error.
        } else {
            printf("Arg %d convertido con éxito: %ld\n", i, valor); //
        }
    }
    printf("El puntero apunta a la direccion: %p\n", fin);
    // Salida típica: 0x7fff5fbff7c0
    return 0;
}