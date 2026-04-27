#include <stdio.h>
/*Realizar un programa que copie un archivo a otro cuyos 
nombres estaran indicados como argumentos del main. 
Asi: copy archivo_original.txt archivo_copia.txt. */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo_original> <archivo_copia>\n", argv[0]);
        return 1;
    }

    FILE *archivo_orig = fopen(argv[1], "r");
    if (archivo_orig == NULL) {
        printf("No se pudo abrir el archivo %s.\n", argv[1]);
        return 1;
    }

    FILE *archivo_copia = fopen(argv[2], "w");
    if (archivo_copia == NULL) {
        printf("No se pudo crear el archivo %s.\n", argv[2]);
        fclose(archivo_orig);
        return 1;
    }

    char caracter;
    while ((caracter = fgetc(archivo_orig)) != EOF) {
        fputc(caracter, archivo_copia);
    }

    fclose(archivo_orig);
    fclose(archivo_copia);
    return 0;
}