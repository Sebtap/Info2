/*
Muestre el contenido de un archivo de texto cuyo nombre es ingresado
por argumentos del main.
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nombreArchivo>\n", argv[0]);
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s\n", argv[1]);
        return 1;
    }

    int c;

    // Imprime caracter por caracter usando printf
    while ((c = fgetc(archivo)) != EOF) {
        printf("%c", c);
    }

    /*
    //Mas rapida
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        printf("%s", buffer); // O bien: fputs(buffer, stdout);
    }
    */

    fclose(archivo);
    return 0;
}