#include <stdio.h>
/*Realizar un programa que muestre el contenido de un 
archivo de texto, cuyo nombre es ingresado por argumentos 
del main */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo>\n", argv[0]);
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", argv[1]);
        return 1;
    }

    char caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        putchar(caracter); // putchar(caracter) imprime el caracter leído en la consola
    }

    fclose(archivo);
    return 0;
}