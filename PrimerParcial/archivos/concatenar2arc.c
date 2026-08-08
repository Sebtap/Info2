#include <stdio.h>

/*
Concatenar 2 archivos de texto en uno nuevo
*/
int main() {

    // 1. Abrimos los dos archivos de lectura
    FILE *archTexto1 = fopen("archTexto1.txt", "r");
    if (archTexto1 == NULL) {
        fprintf(stderr, "Error al abrir archTexto1.txt\n");
        return 1;
    }

    FILE *archTexto2 = fopen("archTexto2.txt", "r");
    if (archTexto2 == NULL) {
        fprintf(stderr, "Error al abrir archTexto2.txt\n");
        fclose(archTexto1);
        return 1;
    }

    // 2. Abrimos el nuevo archivo en modo escritura ("w" alcanza, no hace falta "w+")
    FILE *nuevoArchivo = fopen("nuevoArchivo.txt", "w");
    if (nuevoArchivo == NULL) {
        fprintf(stderr, "Error al abrir nuevoArchivo.txt\n");
        fclose(archTexto1);
        fclose(archTexto2);
        return 1;
    }

   int c;
    int ultimo_c = '\n'; // Inicializamos en '\n' por si el archivo 1 está vacío

    // 1. Copiar el primer archivo
    while ((c = fgetc(archTexto1)) != EOF) {
        fputc(c, nuevoArchivo);
        ultimo_c = c;
    }

    // Si el primer archivo no terminó en salto de línea, lo agregamos
    if (ultimo_c != '\n') {
        fputc('\n', nuevoArchivo);
    }

    // 2. Copiar el segundo archivo
    while ((c = fgetc(archTexto2)) != EOF) {
        fputc(c, nuevoArchivo);
    }

    // 5. Cerramos todos los recursos
    fclose(archTexto1);
    fclose(archTexto2);
    fclose(nuevoArchivo);

    printf("Archivos concatenados con exito en 'nuevoArchivo.txt'\n");

    return 0;
}